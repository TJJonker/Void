#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

in vec2 TextureCoords;
in vec3 TextureIndex;

uniform vec3 viewPosition;  
uniform sampler2D Textures[32];
uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(FragPosition - viewPosition);
    vec3 R = reflect(I, normalize(Normal));

    vec3 reflectColor = texture(skybox, R).rgb;
    vec3 tex = texture(Textures[int(TextureIndex.x)], TextureCoords).rgb;
    vec3 finalColor = mix(tex, reflectColor, .7);
    FragColor = vec4(finalColor, .8);
}