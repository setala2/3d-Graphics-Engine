#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
