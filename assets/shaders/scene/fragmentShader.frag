#version 460 core
out vec4 FragColor;

in vec2 UV;
in vec3 FragPos;
in vec3 Normal;

void main() {
    float ambientStrength = 0.3;
    vec3 lightColor = vec3(0.8, 0.8, 0.8);
    vec3 lightPos = vec3(2.0, 4.0, 3.0);

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);
    FragColor = vec4(result, 1.0);
}