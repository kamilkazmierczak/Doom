#include "ResourceManager.h"
#include "TriangleVertices.h"
#include "CubeVertices.h"
#include "SkyboxVertices.h"
#include "FloorVertices.h"
#include "WallVertices.h"
#include "WallVertices2.h"
#include "BBVertices.h"
#include "Entity.h"
#include "Test.h"
#include "Constants.h"


#include <typeinfo>


vector<ShaderInterface *>* ResourceManager::getShaderArray()
{
	return _shaderArray;
}

vector<VertexBuffer *>* ResourceManager::getVertexBufferArray()
{
	return _vertexBufferArray;
}


Sphere* ResourceManager::getBullet()
{
	return _bullet;
}

vector<Model*>* ResourceManager::getDalekArray()
{
	return _dalekArray;
}


ResourceManager::ResourceManager()
{

	_bullet = new Sphere(BulletRadius, 15, 15);
	_dalekArray = new vector<Model*>();

	for (int i = 0; i < NumberOfDaleks; i++)
	{
		_dalekArray->push_back(new Model("Models/dalek/Dalek.obj"));
	}


	//Shaders
	_shaderArray = new vector<ShaderInterface *>();
	ShaderInterface *shader = new ShaderInterface("Shaders/ColorShader.vs", "Shaders/ColorShader.frag");
	_shaderArray->push_back(shader);

	ShaderInterface *lightShader = new ShaderInterface("Shaders/LightShader.vs", "Shaders/LightShader.frag");
	_shaderArray->push_back(lightShader);

	ShaderInterface *skyboxShader = new ShaderInterface("Shaders/Skybox.vs", "Shaders/Skybox.frag");
	_shaderArray->push_back(skyboxShader);

	ShaderInterface *lampShader = new ShaderInterface("Shaders/Lamp.vs", "Shaders/Lamp.frag");
	_shaderArray->push_back(lampShader);
												
	Light light1;
	light1.position = vec3(2.0f, -0.23f, 3.0f);
	light1.ambient = vec3(0.4f, 0.4f, 0.4f);
	light1.diffuse = vec3(0.5f, 0.5f, 0.5f);
	light1.specular = vec3(0.3f, 0.3f, 0.3f);

	Light sun;
	sun.position = vec3(0.0f, 60.0f, -120.0f);
	sun.ambient = vec3(0.05f, 0.05f, 0.05f);
	sun.diffuse = vec3(0.2f, 0.2f, 0.2f);
	sun.specular = vec3(0.5f, 0.5f, 0.5f);


	Material material;
	material.specular = vec3(0.5f, 0.5f, 0.5f);
	material.shininess = 32.0f;

	vector<Light> *lights = new vector<Light>();
	lights->push_back(light1);
	lights->push_back(sun);

	//1
	shaderData = new ShaderData(lights, material, makeVector4(0.0f, 0.0f, 1.0f, 1.0f));

	TextureLoader *textureLoader; 
	_vertexBufferArray = new vector<VertexBuffer *>();



	//trojkat 
	vector <ThreeVertices> *myVertices = new vector<ThreeVertices>();
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
	textureLoader = new TextureLoader("Textures/container.png",TX_TEXTURE);
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
	    textureLoader = new TextureLoader("Textures/container2.jpg",TX_TEXTURE);
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
												  shaderData,
												  (GLvoid *)0,					
												  NULL,
												  NULL,
												  textureLoader);
	_vertexBufferArray->push_back(skyBox);

		//floor
		    textureLoader = new TextureLoader("Textures/floor_tiles.jpg",TX_TEXTURE);
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
	textureLoader = new TextureLoader("Textures/wall.jpg", TX_TEXTURE);
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


				//wallfront
	textureLoader = new TextureLoader("Textures/wall.jpg", TX_TEXTURE);
	VertexBuffer *wall2 = new VertexBuffer(wallVerticesfront, 
												  sizeof(wallVerticesfront), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(wall2);

					//wall left
	textureLoader = new TextureLoader("Textures/wall4.jpg", TX_TEXTURE);
	VertexBuffer *wall3 = new VertexBuffer(wallVerticesSide, 
												  sizeof(wallVerticesSide), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(wall3);


		  //right blocker 
	    textureLoader = new TextureLoader("Textures/container2.jpg",TX_TEXTURE);
		VertexBuffer *rightBlocker = new VertexBuffer(cubeVertices, 
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
		_vertexBufferArray->push_back(rightBlocker);

			//left blocker
	    textureLoader = new TextureLoader("Textures/container2.jpg",TX_TEXTURE);
		VertexBuffer *leftBlocker = new VertexBuffer(cubeVertices, 
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
		_vertexBufferArray->push_back(leftBlocker);

			//front blocker
	    textureLoader = new TextureLoader("Textures/container2.jpg",TX_TEXTURE);
		VertexBuffer *frontBlocker = new VertexBuffer(cubeVertices, 
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
		_vertexBufferArray->push_back(frontBlocker);

			//back blocker
	    textureLoader = new TextureLoader("Textures/container2.jpg",TX_TEXTURE);
		VertexBuffer *backBlocker = new VertexBuffer(cubeVertices, 
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
		_vertexBufferArray->push_back(backBlocker);



			textureLoader = new TextureLoader("Textures/wall.jpg", TX_TEXTURE);
	VertexBuffer *wallback = new VertexBuffer(wallVerticesfront, 
												  sizeof(wallVerticesfront), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(wallback);

						//wall right
	textureLoader = new TextureLoader("Textures/wall4.jpg", TX_TEXTURE);
	VertexBuffer *wallright = new VertexBuffer(wallVerticesSide, 
												  sizeof(wallVerticesSide), 
												  GL_TRIANGLES, 
												  36, 
												  sizeof(VertexDataPNT) , 
												  _shaderArray->at(1),
												  shaderData,
												  (GLvoid *)(offsetof(VertexDataPNT, positionCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, normalCoordinates)),
												  (GLvoid *)(offsetof(VertexDataPNT, textureCoordinates)),
												  textureLoader);
	_vertexBufferArray->push_back(wallright);

	//lamp2
		VertexBuffer *lamp2 = new VertexBuffer(cubeVertices, 
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
	_vertexBufferArray->push_back(lamp2);
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

