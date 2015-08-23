#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class Scene
{
private:
	vector<Entity *> *_children;

public:
	vector<Entity *> *getChildren();


	Scene();
	~Scene();
};

