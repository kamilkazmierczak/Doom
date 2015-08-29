#version 330 core
layout (location = 0) in vec3 aPositionVertex;
layout (location = 1) in vec3 aPositionNormal;
layout (location = 2) in vec2 aTextureCoord;

//out vec4 oFinalVertexColor;

//attribute vec3 aPositionVertex; //podobno to samo co in ale uzyl "_aPositionVertex = glGetAttribLocation(shader->Program, "aPositionVertex");"
								//a to juz nie wiem czy zadziala jak wstawie in
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 Normal;
out vec3 FragPos;
out vec2 TextureCoord;

void main()
{
	/*
					//gl_NormalMatrix ZABRONIONE (tymczasowo)
					//Normal = mat3(transpose(inverse(model))) * normal; 
	vec3 normal = normalize(gl_NormalMatrix * aPositionNormal);
	vec3 lightPosition = normalize(vec3(0.0, 0.0, 1.0));

		  //diffuse lighting
	float dotProduct = max(dot(normal, lightPosition), 0.0);
									//jakis kolor (red)
	oFinalVertexColor = dotProduct * vec4(1.0, 0.0, 0.0, 1.0);
	*/

	gl_Position = projection * view * model * vec4(aPositionVertex, 1.0);
	FragPos = vec3(model* vec4(aPositionVertex, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aPositionNormal;
	TextureCoord = vec2(aTextureCoord.x, 1.0 - aTextureCoord.y);
	//Normal = aPositionNormal; //??? tez tak niby wg learnopengl
	//Normal = projection * view * model * aPositionNormal; //niby wg tutoriala
} 