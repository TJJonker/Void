#version 330 core
			
out vec4 color;

in float Transparency;



void main() {
    color = vec4(1, 1, 1, Transparency);
}
