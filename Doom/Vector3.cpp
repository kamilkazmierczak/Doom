#include "Vector3.h"

Vector3 makeVector3(GLfloat x, GLfloat y, GLfloat z)
{
	Vector3 newVector;
	newVector.x = x;
	newVector.y = y;
	newVector.z = z;

	return newVector;
}