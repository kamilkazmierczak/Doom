#include "Scene.h"
#include "CameraSystem.h"
#include "ResourceManager.h"
#include "PlayerInputSystem.h"

using namespace glm;

Scene::Scene()
{
	_children = new vector<Entity *>();

	ResourceManager *resourceManager = &ResourceManager::getResourceManager();

	Entity *entity = new Entity(resourceManager->getVertexBufferArray()->at(1), makeVector3(0.0f, 0.0f, -5.0f));
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setScaleVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	_children->push_back(entity);

	
	entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 1.5f, -5.0f));
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	_children->push_back(entity);


	entity = new Entity(resourceManager->getVertexBufferArray()->at(2), makeVector3(0.0f, -1.5f, -5.0f));
	entity->setRotation(makeVector3(45.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity2->setRotationVelocity(makeVector3(0.0f, 0.0f, 0.0f));
	_children->push_back(entity);


	

	Camera *camera = new Camera(vec3(0.0f, 0.0f, 3.0f));
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