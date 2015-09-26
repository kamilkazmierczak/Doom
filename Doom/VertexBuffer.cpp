#include "VertexBuffer.h"
#include "VertexData.h"

VertexBuffer::VertexBuffer(GLvoid *data, 
						   GLsizeiptr size, 
						   GLenum mode, 
						   GLsizei count, 
						   GLsizei stride, 
						   ShaderInterface *shader,
						   ShaderData *shaderData,
						   GLvoid *positionOffset,
						   GLvoid *normalOffset,
						   GLvoid *textureOffset,
						   TextureLoader *textureLoader)
:_mode(mode), _count(count), _stride(stride), _shader(shader), _positionOffset(positionOffset), _normalOffset(normalOffset),
_textureOffset(textureOffset), _shaderData(shaderData), _textureLoader(textureLoader)
{
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	configureVertexAttributes();
								
	_myRealVertices = new vector<ThreeVertices>();
	_myVertices = new vector<ThreeVertices>();
	loadVertices(data, size, stride);
}


vector <ThreeVertices>* VertexBuffer::getRealVertices()
{
	return _myRealVertices;
}



void VertexBuffer::loadRealVertices(mat4& model)
{
	_myRealVertices->clear();
	ThreeVertices data;
	vec3 point = vec3(0.0f);
	vec4 point4 = vec4(0.0f);

	int i = 0;
	int j = 0;

	for (vector<ThreeVertices>::iterator iterator = _myVertices->begin(); iterator != _myVertices->end(); iterator++)
	{

		data.a = iterator->a;
		point4 = model * vec4(data.a.x, data.a.y, data.a.z, 1.0f);
		data.a = vec3(point4) / point4.w;

		data.b = iterator->b;
		point4 = model * vec4(data.b.x, data.b.y, data.b.z, 1.0f);
		data.b = vec3(point4) / point4.w;

		data.c = iterator->c;
		point4 = model * vec4(data.c.x, data.c.y, data.c.z, 1.0f);
		data.c = vec3(point4) / point4.w;

		_myRealVertices->push_back(data);
	}
}




void VertexBuffer::loadVertices(GLvoid *table, GLsizeiptr size, GLsizeiptr dataSize)
{

		int nrOfVertices = 0;
		VertexDataP *dataP = nullptr;
		VertexDataPN *dataPN = nullptr;
		VertexDataPNT *dataPNT = nullptr;
	
	
		if (dataSize == sizeof(VertexDataPNT))
		{		
			dataPNT = static_cast<VertexDataPNT*>(table);
			nrOfVertices = size / (8 * sizeof(GLfloat));
		}
		else if (dataSize == sizeof(VertexDataPN))
		{
			dataPN = static_cast<VertexDataPN*>(table);
			nrOfVertices = size / (6*sizeof(GLfloat));
		}
		else if (dataSize == sizeof(VertexDataP))
		{
			dataP = static_cast<VertexDataP*>(table);
			nrOfVertices = size / (3*sizeof(GLfloat));
		}
		else
		{
			cout << "Wrong type of vertices" << endl;
		}
	
	
		ThreeVertices data;
		vec3 point = vec3(0.0f);
	
		
	
			int j = 0;
			for (int i = 0; i < nrOfVertices; i++)
			{
				if (j % 3 == 0)	j = 0;
	
				if (dataPNT != nullptr)
				{
					point.x = dataPNT[i].positionCoordinates.x;
					point.y = dataPNT[i].positionCoordinates.y;
					point.z = dataPNT[i].positionCoordinates.z;
				}
				else if (dataPN != nullptr)
				{
					point.x = dataPN[i].positionCoordinates.x;
					point.y = dataPN[i].positionCoordinates.y;
					point.z = dataPN[i].positionCoordinates.z;
				}
				else if (dataP != nullptr)
				{
					point.x = dataP[i].positionCoordinates.x;
					point.y = dataP[i].positionCoordinates.y;
					point.z = dataP[i].positionCoordinates.z;
				}
	
				if (j==0)
				{
					data.a = point;
					j++;
				}
				else if (j==1)
				{
					data.b = point;
					j++;
				}
				else
				{
					data.c = point;
					_myVertices->push_back(data);
					j++;
				}
			}
}



VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferID);
	_vertexBufferID = 0;
	//delete _myRealVertices;
	//delete _myVertices;
}

GLuint VertexBuffer::getVertexBufferID()
{
	return _vertexBufferID;
}


ShaderInterface* VertexBuffer::getShader()
{
	return _shader;
}

ShaderData* VertexBuffer::getShaderData()
{
	return _shaderData;
}

TextureLoader* VertexBuffer::getTextureLoader()
{
	return _textureLoader;
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

		if (_shader->get_aTextureCoord() != -1)
		{
			glEnableVertexAttribArray(_shader->get_aTextureCoord());
			glVertexAttribPointer(_shader->get_aTextureCoord(), 3, GL_FLOAT, GL_FLOAT, _stride, _textureOffset);
		}

		glBindVertexArray(0);
}


void VertexBuffer::renderVertexBuffer()
{	
	if (_textureLoader != NULL)
		_textureLoader->createTexture(_shader);
	
	glBindVertexArray(VAO);
	glDrawArrays(_mode, 0, _count);
	glBindVertexArray(0);
	
}