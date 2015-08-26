#pragma once
#include "Entity.h"
#include <vector>

#include <GLFW/glfw3.h>



class Scene
{
private:
	vector<Entity *> *_children;

public:
	vector<Entity *> *getChildren();


	Scene();
	~Scene();
};

