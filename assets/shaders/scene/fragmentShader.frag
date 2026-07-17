#version 460 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;
in vec3 ViewPos;
in vec4 FragPosLight;
in mat3 TBN;

uniform int componentID;

uniform sampler2D shadowMap;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

const float PI = 3.14159265359;

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

layout (std140, binding = 0) uniform MeshProperties {
    MeshInstanceData data[512];
}
properties;

layout (std140, binding = 3) uniform LightsData {
    DirectionalLight dirLights[512];
    PointLight pointLights[512];
    SpotLight spotLights[512];
}
lights;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 cookTorranceBRDF(vec3 N, vec3 H, vec3 L, vec3 V, vec3 F0, vec3 radiance, vec3 albedo, float metallic, float roughness) {
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 kS = F;
    vec3 kD = vec3(1) - kS;
    kD *= 1.0 - metallic;

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;

    float NdotL = max(dot(N, L), 0.0);
    return (kD * albedo / PI + specular) * radiance * NdotL;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness) {
    vec3 L = normalize(-light.direction.xyz);
    vec3 H = normalize(V + L);

    vec3 radiance = light.color.rgb * light.color.a;
    return cookTorranceBRDF(N, H, L, V, F0, radiance, albedo, metallic, roughness);
};

vec3 calculatePointLight(PointLight light, vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness) {
    if (light.position.xyz == vec3(0)) return vec3(0);

    vec3 L = normalize(light.position.xyz - FragPos);
    vec3 H = normalize(V + L);

    float distance = length(light.position.xyz - FragPos);
    float attenuation = 1.0 / (light.params.y + light.params.z * distance + light.params.w * (distance * distance));

    vec3 radiance = light.color.rgb * attenuation * light.color.a;
    return cookTorranceBRDF(N, H, L, V, F0, radiance, albedo, metallic, roughness);
}

vec3 calculateSpotLight(SpotLight light, vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness) {
    if (light.direction.xyz == vec3(0)) return vec3(0);

    vec3 L = normalize(light.position.xyz - FragPos);
    vec3 H = normalize(V + L);

    float theta = dot(L, normalize(-light.direction.xyz));
    if (theta > light.params.y) {
        float distance = length(light.position.xyz - FragPos);
        float attenuation = 1.0 / (light.attenuationParams.x + light.attenuationParams.y * distance + light.attenuationParams.z * (distance * distance));

        vec3 radiance = light.color.rgb * attenuation * light.color.a;
        return cookTorranceBRDF(N, H, L, V, F0, radiance, albedo, metallic, roughness);
    };

    return vec3(0);
};

void main() {
    MeshInstanceData data = properties.data[componentID];
    float gamma = 2.2f;
    vec3 viewDirection = normalize(ViewPos - FragPos);

    vec4 albedo = texture(albedoMap, UV);
    albedo = vec4(pow(albedo.rgb, vec3(gamma)), albedo.a);

    vec3 normal = texture(normalMap, UV).rgb;
    normal = normal * 2.0 - 1.0;
    normal = normalize(TBN * normal);

    float metallic = texture(metallicMap, UV).r;
    float roughness = texture(roughnessMap, UV).r;
    float ambientOcclusion = texture(aoMap, UV).r;

    vec3 F0 = mix(vec3(0.04), albedo.rgb, metallic);
    vec3 outputColor = vec3(0);

    for (int i = 1; i < 2; i++) {
        outputColor += calculateDirectionalLight(lights.dirLights[i], normal, viewDirection, F0, albedo.rgb, metallic, roughness);
        // outputColor += calculatePointLight(lights.pointLights[i], normal, viewDirection, F0, albedo.rgb, metallic, roughness);
        // outputColor += calculateSpotLight(lights.spotLights[i], normal, viewDirection, F0, albedo.rgb, metallic, roughness);
    };

    vec3 projCoords = FragPosLight.xyz / FragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5;

    float currentDepth = projCoords.z;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -5; x <= 5; ++x) {
        for (int y = -5; y <= 5; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 121.0;

    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }

    vec3 ambient = vec3(0.01) * albedo.rgb * ambientOcclusion;
    vec3 color = ambient + (1.0 - shadow) * outputColor;

    vec4 finalColor = vec4(color, albedo.a);
    finalColor *= data.color;
    finalColor.rgb = pow(finalColor.rgb, vec3(1 / gamma));

    FragColor = finalColor;
}