#version 330 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

out vec4 color;

uniform vec3 LightPosition;
uniform sampler2D TheTexture;

void main()
{
	float ambientIntensity = 0.2f;
	vec4 ambient = texture(TheTexture, TexCoords) * ambientIntensity;
	
	vec3 unitNormal = normalize(Normal);
	vec3 fragToLight = normalize(LightPosition - FragPosition);
	float diffuseIntensity = max(dot(fragToLight, unitNormal), 0.0f);
	vec4 diffuse = texture(TheTexture, TexCoords) * diffuseIntensity;

	color = ambient + diffuse;
}
