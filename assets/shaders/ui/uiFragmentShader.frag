#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec4 Color;
flat in uint WidgetID;

uniform sampler2D albedoMap;

struct WidgetData {
    vec4 rect;  // x,y = Position; z,w = Size;
    vec4 borderColor;
    vec4 params;      // x = cornerRadius; y = borderSize; z,w = unused
    vec4 clipRect;    // x,y = Position; z,w = size;
    vec4 clipParams;  // x = clipCornerRadius; y = clipBorderSize; z,w = unused
};

layout(std140, binding = 2) uniform WidgetProperties {
    WidgetData data[512];
}
widgets;

float roundedBoxSDF(vec2 centerPosition, vec2 halfSize, float radius) {
    vec2 q = abs(centerPosition) - halfSize + radius;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - radius;
}

void main() {
    WidgetData data = widgets.data[WidgetID];
    vec2 position = data.rect.xy;
    vec2 size = data.rect.zw;
    vec2 halfSize = size * 0.5;
    vec2 center = position + halfSize;

    float radius = min(data.params.x, min(halfSize.x, halfSize.y));
    float borderSize = data.params.y;

    float distance = roundedBoxSDF(gl_FragCoord.xy - center, halfSize, radius);
    float antiAliasing = fwidth(distance) * 1.5f;

    float clipAlpha = 1.0f;
    float smoothedAlpha = 1.0 - smoothstep(0.0f, antiAliasing, distance);
    float borderAlpha = 1.0 - smoothstep(borderSize - antiAliasing, borderSize, -distance);
    borderAlpha *= smoothedAlpha;

    if (data.clipRect.z > 0.0f) {
        vec2 clipPos = data.clipRect.xy;
        vec2 clipSize = data.clipRect.zw;
        vec2 clipHalfSize = clipSize * 0.5f;
        vec2 clipCenter = clipPos + clipHalfSize;
        float clipBorderSize = data.clipParams.y - 1.0f;
        float clipRadius = min(data.clipParams.x, min(clipHalfSize.x, clipHalfSize.y));

        float clipDistance = roundedBoxSDF(gl_FragCoord.xy - clipCenter, clipHalfSize, clipRadius) + clipBorderSize;
        clipAlpha = 1.0 - smoothstep(-antiAliasing, antiAliasing, clipDistance);
    }

    vec4 texColor = texture(albedoMap, UV);
    vec4 finalColor = mix(Color, data.borderColor, borderAlpha);
    finalColor.a *= clipAlpha;
    finalColor.a *= smoothedAlpha;
    finalColor.a *= texColor.a;
    FragColor = finalColor;
}