#pragma once
//#include "GameManager.h"
#include "CameraSystem.h"
#include "Player.h"
#include "ModelObject.h"
#include "EnemyIntelligence.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

class EnvironmentReactions
{
private:

	void takeAmmo();
	void createWave();

	int _deadDalekNumber;
	
	bool _allEnemyDead;
	bool _resetInformation;

	EnvironmentReactions();
	~EnvironmentReactions();

public:

	void react();
	void countDalek();
	bool getAllEnemyDeadStatus();
	void resetInformation();

	static EnvironmentReactions& getEnvironmentReactions();
	static void destroyEnvironmentReactions();
};

