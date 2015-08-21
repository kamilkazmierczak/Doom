#include "ResourceManager.h"
#include "TriangleVertices.h"
#include "CubeVertices.h"

vector<ShaderInterface *>* ResourceManager::getShaderArray()
{
	return _shaderArray;
}

vector<VertexBuffer *>* ResourceManager::getVertexBufferArray()
{
	return _vertexBufferArray;
}


ResourceManager::ResourceManager()
{
	//Shaders
	_shaderArray = new vector<ShaderInterface *>();
	ShaderInterface *shader = new ShaderInterface("ColorShader.vs", "ColorShader.frag");
	_shaderArray->push_back(shader);

	ShaderInterface *lightShader = new ShaderInterface("SimpleLightShader.vs", "SimpleLightShader.frag");
	_shaderArray->push_back(lightShader);

	//VertexBuffers
	_vertexBufferArray = new vector<VertexBuffer *>();

			VertexBuffer *vertexBuffer = new VertexBuffer(vertices, 
												  sizeof(vertices), 
												  GL_TRIANGLES, 
												  3, 
												  sizeof(GLfloat) * 3, 
												  _shaderArray->at(0),
												  (GLvoid*)0,
												  (GLvoid*)0);
	_vertexBufferArray->push_back(vertexBuffer);

	VertexBuffer *cubeVertexBuffer = new VertexBuffer(cubeVertices, 
												  sizeof(cubeVertices), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPN) , 
												  _shaderArray->at(1),
												  (GLvoid *)(offsetof(VertexDataPN, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPN, normalCoordinates)));
	_vertexBufferArray->push_back(cubeVertexBuffer);




}


ResourceManager::~ResourceManager()
{
	for (vector<ShaderInterface *>::iterator iterator = _shaderArray->begin(); iterator != _shaderArray->end(); iterator++){
		delete *iterator;
	} 
	delete _shaderArray;


	for (vector<VertexBuffer *>::iterator iterator = _vertexBufferArray->begin(); iterator != _vertexBufferArray->end(); iterator++){
		delete *iterator;
	}
	delete _vertexBufferArray;
}


ResourceManager& ResourceManager::getResourceManager()
{
	static ResourceManager *resourceManager = NULL;

	if (resourceManager == NULL){
		resourceManager = new ResourceManager();
	}

	return *resourceManager;
}

void ResourceManager::destroyResourceManager()
{
	ResourceManager *resourceManager = &getResourceManager();
	delete resourceManager;
}