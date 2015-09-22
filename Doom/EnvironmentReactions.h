#pragma once
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

	EnvironmentReactions();
	~EnvironmentReactions();

public:

	void react();
	void countDalek();
	bool getAllEnemyDeadStatus();


	static EnvironmentReactions& getEnvironmentReactions();
	static void destroyEnvironmentReactions();
};

