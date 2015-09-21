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

	//temporary (potem to jakos inaczej zrob)
	Sphere *_bullet;
	vector<Model*> *_dalekArray;
	//void loadVertices(GLvoid *table, GLsizeiptr size, vector<ThreeVertices>*Vertices, GLsizeiptr dataSize);

	ResourceManager();
	~ResourceManager();
public:
	
	vector<ShaderInterface *> *getShaderArray();
	vector<VertexBuffer *> *getVertexBufferArray();

	//temporary (potem to jakos inaczej zrob)
	Sphere *getBullet();
	vector<Model*> *getDalekArray();
	

	static ResourceManager& getResourceManager();
	static void destroyResourceManager();

};

