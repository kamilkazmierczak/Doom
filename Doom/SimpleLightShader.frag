#version 330 core
out vec4 color;


struct Material {
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec4 uColor;
//uniform vec3 uLightPosition;
//uniform vec3 uLightPosition2;
uniform sampler2D uTexture1;
uniform vec3 uViewPosition;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TextureCoord;


//
#define NR_OF_LIGHTS 2

uniform Material material;
uniform Light light[NR_OF_LIGHTS];


vec3 CalcLight(Light light, Material material, sampler2D uTexture1, vec3 fragPos, vec3 normal, vec2 TextureCoord);


void main()
{	
	vec3 result;

	  for (int i = 0; i < NR_OF_LIGHTS; i++)
		result += CalcLight(light[i], material, uTexture1, FragPos, Normal, TextureCoord);

	color = vec4(result, 1.0f);

}


vec3 CalcLight(Light light, Material material, sampler2D uTexture1, vec3 fragPos, vec3 normal, vec2 TextureCoord)
{

	// Ambient
	vec3 ambient = light.ambient * vec3(texture(uTexture1, TextureCoord));

	// Diffuse 
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(uTexture1, TextureCoord));

	// Specular 
	vec3 viewDir = normalize(uViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse +specular;

	return result;
}