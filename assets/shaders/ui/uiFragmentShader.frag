#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec3 Color;

uniform sampler2D uiTexture;

void main() {
    vec4 texColor = texture(uiTexture, UV);
    if (texColor.a < 0.01)
        discard;

    FragColor = vec4(Color, texColor.a);
}