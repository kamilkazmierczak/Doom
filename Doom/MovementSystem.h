#pragma once
#include "Entity.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

class MovementSystem
{
private:
	MovementSystem();
	~MovementSystem();

public:
	static MovementSystem& getMovementSystem();
	static void destroyMovementSystem();

	void update(vector<Entity *> *entityArray);
};

