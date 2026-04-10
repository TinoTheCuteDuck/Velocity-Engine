#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec3 Color;

void main() {
    FragColor = vec4(Color, 1.0);
}