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

uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;
uniform sampler2D texture1;

void main()
{
    // Ambient
    vec3 ambient = directionalLight.ambient * vec3(texture(texture1, TextureCoords));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff * vec3(texture(texture1, TextureCoords));

    // Specuar 
//    vec3 viewDir = normalize(viewPosition - FragPosition); 
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = directionalLight.specular * spec;

    //vec3 result = ambient + diffuse + specular;
    vec3 result = ambient + diffuse;
    color = vec4(result, 1.0);
}