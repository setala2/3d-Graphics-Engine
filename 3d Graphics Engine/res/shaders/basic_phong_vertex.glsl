#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 fragPosition;
out vec3 normal;

uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main()
{
	fragPosition = vec3(modelMatrix * vec4(aPosition, 1.0f));
	normal = normalMatrix * aNormal;

	gl_Position = viewProjectionMatrix * modelMatrix * vec4(aPosition, 1.0f);
}
