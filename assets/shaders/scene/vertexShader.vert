#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 lightProjection;

out vec3 FragPos;
out vec2 UV;
out vec3 Normal;
out vec3 ViewPos;
out vec4 FragPosLight;

layout(std140, binding = 1) uniform CameraMatrices {
    mat4 viewProjection;
    vec4 viewPos;  // w unused
}
matrices;

void main() {
    gl_Position = matrices.viewProjection * model * vec4(aPos, 1.0);

    FragPos = vec3(model * vec4(aPos, 1.0));
    UV = aUV;
    Normal = transpose(inverse(mat3(model))) * aNormal;
    ViewPos = matrices.viewPos.xyz;
    FragPosLight = lightProjection * vec4(FragPos, 1.0);
}