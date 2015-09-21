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
	ShaderInterface *shader = new ShaderInterface("ColorShader.vs", "ColorShader.frag");
	_shaderArray->push_back(shader);

	ShaderInterface *lightShader = new ShaderInterface("SimpleLightShader.vs", "SimpleLightShader.frag");
	_shaderArray->push_back(lightShader);

	ShaderInterface *skyboxShader = new ShaderInterface("skybox.vs", "skybox.frag");
	_shaderArray->push_back(skyboxShader);

	ShaderInterface *lampShader = new ShaderInterface("lamp.vs", "lamp.frag");
	_shaderArray->push_back(lampShader);
												
	Light light1;
	light1.position = vec3(0.0f, 2.0f, 5.0f);
	light1.ambient = vec3(0.2f, 0.2f, 0.2f);
	light1.diffuse = vec3(0.5f, 0.5f, 0.5f);
	light1.specular = vec3(0.5f, 0.5f, 0.5f);
	//light.ambient = vec3(0.05f, 0.05f, 0.05f);
	//light.diffuse = vec3(1.0f, 1.0f, 1.0f);
	//light.specular = vec3(1.0f, 1.0f, 1.0f);

	//light2
	Light light2;
	light2.position = vec3(0.0f, 2.0f, -6.0f);
	light2.ambient = vec3(0.2f, 0.2f, 0.2f);
	light2.diffuse = vec3(0.5f, 0.5f, 0.5f);
	light2.specular = vec3(0.5f, 0.5f, 0.5f);
	//light.ambient = vec3(0.05f, 0.05f, 0.05f);
	//light.diffuse = vec3(1.0f, 1.0f, 1.0f);
	//light.specular = vec3(1.0f, 1.0f, 1.0f);

	Material material;
	//material.specular = vec3(0.5f, 0.5f, 0.5f);
	material.specular = vec3(0.0f, 0.0f, 0.0f);
	material.shininess = 32.0f;

	vector<Light> *lights = new vector<Light>();
	lights->push_back(light1);
	lights->push_back(light2);


	//1
	shaderData = new ShaderData(lights, material, makeVector4(0.0f, 0.0f, 1.0f, 1.0f));


	//VertexBuffers
	//zasadniczo mozna by to przeniesc do zmiennej klasy ale potem by trzeba bylo robic
	//delete przed kazdym nowym - chyba i tak bd trzeba + dla shaderData bd podobny problem
	//bo aktualnie wszystkie obiekty uzywaja tego samego
	
	TextureLoader *textureLoader; 
	_vertexBufferArray = new vector<VertexBuffer *>();



	//trojkat 
	vector <ThreeVertices> *myVertices = new vector<ThreeVertices>();
	//loadVertices(verticesTest, sizeof(verticesTest), myVertices, sizeof(VertexDataP));
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
	    textureLoader = new TextureLoader("container2.jpg",TX_TEXTURE);
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
	    textureLoader = new TextureLoader("container2.jpg",TX_TEXTURE);
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
	    textureLoader = new TextureLoader("container2.jpg",TX_TEXTURE);
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
	    textureLoader = new TextureLoader("container2.jpg",TX_TEXTURE);
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


//
//void ResourceManager::loadVertices(GLvoid *table, GLsizeiptr size, vector<ThreeVertices>*Vertices, GLsizeiptr dataSize)
//{
//	//type = type.substr(0, type.find_last_of(' '));
//	int nrOfVertices = 0;
//	VertexDataP *dataP = nullptr;
//	VertexDataPN *dataPN = nullptr;
//	VertexDataPNT *dataPNT = nullptr;
//
//
//	if (dataSize == sizeof(VertexDataPNT))
//	{
//		//VertexDataPNT *data = static_cast<VertexDataPNT*>(table);
//		dataPNT = static_cast<VertexDataPNT*>(table);
//		nrOfVertices = size / (8 * sizeof(GLfloat));
//		//cout << nrOfVertices << endl;
//		cout << "PNT" << endl;
//	}
//	else if (dataSize == sizeof(VertexDataPN))
//	{
//		//VertexDataPN *data = static_cast<VertexDataPN*>(table);
//		dataPN = static_cast<VertexDataPN*>(table);
//		nrOfVertices = size / (6*sizeof(GLfloat));
//		//cout << nrOfVertices << endl;
//		cout << "PN" << endl;
//	}
//	else if (dataSize == sizeof(VertexDataP))
//	{
//		//VertexDataP *data = static_cast<VertexDataP*>(table);
//		dataP = static_cast<VertexDataP*>(table);
//		nrOfVertices = size / (3*sizeof(GLfloat));
//		//cout << nrOfVertices << endl;
//		cout << "P" << endl;
//	}
//	else
//	{
//		cout << "Wrong type of vertices" << endl;
//	}
//
//
//	ThreeVertices data;
//	vec3 point = vec3(0.0f);
//
//	
//
//		int j = 0;
//		for (int i = 0; i < nrOfVertices; i++)
//		{
//			if (j % 3 == 0)	j = 0;
//
//
//			//wez to jakos ogarnij pozniej bo nie potrzebnie sprawdza tyle razy warunek moze to zrobic raz
//			if (dataPNT != nullptr)
//			{
//				point.x = dataPNT[i].positionCoordinates.x;
//				point.y = dataPNT[i].positionCoordinates.y;
//				point.z = dataPNT[i].positionCoordinates.z;
//			}
//			else if (dataPN != nullptr)
//			{
//				point.x = dataPN[i].positionCoordinates.x;
//				point.y = dataPN[i].positionCoordinates.y;
//				point.z = dataPN[i].positionCoordinates.z;
//			}
//			else if (dataP != nullptr)
//			{
//				point.x = dataP[i].positionCoordinates.x;
//				point.y = dataP[i].positionCoordinates.y;
//				point.z = dataP[i].positionCoordinates.z;
//			}
//
//			if (j==0)
//			{
//				data.a = point;
//				j++;
//			}
//			else if (j==1)
//			{
//				data.b = point;
//				j++;
//			}
//			else
//			{
//				data.c = point;
//				Vertices->push_back(data);
//				j++;
//			}
//		}
//	
//	
//	for (vector<ThreeVertices>::iterator iterator = Vertices->begin(); iterator != Vertices->end(); iterator++)
//	{
//		cout << iterator->a.x << endl;
//		cout << iterator->a.y << endl;
//		cout << iterator->a.z << endl;
//		cout << "##" << endl;
//		cout << iterator->b.x << endl;
//		cout << iterator->b.y << endl;
//		cout << iterator->b.z << endl;
//		cout << "##" << endl;
//		cout << iterator->c.x << endl;
//		cout << iterator->c.y << endl;
//		cout << iterator->c.z << endl;
//		cout << "##" << endl;
//	}
//}
