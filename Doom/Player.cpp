#include "Player.h"


Player::Player() : _health(100.0f)
{	
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	_cameraSystem = cameraSystem;
}


Player::~Player()
{
}


Vector3 Player::getPosiion()
{	
	return makeVector3(_cameraSystem->getCurrentCamera()->getPosition().x, 
					   _cameraSystem->getCurrentCamera()->getPosition().y, 
					   _cameraSystem->getCurrentCamera()->getPosition().z);
}



Player& Player::getPlayer()
{
	static Player *resourceManager = NULL;

	if (resourceManager == NULL){
		resourceManager = new Player();
	}

	return *resourceManager;
}

void Player::destroyPlayer()
{
	Player *player = &getPlayer();
	delete player;
}