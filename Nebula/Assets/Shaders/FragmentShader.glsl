#version 330 core
			
out vec4 color;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLightData {
	vec3 Position;
	float Constant;
	float Linear;
	float Quadratic;
	vec3 Ambient;
	vec3 Diffuse;
};

in vec2 TextureCoords;
in vec3 Normal;
in vec3 FragPosition;
in vec3 TextureIndex;
flat in int ShowTexture;

uniform DirectionalLight directionalLight;

#define NR_POINTS_LIGHT 1
uniform PointLightData pointLightData[NR_POINTS_LIGHT];

uniform vec3 viewPosition;  
uniform sampler2D Textures[32];

layout (std140) uniform Lights
{
    mat4 projection;
    mat4 view;
};



vec3 CalculateDirectionalLighting() {
    // Ambient
    vec3 ambient = directionalLight.ambient;
    if(ShowTexture == 1)
        ambient *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff;
    if(ShowTexture == 1)
        diffuse *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));

    // Specuar 
    vec3 viewDir = normalize(viewPosition - FragPosition); 
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = directionalLight.specular * spec;

    vec3 result = ambient + diffuse + specular;

    return result;
}

vec3 CalcPointLight(PointLightData light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.Position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Attenuation shading
    float dist = length(light.Position - fragPos);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

    vec3 ambient = light.Ambient;
    if(ShowTexture == 1)
        ambient *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));

    vec3 diffuse = light.Diffuse * diff;
    if(ShowTexture == 1)
        diffuse *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));

    return (ambient + diffuse) * attenuation;
}

//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos) {
//    vec3 lightDir = normalize(light.position - fragPos);
//    // Diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    
//    // Attenuation and spotlight effects
//    float dist = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
//    float spotEffect = dot(normalize(-lightDir), normalize(light.direction));
//
//    if (spotEffect > cos(light.cutOff)) {
//        // Within spotlight cone
//        float spotlightFactor = smoothstep(cos(light.outerCutOff), cos(light.cutOff), spotEffect);
//        vec3 ambient = light.ambient * vec3(texture(texture1, TextureCoords));
//        vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, TextureCoords));
//
//        return (ambient + diffuse) * attenuation * spotlightFactor;
//    } else {
//        // Outside spotlight cone
//        return vec3(0.0);
//    }
//}

void main() {
    vec3 norm = normalize(Normal);

    vec3 result = CalculateDirectionalLighting();

    for (int i = 0; i < NR_POINTS_LIGHT; i++) {
        result += CalcPointLight(pointLightData[i], norm, FragPosition);
    }

//    for (int i = 0; i < NR_SPOT_LIGHTS; i++) {
//        result += CalcSpotLight(spotLights[i], norm, FragPosition);
//    }

    color = vec4(result, 1.0);
}



//void main()
//{
//     // Ambient
//    vec3 ambient = directionalLight.ambient;
//    if(ShowTexture == 1)
//        ambient *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));
//
//    // Diffuse
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(-directionalLight.direction);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = directionalLight.diffuse * diff;
//    if(ShowTexture == 1)
//        diffuse *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords));
//
//
//    // Specuar 
//    vec3 viewDir = normalize(viewPosition - FragPosition); 
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
//    vec3 specular = directionalLight.specular * spec;
//
//    vec3 result = ambient + diffuse + specular;
//    color = vec4(result, 1);
//}