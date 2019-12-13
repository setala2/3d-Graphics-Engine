#version 330 core

in vec3 color_pass;

out vec4 color;

void main()
{
	color = vec4(color_pass, 1.0f);
}