#version 330 core
			
out vec4 color;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TextureCoords;
in vec3 Normal;
in vec3 FragPosition;
in vec3 TextureIndex;
flat in int ShowTexture;
in float Intensity;

uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;
uniform sampler2D Textures[32];

void main()
{
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

    float alpha = texture(Textures[int(TextureIndex.y)], TextureCoords).a;
    
    if(alpha < .1)
        discard;
    color = vec4(result * 5 * Intensity, alpha);
}