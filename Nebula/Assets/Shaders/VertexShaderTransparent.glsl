#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 aTextureCoords;
layout(location = 3) in vec3 a_TextureIndex;
layout(location = 4) in int a_showTexture;

uniform mat4 viewProjectionMatrix;

out vec2 TextureCoords;
out vec3 Normal;
out vec3 FragPosition;
out vec3 TextureIndex;
flat out int ShowTexture;

void main()
{
	TextureCoords = aTextureCoords;
	FragPosition = a_Position;
	Normal = a_Normal;

	gl_Position = viewProjectionMatrix * vec4(a_Position, 1);
}