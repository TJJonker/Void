#version 330 core

out vec4 outcolor;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINTS_LIGHT 4
#define NR_SPOT_LIGHTS 2  // Adjust the number of spotlights as needed

uniform PointLight pointLights[NR_POINTS_LIGHT];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];  // Add spotlights

in vec2 TextureCoords;
in vec3 Normal;
in vec3 FragPosition;

uniform DirectionalLight directionalLight;

uniform sampler2D texture1;

vec3 CalculateDirectionalLighting() {
    // Ambient
    vec3 ambient = directionalLight.ambient * vec3(texture(texture1, TextureCoords));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff * vec3(texture(texture1, TextureCoords));

    return ambient + diffuse;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Attenuation shading
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec3 ambient = light.ambient * vec3(texture(texture1, TextureCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, TextureCoords));

    return (ambient + diffuse) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Attenuation and spotlight effects
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    float spotEffect = dot(normalize(-lightDir), normalize(light.direction));

    if (spotEffect > cos(light.cutOff)) {
        // Within spotlight cone
        float spotlightFactor = smoothstep(cos(light.outerCutOff), cos(light.cutOff), spotEffect);
        vec3 ambient = light.ambient * vec3(texture(texture1, TextureCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, TextureCoords));

        return (ambient + diffuse) * attenuation * spotlightFactor;
    } else {
        // Outside spotlight cone
        return vec3(0.0);
    }
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 result = CalculateDirectionalLighting();

    for (int i = 0; i < NR_POINTS_LIGHT; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPosition);
    }

    for (int i = 0; i < NR_SPOT_LIGHTS; i++) {
        result += CalcSpotLight(spotLights[i], norm, FragPosition);
    }

    outcolor = vec4(result, 1.0);
}
