#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#define PI 3.1415926535897932	

using namespace glm;
using namespace std;


#define BEHIND		0	
#define INTERSECTS	1	
#define FRONT		2	

//2D 

bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius);

GLfloat	dist_Point_to_Line(vec2 S, vec2 P1, vec2 P2);

//3D

float PlaneDistance(vec3 Normal, vec3 Point);

bool IntersectedPlane(vec3 vPoly[], vec3 vLine[], vec3 &vNormal, float &originDistance);

vec3 Normal(vec3 vTriangle[]);

double AngleBetweenVectors(vec3 Vector1, vec3 Vector2);

vec3 IntersectionPoint(vec3 vNormal, vec3 vLine[], double distance);

bool InsidePolygon(vec3 vIntersection, vec3 Poly[], long verticeCount);

bool IntersectedPolygon(vec3 vPoly[], vec3 vLine[], int verticeCount);

vec3 ClosestPointOnLine(vec3 vA, vec3 vB, vec3 vPoint);

int ClassifySphere(vec3 &vCenter,
	vec3 &vNormal, vec3 &vPoint, float radius, float &distance);

bool EdgeSphereCollision(vec3 &vCenter,
	vec3 vPolygon[], int vertexCount, float radius);

bool SpherePolygonCollision(vec3 vPolygon[],
	vec3 &vCenter, int vertexCount, float radius);

vec3 GetCollisionOffset(vec3 &vNormal, float radius, float distance);

float absolute(float num);