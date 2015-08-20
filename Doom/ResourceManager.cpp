#include "ResourceManager.h"

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
	_shaderArray = new vector<ShaderInterface *>();
	_vertexBufferArray = new vector<VertexBuffer *>();
}


ResourceManager::~ResourceManager()
{
	delete _shaderArray;
	delete _vertexBufferArray;
}


ResourceManager& ResourceManager::getResourceManager()
{
	ResourceManager *resourceManager = NULL;

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