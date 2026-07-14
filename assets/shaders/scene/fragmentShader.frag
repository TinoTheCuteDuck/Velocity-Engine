#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;
in vec3 ViewPos;
in vec4 FragPosLight;

uniform int componentID;
uniform sampler2D shadowMap;
uniform sampler2D albedo;
uniform sampler2D metallic;

struct DirectionalLight {
    vec4 direction;  // w unused
    vec4 color;      // w is intensity
};

struct PointLight {
    vec4 position;  // w unused
    vec4 color;     // w unused
    vec4 params;    // x = intensity, y = constant, z = linear, w = quadratic
};

struct SpotLight {
    vec4 position;           // w unused
    vec4 direction;          // w unused
    vec4 color;              // w unused
    vec4 params;             // x = intensity, y = outerAngle, z = innerAngle, w = unused
    vec4 attenuationParams;  // x = constant, y = linear, z = quadratic, w = unused
};

struct MeshInstanceData {
    vec4 color;
};

layout(std140, binding = 0) uniform MeshProperties {
    MeshInstanceData data[512];
}
properties;

layout(std140, binding = 3) uniform LightsData {
    DirectionalLight dirLights[512];
    PointLight pointLights[512];
    SpotLight spotLights[512];
}
lights;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    if (light.direction.xyz == vec3(0)) {
        return vec3(0);
    }
    vec3 lightDirection = normalize(-light.direction.xyz);

    float diff = max(dot(lightDirection, normal), 0);
    vec3 diffuse = light.color.rgb * diff * light.color.w;

    vec3 halfwayVector = normalize(lightDirection + viewDirection);
    float spec = max(dot(normal, halfwayVector), 0.0);
    vec3 specular = light.color.rgb * pow(spec, 16) * light.color.w * 0.5f;

    vec3 finalColor = diffuse + specular;

    return finalColor;
};

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 viewDirection) {
    if (light.position.xyz == vec3(0)) {
        return vec3(0);
    }
    vec3 lightDirection = normalize(light.position.xyz - FragPos);

    float diff = max(dot(lightDirection, normal), 0);
    vec3 diffuse = light.color.rgb * diff * light.params.x;

    vec3 halfwayVector = normalize(lightDirection + viewDirection);
    float spec = max(dot(normal, halfwayVector), 0.0);
    vec3 specular = light.color.rgb * pow(spec, 32) * light.params.x * 0.5f;

    float distance = length(light.position.xyz - FragPos);
    float attenuation = 1.0 / (light.params.y + light.params.z * distance + light.params.w * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    vec3 finalColor = diffuse + specular;
    return finalColor;
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {
    if (light.direction.xyz == vec3(0)) {
        return vec3(0);
    }
    vec3 lightDirection = normalize(light.position.xyz - FragPos);

    float theta = dot(lightDirection, normalize(-light.direction.xyz));
    if (theta > light.params.y) {
        float diff = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = light.color.rgb * diff * light.params.x;

        vec3 halfwayVector = normalize(lightDirection + viewDirection);
        float spec = max(dot(normal, halfwayVector), 0.0);
        vec3 specular = light.color.rgb * pow(spec, 32) * light.params.x * 0.5;

        float distance = length(light.position.rgb - FragPos);
        float attenuation = 1.0 / (light.attenuationParams.x + light.attenuationParams.y * distance + light.attenuationParams.z * (distance * distance));

        diffuse *= attenuation;
        specular *= attenuation;

        float epsilon = light.params.z - light.params.y;
        float intensity = clamp((theta - light.params.y) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;

        vec3 finalColor = diffuse + specular;
        return finalColor;
    };

    return vec3(0);
};

void main() {
    MeshInstanceData data = properties.data[componentID];

    vec3 viewDirection = normalize(ViewPos - FragPos);
    vec3 normal = normalize(Normal);
    vec3 ambient = vec3(0.08, 0.09, 0.12);
    float gamma = 2.2f;

    vec4 albedoColor = texture(albedo, UV);
    vec4 albedoGammaCorrected = vec4(pow(albedoColor.rgb, vec3(gamma)), albedoColor.a);
    vec4 metallic = texture(metallic, UV);

    vec3 outputColor = vec3(0);

    for (int i = 0; i < 512; i++) {
        outputColor += calculateDirectionalLight(lights.dirLights[i], normal, viewDirection);
        outputColor += calculatePointLight(lights.pointLights[i], normal, viewDirection);
        outputColor += calculateSpotLight(lights.spotLights[i], normal, viewDirection);
    };

    vec3 projCoords = FragPosLight.xyz / FragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5;

    float currentDepth = projCoords.z;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }

    vec3 lighting = ambient + (1.0 - shadow) * outputColor;
    vec4 finalColor = vec4(albedoGammaCorrected.rgb * lighting, albedoGammaCorrected.a);
    finalColor *= data.color;
    finalColor.rgb = pow(finalColor.rgb, vec3(1 / gamma));

    FragColor = finalColor;
}