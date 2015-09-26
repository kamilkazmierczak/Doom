#include "Vector3.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

Vector3 makeVector3(GLfloat x, GLfloat y, GLfloat z)
{
	Vector3 newVector;
	newVector.x = x;
	newVector.y = y;
	newVector.z = z;

	return newVector;
}


Vector3 addVector3(Vector3 vectorA, Vector3 VectorB)
{
	Vector3 newVector;
	newVector.x = vectorA.x + VectorB.x;
	newVector.y = vectorA.y + VectorB.y;
	newVector.z = vectorA.z + VectorB.z;

	return newVector;
}

Vector3 subtractVector3(Vector3 vectorA, Vector3 VectorB)
{
	Vector3 newVector;
	newVector.x = vectorA.x - VectorB.x;
	newVector.y = vectorA.y - VectorB.y;
	newVector.z = vectorA.z - VectorB.z;

	return newVector;
}


Vector3 normalizeVector3(Vector3 vector)
{	
	vec3 unitVector = normalize(vec3(vector.x, vector.y, vector.z));
	return  makeVector3(unitVector.x, unitVector.y, unitVector.z);
}

Vector3 crossProductVector3(Vector3 vectorA, Vector3 VectorB)
{
	vec3 newVector = cross(vec3(vectorA.x, vectorA.y, vectorA.z), vec3(VectorB.x, VectorB.y, VectorB.z));
	return makeVector3(newVector.x, newVector.y, newVector.z);
}

GLfloat dotProductVector3(Vector3 vectorA, Vector3 vectorB)
{
	return vectorA.x*vectorB.x + vectorA.y*vectorB.y + vectorA.z*vectorB.z;
}
