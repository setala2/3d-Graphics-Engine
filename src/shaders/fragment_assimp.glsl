#version 330 core

out vec4 color;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
};
uniform material mat;
uniform vec3 cameraPos;

void main()
{
	// A fixed light position for now
	vec3 lightPos = vec3(2.0f, 6.0f, 3.0f);

	float ambientIntensity = 0.2f;
	vec4 ambient = texture(mat.texture_diffuse1, TexCoords) * ambientIntensity;

	vec3 unitNormal = normalize(Normal);
	vec3 fragToLight = normalize(lightPos - FragPos);
	float diffuseIntensity = max(dot(unitNormal, fragToLight), 0.0f);
	vec4 diffuse = texture(mat.texture_diffuse1, TexCoords) * diffuseIntensity;

	float specularStrength = 0.5f;
	vec3 fragToCamera = normalize(cameraPos - FragPos);
	vec3 reflectDirection = reflect(-fragToLight, unitNormal);
	float spec = pow(max(dot(fragToCamera, reflectDirection), 0.0f), 32);
	vec4 specular = texture(mat.texture_specular1, TexCoords) * specularStrength * spec;
	
	color = ambient + diffuse + specular;
}
