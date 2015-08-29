#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

typedef struct {
	GLfloat x;
	GLfloat y;
} Vector2;

Vector2 makeVector2(GLfloat x, GLfloat y);