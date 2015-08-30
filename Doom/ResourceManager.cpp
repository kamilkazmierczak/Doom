#include "ResourceManager.h"
#include "TriangleVertices.h"
#include "CubeVertices.h"
#include "SkyboxVertices.h"
#include "FloorVertices.h"
#include "WallVertices.h"
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

	ShaderInterface *skyboxShader = new ShaderInterface("skybox.vs", "skybox.frag");
	_shaderArray->push_back(skyboxShader);

	ShaderInterface *lampShader = new ShaderInterface("lamp.vs", "lamp.frag");
	_shaderArray->push_back(lampShader);

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
												  sizeof(VertexDataP),
												  _shaderArray->at(0),
												  shaderData,
												  (GLvoid*)0,
												  NULL,
												  NULL,
												  NULL);
	_vertexBufferArray->push_back(vertexBuffer);

	//container
	textureLoader = new TextureLoader("container.png",TX_TEXTURE);
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
	    textureLoader = new TextureLoader("container2.jpg",TX_TEXTURE);
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

	
	//skybox
		   textureLoader = new TextureLoader(NULL,TX_SKYBOX);
			VertexBuffer *skyBox = new VertexBuffer(skyboxVertices,
												  sizeof(skyboxVertices), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataP) , 
												  _shaderArray->at(2),
												  shaderData, //useless ale inaczej bd bledy niepotrzebne, a nie chce mi sie zmieniac
												  (GLvoid *)0,					
												  NULL,
												  NULL,
												  textureLoader);
	_vertexBufferArray->push_back(skyBox);

		//floor
		   textureLoader = new TextureLoader("floor.png",TX_TEXTURE);
			VertexBuffer *floor = new VertexBuffer(floorVertices,
												  sizeof(floorVertices), 
												  GL_TRIANGLES, 
												  6, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(floor);
	
		//lamp
	VertexBuffer *lamp = new VertexBuffer(cubeVertices, 
												  sizeof(cubeVertices), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(3),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  NULL);
	_vertexBufferArray->push_back(lamp);

			//wall
	textureLoader = new TextureLoader("wall.jpg", TX_TEXTURE);
	VertexBuffer *wall = new VertexBuffer(wallVertices, 
												  sizeof(wallVertices), 
												  GL_TRIANGLES, 
												  6, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(wall);
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