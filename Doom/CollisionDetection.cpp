#include "CollisionDetection.h"



bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius)
{
	//transform x,y,z to x,z 
	vec2 P1 = vec2(Point_1.x, Point_1.z);
	vec2 P2 = vec2(Point_2.x, Point_2.z);
	vec2 Centre = vec2(Circle_Centre.x, Circle_Centre.z);

	P1 = P1 - Centre;
	P2 = P2 - Centre;

	//http://mathworld.wolfram.com/Circle-LineIntersection.html
	GLfloat dx = P2.x - P1.x;
	GLfloat dy = P2.y - P1.y;
	GLfloat dr = sqrt(dx*dx + dy*dy);
	GLfloat D = P1.x * P2.y - P2.x * P1.y;
	GLfloat delta = radius*radius * dr*dr - D*D;

	if (delta < 0) // No intersection
		return false;

	return true;
}



GLfloat	dist_Point_to_Line(vec2 S, vec2 P1, vec2 P2)
{
		vec2 v = P2 - P1;
		vec2 w = S - P1;

		GLfloat c1 = dot(w, v);
		GLfloat c2 = dot(v, v);
		GLfloat b = c1 / c2;

		vec2 Pb = P1 + b*v;
		return glm::distance(S, Pb);
}




/////3D COLLISION DETECTION

float PlaneDistance(vec3 Normal, vec3 Point)
{
	float distance = 0;
	// D = -(Ax + By + Cz)
	distance = -dot(Normal, Point);

	return distance;
}


bool IntersectedPlane(vec3 vPoly[], vec3 vLine[], vec3 &vNormal, float &originDistance)
{
	float distance1 = 0, distance2 = 0;						

	vNormal = Normal(vPoly);							

	originDistance = PlaneDistance(vNormal, vPoly[0]);

	
	distance1 = ((vNormal.x * vLine[0].x) +					// Ax +
		(vNormal.y * vLine[0].y) +					// Bx +
		(vNormal.z * vLine[0].z)) + originDistance;	// Cz + D


	distance2 = ((vNormal.x * vLine[1].x) +					// Ax +
		(vNormal.y * vLine[1].y) +					// Bx +
		(vNormal.z * vLine[1].z)) + originDistance;	// Cz + D


	if (distance1 * distance2 >= 0)			
		return false;						

	return true;							
}


vec3 Normal(vec3 vTriangle[])
{														
	vec3 vVector1 = vTriangle[2] - vTriangle[0];
	vec3 vVector2 = vTriangle[1] - vTriangle[0];

	vec3 vNormal = cross(vVector1, vVector2);		


	vNormal = normalize(vNormal);						

	return vNormal;										
}



double AngleBetweenVectors(vec3 Vector1, vec3 Vector2)
{

	float dotProduct = dot(Vector1, Vector2);


	float vectorsMagnitude = length(Vector1) * length(Vector2);

	double angle = acos(dotProduct / vectorsMagnitude);

	if (_isnan(angle))
		return 0;

	return(angle);
}



vec3 IntersectionPoint(vec3 vNormal, vec3 vLine[], double distance)
{
	vec3 vPoint =vec3(0.0f), vLineDir = vec3(0.0f);		
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	vLineDir = vLine[1] - vLine[0];			    
	vLineDir = normalize(vLineDir);				


	Numerator = -(vNormal.x * vLine[0].x +		
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	Denominator = dot(vNormal, vLineDir);		

	if (Denominator == 0.0)						
		return vLine[0];						

	dist = Numerator / Denominator;				

	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;
}


bool InsidePolygon(vec3 vIntersection, vec3 Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.9999;		
	double Angle = 0.0;						
	vec3 vA, vB;						


	for (int i = 0; i < verticeCount; i++)		
	{
		vA = Poly[i] - vIntersection;	
										
		vB = Poly[(i + 1) % verticeCount] - vIntersection;

		Angle += AngleBetweenVectors(vA, vB);	
	}


	if (Angle >= (MATCH_FACTOR * (2.0 * PI)))	
		return true;							

	return false;
}


bool IntersectedPolygon(vec3 vPoly[], vec3 vLine[], int verticeCount)
{
	vec3 vNormal = vec3(0.0f);
	float originDistance = 0;

								    // Reference   // Reference
	if (!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
		return false;

	vec3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	if (InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;							

	return false;								
}


vec3 ClosestPointOnLine(vec3 vA, vec3 vB, vec3 vPoint)
{

	vec3 vVector1 = vPoint - vA;
	
	vec3 vVector2 = normalize(vB - vA);
	
	float d = glm::distance(vA, vB);

	float t = dot(vVector2, vVector1);

	if (t <= 0)
		return vA;

	if (t >= d)
		return vB;

	vec3 vVector3 = vVector2 * t;

	vec3 vClosestPoint = vA + vVector3;

	return vClosestPoint;
}


float Absolute(float num)
{
	if (num < 0)
		return (0 - num);

	return num;
}



bool SpherePolygonCollision(vec3 vPolygon[],
	vec3 &vCenter, int vertexCount, float radius)
{
	
	
	vec3 vNormal = Normal(vPolygon);

	
	float distance = 0.0f;

	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);


	if (classification == INTERSECTS)
	{		
		vec3 vOffset = vNormal * distance;

		vec3 vPosition = vCenter - vOffset;

		if (InsidePolygon(vPosition, vPolygon, vertexCount))
			return true;	
		else
		{
			if (EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius))
			{
				return true;	
			}
		}
	}


	return false;
}



int ClassifySphere(vec3 &vCenter,
	vec3 &vNormal, vec3 &vPoint, float radius, float &distance)
{
	float d = (float)PlaneDistance(vNormal, vPoint);

	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	if (Absolute(distance) < radius)
		return INTERSECTS;

	else if (distance >= radius)
		return FRONT;

	return BEHIND;
}



bool EdgeSphereCollision(vec3 &vCenter,
	vec3 vPolygon[], int vertexCount, float radius)
{
	vec3 vPoint;

	for (int i = 0; i < vertexCount; i++)
	{

		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);

		float distance = glm::distance(vPoint, vCenter);

		if (distance < radius)
			return true;
	}

	return false;
}



vec3 GetCollisionOffset(vec3 &vNormal, float radius, float distance)
{
	vec3 vOffset = vec3(0, 0, 0);

	if (distance > 0)
	{
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else
	{

		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	return vOffset;
}