#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride)
	:_mode(mode), _count(count), _stride(stride)
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


void VertexBuffer::configureVertexAttributes(GLint vertexPosition)
{

	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	if (vertexPosition != -1)
	{
		glEnableVertexAttribArray(vertexPosition);
		glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FLOAT, _stride, (GLvoid*)0);
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