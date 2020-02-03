#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	color = texture(texture_diffuse1, TexCoords);
}
