#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uint aWidgetId;

out vec2 UV;
out vec4 Color;
out uint WidgetID;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    UV = aUV;
    Color = aColor;
    WidgetID = aWidgetId;
}