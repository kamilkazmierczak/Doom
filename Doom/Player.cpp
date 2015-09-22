#include "Player.h"


Player::Player() : _health(100.0f), _ammo(MaxAmmo)
{	
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	_cameraSystem = cameraSystem;
}


Player::~Player()
{
}


Vector3 Player::getPosition()
{	
	return makeVector3(_cameraSystem->getCurrentCamera()->getPosition().x, 
					   _cameraSystem->getCurrentCamera()->getPosition().y, 
					   _cameraSystem->getCurrentCamera()->getPosition().z);
}


GLfloat Player::getHealth()
{
	return _health;
}

void Player::changeHealth(GLfloat change)
{
	if (_health+change < 0)
	{
		_health = 0.0f;
	}else
	{
		_health += change;
	}
}

GLfloat Player::getAmmo()
{
	return _ammo;
}

void Player::setAmmo(GLfloat newAmmo)
{
	if (_ammo + newAmmo >MaxAmmo)
	{
		_ammo = MaxAmmo;
	}
	else
	{
		_ammo += newAmmo;
	}	
}


Player& Player::getPlayer()
{
	static Player *player = NULL;

	if (player == NULL){
		player = new Player();
	}

	return *player;
}

void Player::destroyPlayer()
{
	Player *player = &getPlayer();
	delete player;
}