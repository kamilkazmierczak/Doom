#pragma once
#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"

using namespace std;

class ResourceManager
{
private:
	vector<ShaderInterface *> *_shaderArray;
	vector<VertexBuffer *> *_vertexBufferArray;

	ResourceManager();
	~ResourceManager();
public:
	
	vector<ShaderInterface *> *getShaderArray();
	vector<VertexBuffer *> *getVertexBufferArray();

	static ResourceManager& getResourceManager();
	static void destroyResourceManager();

};

