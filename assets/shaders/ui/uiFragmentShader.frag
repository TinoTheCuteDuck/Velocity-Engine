#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec3 Color;
flat in int widgetID;

uniform sampler2D uiTexture;

struct WidgetData {
        vec2 position;
        vec2 size;
        vec4 borderColor;
        float cornerRadius;
        float borderSize;
};

layout(std140, binding = 2) uniform WidgetProperties {
    WidgetData data[512];
}
widgets;

void main() {
    vec4 localSpace = gl_FragCoord - vec4(widgets.data[widgetID].position, 0, 0);
    vec4 texColor = texture(uiTexture, UV);
    // if (texColor.a < 0.01)
    //     discard;

    FragColor = vec4(Color, texColor.a);
}