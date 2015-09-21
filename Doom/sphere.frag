#version 330 core
out vec4 color;

//uniform vec4 uColor;
uniform vec4 uColor;

void main()
{
    //color = vec4(1.0f); // Set alle 4 vector values to 1.0f
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	color = uColor;
}