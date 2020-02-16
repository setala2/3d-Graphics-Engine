#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPosition;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(aPosition, 1.0f);
	FragPosition = aPosition;
	Normal = aNormal;
	TexCoords = aTexCoords;
}