#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 uv_in;

uniform mat4 model;
uniform mat4 viewProjection;
uniform mat3 normalMatrix;

smooth out vec3 normal;
out vec3 fragPosition;
out vec2 uv;

void main()
{
	gl_Position = viewProjection * model * vec4(position, 1.0f);
	normal = normalMatrix * normal_in;
	fragPosition = vec3(model * vec4(position, 1.0f));
	uv = uv_in;
}