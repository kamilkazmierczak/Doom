#version 330 core
out vec4 color;
//uniform vec4 uColor;

in vec4 oFinalVertexColor;

void main()
{

	//color = oFinalVertexColor; //
	color = vec4(0.1f, 0.2f, 0.4f, 1.0f); //for now
}