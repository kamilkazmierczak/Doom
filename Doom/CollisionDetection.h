#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#define PI 3.1415926535897932	

using namespace glm;
using namespace std;

//ZROB TO JAKO ENUM
#define BEHIND		0	// This is returned if the sphere is completely behind the plane
#define INTERSECTS	1	// This is returned if the sphere intersects the plane
#define FRONT		2	// This is returned if the sphere is completely in front of the plane

//2D 
//zmien te podkreslenia sa tylko po to bo nie wiem czy funkcja nadpisze mi na nowe czy bd glupiec
bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius);

GLfloat	dist_Point_to_Line(vec2 S, vec2 P1, vec2 P2);


//3D
//1. Line Segment and Plane Collision

// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(vec3 Normal, vec3 Point);

// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(vec3 vPoly[], vec3 vLine[], vec3 &vNormal, float &originDistance);

//	This returns the normal of a polygon (The direction the polygon is facing)
vec3 Normal(vec3 vTriangle[]);



//2. Line Segment and Polygon Collision

// This returns the angle between 2 vectors
double AngleBetweenVectors(vec3 Vector1, vec3 Vector2);

// This returns an intersection point of a polygon and a line (assuming intersects the plane)
vec3 IntersectionPoint(vec3 vNormal, vec3 vLine[], double distance);

// This returns true if the intersection point is inside of the polygon
bool InsidePolygon(vec3 vIntersection, vec3 Poly[], long verticeCount);

// Use this function to test collision between a line and polygon
bool IntersectedPolygon(vec3 vPoly[], vec3 vLine[], int verticeCount);


///////

//3. Closest Point on a Line
// This returns the point on the line segment vA_vB that is closest to point vPoint
//ale gdyby vPoint obliczac gdzie sie znajduje w grze to by mozna bylo chyba podstawic tu wspolrzedne pkt z gry
//chyba by to bylo nawet lepsze
vec3 ClosestPointOnLine(vec3 vA, vec3 vB, vec3 vPoint);


//4. Sphere Polygon Collison

// This function classifies a sphere according to a plane.  The information returned
// tells us if the sphere is BEHIND, in FRONT, or INTERSECTS the plane.  This takes 
// the sphere's center, the plane's normal, a point on the plane, the sphere's radius
// and a referenced variable to hold the distance.  This way we can return the distance
// and the sphere's relationship to the plane.  The distance is from the plane to the center
// of the sphere.  With this information it enables us to offset the sphere if needed.
int ClassifySphere(vec3 &vCenter,
	vec3 &vNormal, vec3 &vPoint, float radius, float &distance);

// This takes in the sphere center, radius, polygon vertices and vertex count.
// This function is only called if the intersection point failed.  The sphere
// could still possibly be intersecting the polygon, but on it's edges.
bool EdgeSphereCollision(vec3 &vCenter,
	vec3 vPolygon[], int vertexCount, float radius);

// This returns true if the sphere is intersecting with the polygon.
// The parameters are the vertices of the polygon, vertex count, along with the center 
// and radius of the sphere.
bool SpherePolygonCollision(vec3 vPolygon[],
	vec3 &vCenter, int vertexCount, float radius);


// This returns the offset the sphere needs to move in order to not intersect the plane
vec3 GetCollisionOffset(vec3 &vNormal, float radius, float distance);



//WYWAL TO
// This returns the absolute value of num - a simple if/else check
float absolute(float num);