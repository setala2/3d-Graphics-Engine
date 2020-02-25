#version 330 core

out vec4 color;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;

struct material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
};

uniform material mat;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

void main()
{
	float ambientIntensity = 0.2f;
	vec4 ambient = texture(mat.texture_diffuse1, TexCoords) * ambientIntensity;

	vec3 unitNormal = normalize(Normal);
	vec3 fragToLight = normalize(lightPosition - FragPosition);
	float diffuseIntensity = max(dot(unitNormal, fragToLight), 0.0f);
	vec4 diffuse = texture(mat.texture_diffuse1, TexCoords) * diffuseIntensity;

	float specularStrength = 0.5f;
	vec3 fragToCamera = normalize(cameraPosition - FragPosition);
	vec3 reflectDirection = reflect(-fragToLight, unitNormal);
	float spec = pow(max(dot(fragToCamera, reflectDirection), 0.0f), 64);
	vec4 specular = texture(mat.texture_specular1, TexCoords) * specularStrength * spec;
	
	color = ambient + diffuse + specular;
	//color = vec4(FragPosition, 1.0f);
}
