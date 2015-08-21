#pragma once
#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ShaderData.h"

using namespace std;

class ResourceManager
{
private:
	vector<ShaderInterface *> *_shaderArray;
	vector<VertexBuffer *> *_vertexBufferArray;

	ShaderData *shaderData;

	ResourceManager();
	~ResourceManager();
public:
	
	vector<ShaderInterface *> *getShaderArray();
	vector<VertexBuffer *> *getVertexBufferArray();

	static ResourceManager& getResourceManager();
	static void destroyResourceManager();

};

