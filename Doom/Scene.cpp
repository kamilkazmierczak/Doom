#include "Scene.h"
#include "CameraSystem.h"
#include "ResourceManager.h"
#include "PlayerInputSystem.h"
#include "IObject.h"
#include "BulletObject.h"
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

	//triangle //testowy
	//entity = new Entity(resourceManager->getVertexBufferArray()->at(0), makeVector3(0.0f, 0.0f, 4.0f),ENTITY_TEST);
	////entity->setScale(makeVector3(2.0f, 2.0f, 2.0f));
	////entity->setRotationVelocity(makeVector3(0.0f, 1.0f, 1.0f));
	////entity->setVelocity(makeVector3(0.0f, 0.0f, -0.007f));
	////entity->setRotation(makeVector3(0.0f, 0.0f, 180.0f));
	//_children->push_back(entity);

	//container1 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(1), makeVector3(-8.7f, 0.6f, 1.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 0.0f, 90.0f));//to jest kat o jaki obrocic dla danej osi
	entity->setScale(makeVector3(0.6f, 0.6f, 0.6f));
	entity->setRotationVelocity(makeVector3(1.0f, 1.0f, 1.0f));
	_children->push_back(entity);

	//container2 //chyba
	entity = new Entity(resourceManager->getVertexBufferArray()->at(2), makeVector3(2.0f, -1.0f, 3.0f),ENTITY_MAP);
	entity->setScale(makeVector3(1.0f, 1.0f, 1.0f));
	_children->push_back(entity);
	
	//floor
	entity = new Entity(resourceManager->getVertexBufferArray()->at(4), makeVector3(0.0f, -1.0f, 0.0f),ENTITY_MAP);
	_children->push_back(entity);

	////lamp	
	Vector3 lightPosition1 = makeVector3(
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(0).position.x,
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(0).position.y,
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(0).position.z);

	entity = new Entity(resourceManager->getVertexBufferArray()->at(5), lightPosition1 ,ENTITY_MAP);
	entity->setScale(makeVector3(0.2f, 0.2f, 0.2f));
	_children->push_back(entity);

	////NEW IObject (testing)
	//sphere
	//IObject *sphere = new BulletObject(new Sphere(0.05f, 15, 15));
	//entity = new Entity(sphere, makeVector3(0.0f, -0.5f, -3.5f),ENTITY_BULLET);
	////entity->setScale(makeVector3(1.2f, 1.2f, 1.2f));
	//entity->setVelocity(makeVector3(0.0f, 0.0f, -0.008f));
	//_children->push_back(entity);

	//dalek1
	IObject *model = new ModelObject(resourceManager->getDalekArray()->at(0), new EnemyIntelligence());
	entity = new Entity(model, makeVector3(-5.0f, -1.5f, -8.5f), ENTITY_ENEMY);
	//entity = new Entity(model, makeVector3(0.0f, -1.5f, 0.0f), ENTITY_ENEMY);
	vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	vec2 v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	_children->push_back(entity);

	//dalek2
	model = new ModelObject(resourceManager->getDalekArray()->at(1), new EnemyIntelligence());
	entity = new Entity(model, makeVector3(5.0f, -1.5f, -8.5f), ENTITY_ENEMY);
	u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	_children->push_back(entity);




	//model - tardis
	/*model = new ModelObject(new Model("Models/tardis/TARDIS.obj"), NULL);
	entity = new Entity(model, makeVector3(8.7f, -1.5f, 8.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	entity->setScale(makeVector3(0.5f, 0.5f, 0.5f));
	_children->push_back(entity);*/

	//model - gun
	/*model = new ModelObject(new Model("Models/gun/freeze_gun.obj"), NULL);
	entity = new Entity(model, makeVector3(8.7f, -0.3f, -1.2f), ENTITY_MAP);
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	entity->setRotationVelocity(makeVector3(0.0f, -1.0f, 0.0f));
	_children->push_back(entity);*/

	//drewniana skrzynka
	/*model = new ModelObject(new Model("Models/woodenbox/Wooden_Box.obj"), NULL);
	entity = new Entity(model, makeVector3(8.7f, -1.5f, -1.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	entity->setScale(makeVector3(0.5f, 0.5f, 0.5f));
	_children->push_back(entity);*/

	//pudelko z nabojami
	/*model = new ModelObject(new Model("Models/ammobox/box.obj"), NULL);
	entity = new Entity(model, makeVector3(8.7f, -0.6f, -2.0f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -45.0f, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	_children->push_back(entity);*/
	
	//kartony
	/*model = new ModelObject(new Model("Models/boxes/untitled.obj"), NULL);
	entity = new Entity(model, makeVector3(-8.7f, -1.5f, +10.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -180.0f, 0.0f));
	entity->setScale(makeVector3(0.5f, 0.5f, 0.5f));
	_children->push_back(entity);*/

	//miecz
	/*model = new ModelObject(new Model("Models/sword/Sword.obj"), NULL);
	entity = new Entity(model, makeVector3(9.45f, -0.6f, -0.1f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 0.0f, 70.0f));
	entity->setScale(makeVector3(0.07f, 0.07f, 0.07f));
	_children->push_back(entity);*/

	//samolot (wczytuje sie 1,5min)
	//model = new ModelObject(new Model("Models/starcruiser/Starcruiser military.obj"), NULL);
	//entity = new Entity(model, makeVector3(-10.0f, 4.0f, 0.0f), ENTITY_MAP);
	//entity->setRotation(makeVector3(0.0f, 135.0f, 17.0f));
	//entity->setScale(makeVector3(0.02f, 0.02f, 0.02f));
	//entity->setVelocity(makeVector3(0.003f,0.0f,-0.003f));
	//_children->push_back(entity);

	//beczka
	/*model = new ModelObject(new Model("Models/b1/barrel.obj"), NULL);
	entity = new Entity(model, makeVector3(-8.7f, -1.5f, 1.5f), ENTITY_MAP);
	entity->setScale(makeVector3(0.6f, 0.6f, 0.6f));
	_children->push_back(entity);*/

	//lampa  z wielkim Bounding box
	//IObject *model = new ModelObject(new Model("Models/lampbb/Light Pole.obj"), NULL);
	//entity = new Entity(model, makeVector3(0.0f, 0.0f, 0.0f), ENTITY_MAP);
	//entity->setScale(makeVector3(0.3f, 0.3f, 0.3f));
	//_children->push_back(entity);

	//lampa 
	//IObject *model = new ModelObject(new Model("Models/lamp/little_brown_lamp.obj"), NULL);
	//entity = new Entity(model, makeVector3(0.0f, 0.0f, 0.0f), ENTITY_MAP);
	//entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	//_children->push_back(entity);

	//r2d2
	/*model = new ModelObject(new Model("Models/r2d2/untitled.obj"), NULL);
	entity = new Entity(model, makeVector3(0.0f, -1.5f, +13.8f), ENTITY_MAP);
	entity->setScale(makeVector3(0.7f, 0.7f, 0.7f));
	entity->setRotationVelocity(makeVector3(0.0f, 1.0f, 0.0f));
	_children->push_back(entity);*/

	//portal 1
	/*model = new ModelObject(new Model("Models/portalbutton/portalbutton.obj"), NULL);
	entity = new Entity(model, makeVector3(-5.0f, 0.9f, -8.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(-10.0f, 0.0f, 180.0f));
	entity->setScale(makeVector3(0.02f, 0.02f, 0.02f));
	_children->push_back(entity);*/

	//portal 2
	/*model = new ModelObject(new Model("Models/portalbutton/portalbutton.obj"), NULL);
	entity = new Entity(model, makeVector3(5.0f, 0.9f, -8.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(-10.0f, 0.0f, 180.0f));
	entity->setScale(makeVector3(0.02f, 0.02f, 0.02f));
	_children->push_back(entity);*/
	

	//WALLS
	////front wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(7), makeVector3(0.0f, 0.0f, -9.75f), ENTITY_MAP);
	_children->push_back(entity);
	////back wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(13), makeVector3(0.0f, 0.0f, +15.25f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 180.0f, 0.0f));
	_children->push_back(entity);

	//side walls (right)
	entity = new Entity(resourceManager->getVertexBufferArray()->at(14), makeVector3(10.0f, 0.0f, 0.0f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	_children->push_back(entity);
	//side walls (left)
	entity = new Entity(resourceManager->getVertexBufferArray()->at(8), makeVector3(-10.0f, 0.0f, 5.0f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 90.0f, 0.0f));
	_children->push_back(entity);

	////blocker prawej sciany
	entity = new Entity(resourceManager->getVertexBufferArray()->at(9), makeVector3(10.0f, -0.5f, 2.5f),ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	entity->setScale(makeVector3(25.0f, 0.1f, 0.1f));
	_children->push_back(entity);
	////blocker lewej sciany
	entity = new Entity(resourceManager->getVertexBufferArray()->at(10), makeVector3(-10.0f, -0.5f, 2.5f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, -90.0f, 0.0f));
	entity->setScale(makeVector3(25.0f, 0.1f, 0.1f));
	_children->push_back(entity);
	////blocker front wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(11), makeVector3(0.0f, -0.5f, -9.75f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));
	entity->setScale(makeVector3(20.0f, 0.1f, 0.1f));
	_children->push_back(entity);
	////blocker back wall
	entity = new Entity(resourceManager->getVertexBufferArray()->at(12), makeVector3(0.0f, -0.5f, 15.25f), ENTITY_MAP);
	entity->setRotation(makeVector3(0.0f, 0.0f, 0.0f));
	entity->setScale(makeVector3(20.0f, 0.1f, 0.1f));
	_children->push_back(entity);
	//WALLS END

	////lamp2		

	////lamp2  //SUN
	Vector3 lightPosition2 = makeVector3(
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(1).position.x,
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(1).position.y,
		resourceManager->getVertexBufferArray()->at(5)->getShaderData()->get_uLightArray()->at(1).position.z);

	entity = new Entity(resourceManager->getVertexBufferArray()->at(15), lightPosition2, ENTITY_MAP);
	//entity->setScale(makeVector3(0.2f, 0.2f, 0.2f));
	entity->setScale(makeVector3(3.2f, 3.2f, 3.2f));
	//potem ustaw na (tego i tak nie widac bo jest poza Skybox
	//entity->setScale(makeVector3(0.0f, 0.0f, 0.0f));

	_children->push_back(entity);


	//Camera *camera = new Camera(vec3(0.0f, 0.0f, 3.0f));
	Camera *camera = new Camera(CameraPosition);
	PlayerInputSystem *playerInputSystem = &PlayerInputSystem::getPlayerInputSystem();
	playerInputSystem->setCurrentCamera(camera);

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	cameraSystem->setCurrentCamera(camera);
	
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