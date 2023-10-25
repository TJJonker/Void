#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 aTextureCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 TextureCoords;
out vec3 Normal;
out vec3 FragPosition;

void main()
{
	TextureCoords = aTextureCoords;
	FragPosition = vec3(modelMatrix * vec4(a_Position, 1.0));
	Normal = mat3(transpose(inverse(modelMatrix))) * a_Normal;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_Position, 1.0);
}