#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 aTextureCoords;
layout(location = 3) in vec3 a_TextureIndex;
layout(location = 4) in int a_showTexture;

uniform mat4 viewProjectionMatrix;
uniform float Time;

out vec2 TextureCoords;
out vec3 Normal;
out vec3 FragPosition;
out vec3 TextureIndex;
flat out int ShowTexture;
out float Intensity;

void main()
{
	TextureCoords = aTextureCoords;
	FragPosition = a_Position;
	Normal = a_Normal;
	TextureIndex = a_TextureIndex;
	ShowTexture = a_showTexture;
	Intensity = 1;

	vec3 newPos = a_Position;
	float switchValue = smoothstep(0.0, 1.0, fract(Time));
	if(gl_VertexID % 4 == 2 || gl_VertexID == 2 || gl_VertexID % 4 == 3 || gl_VertexID == 3){
		newPos = a_Position + vec3(0, switchValue * .5, 0);
		Intensity = 1 - switchValue;
	}

	gl_Position = viewProjectionMatrix * vec4(newPos, 1);
}