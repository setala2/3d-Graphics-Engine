#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

out vec3 normal;
out vec3 fragPosition;

void main()
{
	normal = normalMatrix * aNormal;
	fragPosition = vec3(modelMatrix * vec4(aPosition, 1.0f));
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(aPosition, 1.0f);
}