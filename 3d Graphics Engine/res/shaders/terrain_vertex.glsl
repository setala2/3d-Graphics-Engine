#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPosition;
out vec3 Normal;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(aPosition, 1.0f);
	FragPosition = vec3(modelMatrix * vec4(aPosition, 1.0f));
	Normal = aNormal;
	TexCoords = aTexCoords;
}