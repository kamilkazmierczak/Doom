#include "Scene.h"
#include "CameraSystem.h"
#include "ResourceManager.h"
#include "PlayerInputSystem.h"
#include "IObject.h"
#include "SphereObject.h"
#include "Sphere.h"
#include "ModelObject.h"
#include "Model.h"

using namespace glm;

Scene::Scene()
{
	_children = new vector<Entity *>();

	ResourceManager *resourceManager = &ResourceManager::getResourceManager();

	//skybox (musi byc jako pierwszy)
	Entity *entity = new Entity(resourceManager->getVertexBufferArray()->at(3), makeVector3(NULL, NULL, NULL));
	_children->push_back(entity);

	//triangle //chyba
	//entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 1.5f, -5.0f));
	//entity->setVelocity(makeVector3(0.0f, 0.0f, 0.01f));
	//entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	//entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	//_children->push_back(entity);

	//triangle //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 0.0f, 6.0f));
	entity->setScale(makeVector3(2.0f, 2.0f, 2.0f));
	_children->push_back(entity);



	//container1 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(1), makeVector3(0.0f, 0.0f, -5.0f));
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setScaleVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	_children->push_back(entity);
	
	//container2 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(2), makeVector3(0.0f, -1.5f, -5.0f));
	entity->setRotation(makeVector3(45.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity2->setRotationVelocity(makeVector3(0.0f, 0.0f, 0.0f));
	_children->push_back(entity);
	
	//floor
	entity = new Entity(resourceManager->getVertexBufferArray()->at(4), makeVector3(0.0f, -1.0f, 0.0f));
	_children->push_back(entity);

	//lamp																	
	entity = new Entity(resourceManager->getVertexBufferArray()->at(5), resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightPosition());
	entity->setScale(makeVector3(0.2f, 0.2f, 0.2f));
	_children->push_back(entity);

	//wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(6), makeVector3(0.0f, -1.0f, 8.0f));
	entity->setRotation(makeVector3(-90.0f, 0.0f, 0.0f));
	_children->push_back(entity);


	//NEW IObject (testing)
	//sphere
	IObject *sphere = new SphereObject(new Sphere(0.05f, 15, 15));
	entity = new Entity(sphere, makeVector3(0.0f, 0.0f, 5.2f));
	entity->setScale(makeVector3(1.2f, 1.2f, 1.2f));
	entity->setVelocity(makeVector3(0.0f, 0.0f, 0.004f));
	_children->push_back(entity);

	//model
	IObject *model = new ModelObject(new Model("dalek/Dalek.obj"));
	entity = new Entity(model, makeVector3(0.0f, -1.5f, -2.0f));
	entity->setRotationVelocity(makeVector3(0.0f, 1.0f, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	_children->push_back(entity);

	//Camera *camera = new Camera(vec3(0.0f, 0.0f, 3.0f));
	Camera *camera = new Camera(CameraPosition);
	PlayerInputSystem *playerInputSystem = &PlayerInputSystem::getPlayerInputSystem();
	playerInputSystem->setCurrentCamera(camera);

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	cameraSystem->setCurrentCamera(camera);
	


	/*
	Entity *camera = new Entity(NULL, makeVector3(1.0f, 1.0f, 2.0f));
	camera->setEyeVector(normalizeVector3(makeVector3(-1.0f, -1.0f, -1.0f)));
	camera->setUpVector(normalizeVector3(makeVector3(0.0f, 1.0f, 0.0f)));


	PlayerInputSystem *playerInputSystem = &PlayerInputSystem::getPlayerInputSystem();
	playerInputSystem->setCurrentPlayer(camera);

	_children->push_back(camera);

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	cameraSystem->setCurrentCamera(camera);
	*/ //tu sie zrobil problem
}


Scene::~Scene()
{
	for (vector<Entity *>::iterator iterator = _children->begin(); iterator != _children->end() ; iterator++)
	{
		delete *iterator;
	}
	delete _children;
}


vector<Entity *>* Scene::getChildren()
{
	return _children;
}