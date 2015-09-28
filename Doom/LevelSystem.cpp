#include "LevelSystem.h"



LevelSystem::LevelSystem() :_currentLevel(1), _maxLevel(10), _shootingVariable(10.0f), _finalRound(false)
{
}


LevelSystem::~LevelSystem()
{
}


void LevelSystem::setLevel(GLuint level)
{
	if (level != _maxLevel + 1)
	{
		_currentLevel = level;
		_shootingVariable = level * ShootingMultiplier;
	}
	else
	{
		_finalRound = true;
	}
}

GLfloat LevelSystem::getShootingVariable()
{
	return _shootingVariable;
}

GLuint LevelSystem::getCurrentLevel()
{
	return _currentLevel;
}

GLuint LevelSystem::getMaxLevel()
{
	return _maxLevel;
}

bool LevelSystem::getFinalRoundStatus()
{
	return _finalRound;
}


LevelSystem& LevelSystem::getLevelSystem()
{
	static LevelSystem *levelSystem = NULL;

	if (levelSystem == NULL){
		levelSystem = new LevelSystem();
	}

	return *levelSystem;
}

void LevelSystem::destroyLevelSystem()
{
	LevelSystem *levelSystem = &getLevelSystem();
	delete levelSystem;
}