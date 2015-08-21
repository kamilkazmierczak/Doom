#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vector3;


Vector3 makeVector3(GLfloat x, GLfloat y, GLfloat z);