#version 330 core
out vec4 color;
//uniform vec4 uColor;

//in vec4 oFinalVertexColor;

uniform vec4 uColor;
uniform vec3 uLightPosition;

in vec3 Normal;  
in vec3 FragPos;

void main()
{

	
	vec3 lightPosition = normalize(uLightPosition);
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(uColor.x, uColor.y, uColor.z);
	vec3 result = (diffuse);
	color = vec4(result, 1.0f);

	//color = oFinalVertexColor; //
	//color = vec4(0.1f, 0.2f, 0.4f, 1.0f); //for now
}