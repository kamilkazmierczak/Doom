#include "ResourceManager.h"
#include "TriangleVertices.h"
#include "CubeVertices.h"
#include "Entity.h"

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

	shaderData = new ShaderData(makeVector4(0.0f, 0.0f, 1.0f, 1.0f), makeVector3(0.0f, 0.0f, 1.0f));


	//VertexBuffers
	//zasadniczo mozna by to przeniesc do zmiennej klasy ale potem by trzeba bylo robic
	//delete przed kazdym nowym - chyba i tak bd trzeba + dla shaderData bd podobny problem
	//bo aktualnie wszystkie obiekty uzywaja tego samego
	
	TextureLoader *textureLoader; 
	_vertexBufferArray = new vector<VertexBuffer *>();

	//trojkat
			VertexBuffer *vertexBuffer = new VertexBuffer(vertices, 
												  sizeof(vertices), 
												  GL_TRIANGLES, 
												  3, 
												  sizeof(GLfloat) * 3, 
												  _shaderArray->at(0),
												  shaderData,
												  (GLvoid*)0,
												  (GLvoid*)0,
												  (GLvoid*)0,
												  NULL);
	_vertexBufferArray->push_back(vertexBuffer);

	//container
	textureLoader = new TextureLoader("container.png");
	VertexBuffer *cubeVertexBuffer = new VertexBuffer(cubeVertices, 
												  sizeof(cubeVertices), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(cubeVertexBuffer);

	//container2
	    textureLoader = new TextureLoader("container2.jpg");
		VertexBuffer *cubeVertexBuffer2 = new VertexBuffer(cubeVertices, 
												  sizeof(cubeVertices), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(cubeVertexBuffer2);




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

	delete shaderData;
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