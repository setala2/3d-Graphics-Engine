#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform Sampler2D texture_diffuse1;

void main()
{
	color = texture(texture_diffuse1, TexCoords);
}
