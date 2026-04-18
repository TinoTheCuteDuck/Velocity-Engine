#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec3 Color;

uniform sampler2D uiTexture;

void main() {
    float alpha = texture(uiTexture, UV).r;
    FragColor = vec4(Color, 1.0);
}