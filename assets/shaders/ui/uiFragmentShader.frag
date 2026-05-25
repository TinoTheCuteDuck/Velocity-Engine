#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec4 Color;
flat in uint WidgetID;

uniform sampler2D uiTexture;

struct WidgetData {
        vec4 rect; // x,y = Position; z,w = Size;
        vec4 borderColor;
        vec4 params; // x = cornerRadius; y = borderSize; z,w = unused
};

layout(std140, binding = 2) uniform WidgetProperties {
    WidgetData data[512];
}
widgets;

void main() {
    WidgetData data = widgets.data[WidgetID];
    float radius = data.params.x;
    vec2 position = data.rect.xy;
    vec2 size = data.rect.zw;
    vec2 halfSize = size * 0.5;
    float alpha = 1.0f;

    if (!(radius <= 0)) {
        vec2 localSpace = gl_FragCoord.xy - position - halfSize;
        float distance = length(max(abs(localSpace) - (halfSize - radius), 0)) - radius;
        alpha = smoothstep(2.0f, 0.0f, distance);
    }

    vec4 texColor = texture(uiTexture, UV);
    float finalAlpha = alpha * Color.a * texColor.a;

    FragColor = vec4(Color.rgb, finalAlpha);
}