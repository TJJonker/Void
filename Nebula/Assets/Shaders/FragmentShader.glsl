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
flat in float TextureIndex[3];

uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;
uniform sampler2D Textures[32];

void main()
{
     // Ambient
    vec4 ambient = vec4(directionalLight.ambient, 1) * texture(Textures[int(TextureIndex[0])], TextureCoords);

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(directionalLight.diffuse * diff, 1) * texture(Textures[int(TextureIndex[0])], TextureCoords);

    // Specuar 
//    vec3 viewDir = normalize(viewPosition - FragPosition); 
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = directionalLight.specular * spec;

    //vec3 result = ambient + diffuse + specular;
    vec4 result = ambient + diffuse;
    color = result;
    //color = vec4(0.3, 0.3, 0.6, 1.0);
    //color = texture(Textures[int(TextureIndex[0])], TextureCoords).rrrr;
}