#include "EnemyIntelligence.h"


EnemyIntelligence::EnemyIntelligence() : _resetRotation(false)
{
}


EnemyIntelligence::~EnemyIntelligence()
{
}


void EnemyIntelligence::move(Entity* entity, GLfloat speed)
{

	if (_collisionTime + TimeToEscape < glfwGetTime())
	{
		//go to camera
		moveToCamera(entity, speed);
	}
	else
	{
		//go somewhere else
		moveSomewhere(entity, speed);
	}

	if (rand() % 200 + 1 <ShootingConstant)
	{
		shoot(entity);
	} 

}


void EnemyIntelligence::shoot(Entity* entity)
{
	ResourceManager *resourceManager = &ResourceManager::getResourceManager();
	RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();


	vec3 direction = vec3(entity->getMovementDirection().x, entity->getMovementDirection().y, entity->getMovementDirection().z);
	//tworzenie naboju 
	vec3 center = vec3(entity->getMovementDirection().x, entity->getMovementDirection().y, entity->getMovementDirection().z);
												//te 0.2 nie dziala idealnie bo teraz strzela z roznych miejsc
												//ale lepiej to wyglada niz ze srodka
												//jak bd czas zrob zeby zawsze strzelal z swojej broni
	vec3 position = vec3(entity->getPosition().x + 0.2f, entity->getPosition().y + 0.7f, entity->getPosition().z);

	//testy
	position = position + 0.8f * direction;

	IObject *sphere = new BulletObject(resourceManager->getBullet(),BU_ENEMY);

	Entity *newEntity = new Entity(sphere, makeVector3(position.x, position.y, position.z), ENTITY_BULLET);

	//GLfloat bulletSpeed = 0.008f;
	GLfloat max = std::max(std::abs(center.x), std::max(std::abs(center.y), std::abs(center.z)));

	if (max != 0)
	{
		newEntity->setVelocity(makeVector3((center.x / max)*BulletSpeed,
			(center.y / max)*BulletSpeed,
			(center.z / max)*BulletSpeed));
	}
	else
	{
		cout << "patrzysz na srodekk" << endl;
		//chyba
		newEntity->setVelocity(makeVector3(BulletSpeed, BulletSpeed, BulletSpeed));
	}

	renderSystem->getNewObjects()->push_back(newEntity);
}


void EnemyIntelligence::moveSomewhere(Entity* entity, GLfloat speed)
{
	vec2 u = vec2(0.0f, 1.0f);
	vec2 v = vec2(entity->getMovementDirection().x, entity->getMovementDirection().z);
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, angle, 0.0f));
	entity->setVelocity(_returnSpeed);
}



void EnemyIntelligence::moveToCamera(Entity* entity, GLfloat speed)
{

	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();

	//rotation
	vec2 oldVelocity = vec2(entity->getVelocity().x, entity->getVelocity().z);
	//#rotation
	vec2 cameraPosition = vec2(cameraSystem->getCurrentCamera()->getPosition().x, cameraSystem->getCurrentCamera()->getPosition().z);
	vec2 myPosition = vec2(entity->getPosition().x, entity->getPosition().z);
	vec2 direction = normalize(cameraPosition - myPosition);
	GLfloat max = std::max(std::abs(direction.x), std::abs(direction.y)); //y to tak naprawde z

	if (max != 0)
	{
		entity->setVelocity(makeVector3((direction.x / max) * speed,
			0.0f,
			(direction.y / max) * speed));
	}
	else
	{
		//chyba teraz patrze na srodek
		entity->setVelocity(makeVector3(speed, 0.0f, speed));
	}
	
	//teraz obrot
	if (!_resetRotation)
	{
		vec2 u = oldVelocity;
		vec2 v = vec2(entity->getVelocity().x, entity->getVelocity().z);
		GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
		entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	}
	else
	{
		//reset
		vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
		vec2 v = normalize(vec2(cameraPosition.x, cameraPosition.y) - vec2(entity->getPosition().x, entity->getPosition().z));
		GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
		entity->setRotation(makeVector3(0.0f, angle, 0.0f));
		_resetRotation = false;
	}
}


void EnemyIntelligence::moveWhenCollision(Entity *entity, GLfloat speed)
{
	vec2 movementDir = - vec2(entity->getMovementDirection().x, entity->getMovementDirection().z);
	vec2 oldVelocity = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat max = std::max(std::abs(movementDir.x), std::abs(movementDir.y)); //y to tak naprawde z


	if (max != 0)
	{
		entity->setVelocity(makeVector3((movementDir.x / max)  * speed,
										 0.0f,
										(movementDir.y / max)  * speed));
	}
	else
	{
		entity->setVelocity(makeVector3(speed, 0.0f, speed));
	}
	//fix rotation
	vec2 u = oldVelocity;
	vec2 v = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	_collisionTime = glfwGetTime();

	vec2 u2 = vec2(entity->getVelocity().x, entity->getVelocity().z);
	GLfloat angle2 = rand() % 90 + 1;

	if (rand() % 1 + 1 == 0)
		angle = -1 * angle;

	vec2 returnSpeed = -vec2(u2.x * cos(glm::radians(angle2)) - u2.y * sin(glm::radians(angle2)), u2.x * sin(glm::radians(angle2)) + u2.y * cos(glm::radians(angle2)));
	_returnSpeed = makeVector3(returnSpeed.x, 0.0f, returnSpeed.y);
	_resetRotation = true;



}