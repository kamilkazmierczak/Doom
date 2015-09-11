#pragma once
#define GLM_FORCE_RADIANS
// GLFW
#include <iostream>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

using namespace std;
using namespace glm;

class Sphere
{
private:

	float _radius;
	int _slices, _stacks;

	void makeVertices();
	void makeIndices();
	vector <vec3> _vertices;
	vector <GLuint> _indices;


public:
	Sphere(float radius, int slices, int stacks);
	~Sphere();
	
	void test();

	vector <vec3> getVertives();
	vector <GLuint> getIndices();

	int GetTotalVertices();
	int GetTotalIndices();
};

