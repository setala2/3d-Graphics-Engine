#version 330 core

in vec3 normal;
in vec3 fragPosition;

out vec4 color;

uniform vec3 cameraPosition;
uniform samplerCube skyBox;

void main()
{
	vec3 cameraToFrag = -normalize(fragPosition - cameraPosition);
	vec3 unitNormal = normalize(normal);
	vec3 reflectionVector = reflect(cameraToFrag, unitNormal);
	color = texture(skyBox, reflectionVector);
}