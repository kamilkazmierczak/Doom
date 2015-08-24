#include "Vector3.h"
#include <math.h>
// GLM Mathematics
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
{//mozna by to bylo przeciazyc
	Vector3 newVector;
	newVector.x = vectorA.x + VectorB.x;
	newVector.y = vectorA.y + VectorB.y;
	newVector.z = vectorA.z + VectorB.z;

	return newVector;
}

Vector3 subtractVector3(Vector3 vectorA, Vector3 VectorB)
{//mozna by to bylo przeciazyc
	Vector3 newVector;
	newVector.x = vectorA.x - VectorB.x;
	newVector.y = vectorA.y - VectorB.y;
	newVector.z = vectorA.z - VectorB.z;

	return newVector;
}


Vector3 normalizeVector3(Vector3 vector)
{//Przeciez mozna normalize
	/*
	GLdouble length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	Vector3 unitVector;
	unitVector.x = vector.x / length;
	unitVector.y = vector.y / length;
	unitVector.z = vector.z / length;
	

	return unitVector;
	*/
	vec3 unitVector = normalize(vec3(vector.x, vector.y, vector.z));
	return  makeVector3(unitVector.x, unitVector.y, unitVector.z);
}

Vector3 crossProductVector3(Vector3 vectorA, Vector3 VectorB)
{
	/*
	Vector3 newVector;
	newVector.x = vectorA.y*VectorB.z - vectorA.z*VectorB.y;
	newVector.y = vectorA.z*VectorB.x - vectorA.x*VectorB.z;
	newVector.z = vectorA.x*VectorB.y - vectorA.y*VectorB.x;

	return newVector;
	*/
	vec3 newVector = cross(vec3(vectorA.x, vectorA.y, vectorA.z), vec3(VectorB.x, VectorB.y, VectorB.z));
	return makeVector3(newVector.x, newVector.y, newVector.z);
}

GLfloat dotProductVector3(Vector3 vectorA, Vector3 vectorB)
{
	return vectorA.x*vectorB.x + vectorA.y*vectorB.y + vectorA.z*vectorB.z;
	//return dot(vec3(vectorA.x, vectorA.y, vectorA.z), vec3(vectorB.x, vectorB.y, vectorB.z));
}



Vector3 scalerMultiplyVector3(Vector3 vectorToMultiply, GLfloat scalerValue)
{
	Vector3 newVector;
	newVector.x = vectorToMultiply.x * scalerValue;
	newVector.y = vectorToMultiply.y * scalerValue;
	newVector.z = vectorToMultiply.z * scalerValue;

	return newVector;
}

Vector3 transformVector3(Vector3 vector, Matrix3 transformationMatrix)
{//niby jako mnozenie macierzy dwoch przez siebie //wtf?
	Vector3 newVector;
	newVector.x = dotProductVector3(vector, makeVector3(transformationMatrix.m00, transformationMatrix.m10, transformationMatrix.m20));
	newVector.y = dotProductVector3(vector, makeVector3(transformationMatrix.m01, transformationMatrix.m11, transformationMatrix.m21));
	newVector.z = dotProductVector3(vector, makeVector3(transformationMatrix.m02, transformationMatrix.m12, transformationMatrix.m22));

	return newVector;
}