#version 330 core
out vec4 color;
//uniform vec4 uColor;

in vec4 oFinalVertexColor;

void main()
{
    //color = vec4(0.9f); // Set alle 4 vector values to 1.0f
	//color = vec4(0.1f, 0.2f, 0.4f, 1.0f);

	//gl_FragColor = vec4(0.1f, 0.2f, 0.4f, 1.0f);
	color = oFinalVertexColor; //wtf?
}