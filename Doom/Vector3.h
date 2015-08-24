#pragma once
#include <iostream>
#include "Matrix3.h"
#include <GLFW/glfw3.h>

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vector3;


Vector3 makeVector3(GLfloat x, GLfloat y, GLfloat z);
Vector3 addVector3(Vector3 vectorA, Vector3 VectorB);
Vector3 subtractVector3(Vector3 vectorA, Vector3 VectorB);
Vector3 normalizeVector3(Vector3 vector);
Vector3 scalerMultiplyVector3(Vector3 vectorToMultiply, GLfloat scalerValue);
Vector3 crossProductVector3(Vector3 vectorA, Vector3 VectorB);
GLfloat dotProductVector3(Vector3 vectorA, Vector3 vectorB);
Vector3 transformVector3(Vector3 vector, Matrix3 transformationMatrix);