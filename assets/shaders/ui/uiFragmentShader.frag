#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec4 Color;

void main() {
    FragColor = Color;
}