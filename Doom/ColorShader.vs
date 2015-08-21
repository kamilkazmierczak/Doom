#version 330 core
layout (location = 0) in vec3 aPositionVertex;

//attribute vec3 aPositionVertex; //podobno to samo co in ale uzyl "_aPositionVertex = glGetAttribLocation(shader->Program, "aPositionVertex");"
								//a to juz nie wiem czy zadziala jak wstawie in
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   // gl_Position = projection * view * model * vec4(position, 1.0f);
   // gl_Position = projection * view * model * vec4(aPositionVertex, 1.0f);
	//gl_Position = gl_ModelViewProjectionMatrix * vec4(aPositionVertex, 1.0);

	gl_Position = projection * view * model * vec4(aPositionVertex, 1.0);
} 