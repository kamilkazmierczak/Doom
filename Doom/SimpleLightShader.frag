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
uniform Material material;
uniform Light light;


void main()
{	




	//vec3 light_ambient = vec3(0.2f, 0.2f, 0.2f);
	//vec3 light_diffuse = vec3(0.5f, 0.5f, 0.5f);
	//vec3 light_specular = vec3(0.5f, 0.5f, 0.5f); //jesli bd potrzeba specular potem



	// Ambient
	vec3 ambient = light.ambient * vec3(texture(uTexture1, TextureCoord));


	// Diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(uTexture1, TextureCoord));

	// Specular //jesli to chce dodaj uniforma viewPos i podaj pozycje kamery
	vec3 viewDir = normalize(uViewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//   //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	//2

	//ambient = light.ambient * vec3(texture(uTexture1, TextureCoord));
	//// Diffuse 
	//norm = normalize(Normal);
	//lightDir = normalize(uLightPosition2 - FragPos);
	//diff = max(dot(norm, lightDir), 0.0);
	//diffuse = light.diffuse * diff * vec3(texture(uTexture1, TextureCoord));

	//result = result + ambient + diffuse;

	color = vec4(result/*+ specular*/, 1.0f);

}