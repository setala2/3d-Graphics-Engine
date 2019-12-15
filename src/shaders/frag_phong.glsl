#version 330 core

uniform float ambientIntensity;
uniform vec3 ambientColor;

out vec4 fragmentColor;

void main()
{
	// Let's say the object is pure white, for now.
	// This means that only the light color affects the fragment.
	fragmentColor = vec4(ambientIntensity * ambientColor, 1.0f);
}