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

uniform float Time;
uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;
uniform sampler2D Textures[32];

void main()
{

    //float switchValue = smoothstep(0.0, 1.0, fract(Time / 2));

    // Calculate the progress of time in the range [0, 1] over 2.5 seconds
    float switchValue = smoothstep(0.0, 1.0, fract(Time / 5));

    vec2 txtOffset = vec2(switchValue, 0);

     // Ambient
    vec3 ambient = directionalLight.ambient;
    if(ShowTexture == 1)
        ambient *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords + txtOffset));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionalLight.diffuse * diff;
    if(ShowTexture == 1)
        diffuse *= vec3(texture(Textures[int(TextureIndex.x)], TextureCoords + txtOffset));


    // Specuar 
    vec3 viewDir = normalize(viewPosition - FragPosition); 
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = directionalLight.specular * spec;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1);
}