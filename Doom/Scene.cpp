#include "Scene.h"
#include "CameraSystem.h"
#include "ResourceManager.h"
#include "PlayerInputSystem.h"
#include "IObject.h"
#include "SphereObject.h"
#include "Sphere.h"
#include "ModelObject.h"
#include "Model.h"
#include "EnemyIntelligence.h"

using namespace glm;

Scene::Scene()
{
	_children = new vector<Entity *>();

	ResourceManager *resourceManager = &ResourceManager::getResourceManager();

	Entity *entity;

	//skybox (musi byc jako pierwszy)
	entity = new Entity(resourceManager->getVertexBufferArray()->at(3), makeVector3(NULL, NULL, NULL),ENTITY_MAP);
	_children->push_back(entity);

	//triangle //chyba
	//entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 1.5f, -5.0f));
	//entity->setVelocity(makeVector3(0.0f, 0.0f, 0.01f));
	//entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	//entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	//_children->push_back(entity);

	//triangle //chyba
	//entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 0.0f, 4.0f),ENTITY_TEST);
	////entity->setScale(makeVector3(2.0f, 2.0f, 2.0f));
	////entity->setRotationVelocity(makeVector3(0.0f, 1.0f, 1.0f));
	////entity->setVelocity(makeVector3(0.0f, 0.0f, -0.007f));
	////entity->setRotation(makeVector3(0.0f, 0.0f, 180.0f));
	//_children->push_back(entity);



	////container1 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(1), makeVector3(0.0f, 0.0f, -5.0f),ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));

	//niewiadomo dlaczego przy obrocie wzgledem z przy rejonach 180stopni lapie kolizje z modelem ktory jest
	//oddalony od niego o jakies 1.0f;
	//entity->setRotation(makeVector3(0.0f, 0.0f, 180.0f));
	//entity->setRotationVelocity(makeVector3(0.0f, 0.0f, 1.0f));
	//entity->setScaleVelocity(makeVector3(0.001f, 0.0f, 0.0f));
	_children->push_back(entity);

	//
	////container2 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(2), makeVector3(2.0f, -1.0f, 3.0f),ENTITY_MAP);
	//entity->setRotation(makeVector3(10.0f, 0.0f, 0.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	//entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	_children->push_back(entity);
	//
	//floor
	entity = new Entity(resourceManager->getVertexBufferArray()->at(4), makeVector3(0.0f, -1.0f, 0.0f),ENTITY_MAP);
	_children->push_back(entity);

	//lamp																	
	entity = new Entity(resourceManager->getVertexBufferArray()->at(5), resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightPosition(),ENTITY_MAP);
	entity->setScale(makeVector3(0.2f, 0.2f, 0.2f));
	_children->push_back(entity);

	//wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(6), makeVector3(0.0f, -1.0f, 8.0f),ENTITY_MAP);
	entity->setRotation(makeVector3(-90.0f, 0.0f, 0.0f));
	_children->push_back(entity);


	////NEW IObject (testing)
	//sphere
	//IObject *sphere = new SphereObject(new Sphere(0.05f, 15, 15));
	//entity = new Entity(sphere, makeVector3(0.0f, -0.5f, -3.5f),ENTITY_BULLET);
	////entity->setScale(makeVector3(1.2f, 1.2f, 1.2f));
	//entity->setVelocity(makeVector3(0.0f, 0.0f, -0.008f));
	//_children->push_back(entity);

	//model
	IObject *model = new ModelObject(new Model("dalek/Dalek.obj"), new EnemyIntelligence());
	entity = new Entity(model, makeVector3(-5.0f, -1.0f, 0.0f), ENTITY_ENEMY);
	//entity->setRotationVelocity(makeVector3(0.0f, 1.0f, 0.0f));
	//entity->setVelocity(makeVector3(0.0f, 0.0f, 0.009f));
	vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	vec2 v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));



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