#version 330 core
out vec4 color;
//uniform vec4 uColor;

//in vec4 oFinalVertexColor;

uniform vec4 uColor;
uniform vec3 uLightPosition;
uniform sampler2D uTexture1;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TextureCoord;

void main()
{
	//WRONG odkomentuj to i ogarnij teksture razem ze swiatlem
	
	vec3 lightPosition = normalize(uLightPosition);
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * vec3(uColor.x, uColor.y, uColor.z);
	vec3 diffuse = diff * vec3(texture(uTexture1, TextureCoord));
	vec3 result = (diffuse);
	color = vec4(result, 1.0f); 

	//jak chce zeby kostka swiecila kolorem uColor to
	//doswiadczalnie tak wyszlo
	//vec3 diffuse = diff * vec3(uColor.x, uColor.y, uColor.z);
	//color = vec4(result, 1.0f) * texture(uTexture1, TextureCoord);




	//color = texture(uTexture1, TextureCoord);
	//color = oFinalVertexColor; //
	//color = vec4(0.1f, 0.2f, 0.4f, 1.0f); //for now
}