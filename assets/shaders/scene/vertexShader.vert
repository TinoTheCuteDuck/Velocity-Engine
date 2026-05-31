#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 UV;
out vec3 FragPos;
out vec3 Normal;
out vec3 Color;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    UV = aUV;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    Color = aColor;
}