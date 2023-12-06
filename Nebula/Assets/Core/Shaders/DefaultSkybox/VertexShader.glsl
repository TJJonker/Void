#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

out vec3 TexCoords;

void main()
{
    TexCoords = aPos;
    vec4 pos = viewProjectionMatrix * modelMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  