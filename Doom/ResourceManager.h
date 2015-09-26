#pragma once
#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include "ShaderData.h"
#include "Sphere.h"
#include "Model.h"

using namespace std;

class ResourceManager
{
private:
	vector<ShaderInterface *> *_shaderArray;
	vector<VertexBuffer *> *_vertexBufferArray;
	ShaderData *shaderData;

	Sphere *_bullet;
	vector<Model*> *_dalekArray;

	ResourceManager();
	~ResourceManager();
public:
	
	vector<ShaderInterface *> *getShaderArray();
	vector<VertexBuffer *> *getVertexBufferArray();

	Sphere *getBullet();
	vector<Model*> *getDalekArray();
	
	static ResourceManager& getResourceManager();
	static void destroyResourceManager();

};

