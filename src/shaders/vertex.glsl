#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vColor;

uniform mat4 mvp;
out vec3 color_pass;

void main()
{
	gl_Position = mvp * vec4(position, 1.0f);
	color_pass = vColor;
}