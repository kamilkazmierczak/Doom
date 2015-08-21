#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const GLvoid *data, 
						   GLsizeiptr size, 
						   GLenum mode, 
						   GLsizei count, 
						   GLsizei stride, 
						   ShaderInterface *shader,
						   GLvoid *positionOffset,
						   GLvoid *normalOffset)
:_mode(mode), _count(count), _stride(stride), _shader(shader), _positionOffset(positionOffset), _normalOffset(normalOffset)
{
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0); ??
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferID);
	_vertexBufferID = 0;
}

GLuint VertexBuffer::getVertexBufferID()
{
	return _vertexBufferID;
}


ShaderInterface* VertexBuffer::getShader()
{
	return _shader;
}

void VertexBuffer::configureVertexAttributes()
{

	
	glGenVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);//zeby bral wlasciwe wierzcholki
	glBindVertexArray(VAO);

	if (_shader->get_aPositionVertex() != -1)
	{
		glEnableVertexAttribArray(_shader->get_aPositionVertex());
		glVertexAttribPointer(_shader->get_aPositionVertex(), 3, GL_FLOAT, GL_FLOAT, _stride, _positionOffset);
	}

	if (_shader->get_aPositionNormal() != -1)
	{
		glEnableVertexAttribArray(_shader->get_aPositionNormal());
		glVertexAttribPointer(_shader->get_aPositionNormal(), 3, GL_FLOAT, GL_FLOAT, _stride, _normalOffset);
	}

	glBindVertexArray(0);
}


void VertexBuffer::renderVertexBuffer()
{
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(_mode, 0, _count);
	glBindVertexArray(0);
	
}