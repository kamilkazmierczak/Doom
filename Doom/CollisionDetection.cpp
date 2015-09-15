#include "CollisionDetection.h"

/////////////////////////////////// ~~~~~~~~~~~~~~~~~~~~\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////								2D COLLISION DETECTION
/////
/////////////////////////////////// ~~~~~~~~~~~~~~~~~~~~\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


//bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius)
//{
//	//transform x,y,z to x,z (ignoring y)
//	vec2 P1 = vec2(Point_1.x, Point_1.z);
//	vec2 P2 = vec2(Point_2.x, Point_2.z);
//	vec2 Centre = vec2(Circle_Centre.x, Circle_Centre.z);
//
//
//
//	if (delta < 0) // No intersection
//		return false;
//
//	return true;
//}


bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius)
{
	//transform x,y,z to x,z (ignoring y)
	vec2 P1 = vec2(Point_1.x, Point_1.z);
	vec2 P2 = vec2(Point_2.x, Point_2.z);
	vec2 Centre = vec2(Circle_Centre.x, Circle_Centre.z);


	//cout << "P1 " << Point1.x << ";" << Point1.y << " P2 " << Point2.x << ";" << Point2.y << " S " << CircleCentre.x << ";" << CircleCentre.y << endl;
	
	//Przenies punkty P1 i P2 do przestrzeni lokalnej okregu ( tak jakby S=0,0)
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

	//dist_Point_to_Line(Point P, Line L)
	//{
	//	Vector v = L.P1 - L.P0;
	//	Vector w = P - L.P0;

	//	double c1 = dot(w, v);
	//	double c2 = dot(v, v);
	//	double b = c1 / c2;

	//	Point Pb = L.P0 + b * v;
	//	return d(P, Pb);
	//}


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

//bool CircleLineCollision(vec3 Point_1, vec3 Point_2, vec3 Circle_Centre, GLfloat radius)
//{
//	//transform x,y,z to x,z (ignoring y)
//	vec2 Point1 = vec2(Point_1.x, Point_1.z);
//	vec2 Point2 = vec2(Point_2.x, Point_2.z);
//	vec2 CircleCentre = vec2(Circle_Centre.x, Circle_Centre.z);
//
//
//	//cout << "P1 " << Point1.x << ";" << Point1.y << " P2 " << Point2.x << ";" << Point2.y << " S " << CircleCentre.x << ";" << CircleCentre.y << endl;
//
//	GLfloat distance = dist_Point_to_Line(CircleCentre, Point1, Point2);
//	//cout << distance << endl;
//
//	// Transform to local coordinates
//	vec2 LocalP1 = Point1 - CircleCentre;
//	vec2 LocalP2 = Point2 - CircleCentre;
//
//	vec2 P2minusP1 = LocalP2 - LocalP1;
//
//
//	GLfloat a = (P2minusP1.x) * (P2minusP1.x) + (P2minusP1.y) * (P2minusP1.y);
//	GLfloat	b = 2 * ((P2minusP1.x * LocalP1.x) + (P2minusP1.y * LocalP1.y));
//	GLfloat	c = (LocalP1.x * LocalP1.x) + (LocalP1.y * LocalP1.y) - (radius * radius);
//
//	GLfloat delta = b * b  - (4 * a * c);
//
//
//	if (delta < 0) // No intersection
//		return false;
//
//	return true;
//}















/////////////////////////////////// ~~~~~~~~~~~~~~~~~~~~\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////								3D COLLISION DETECTION
/////
/////////////////////////////////// ~~~~~~~~~~~~~~~~~~~~\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*


// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(vec3 Normal, vec3 Point)
{
	float distance = 0;
	// D = -(Ax + By + Cz)
	distance = -dot(Normal, Point);

	return distance;
}


//we only need 3 points (vPoly[])0,1,2 uzywam w funkcji Normal)
// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(vec3 vPoly[], vec3 vLine[], vec3 &vNormal, float &originDistance)
{
	float distance1 = 0, distance2 = 0;						// The distances from the 2 points of the line from the plane

	vNormal = Normal(vPoly);							// We need to get the normal of our plane to go any further

	// Let's find the distance our plane is from the origin.  We can find this value
	// from the normal to the plane (polygon) and any point that lies on that plane (Any vertice)
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

	distance1 = ((vNormal.x * vLine[0].x) +					// Ax +
		(vNormal.y * vLine[0].y) +					// Bx +
		(vNormal.z * vLine[0].z)) + originDistance;	// Cz + D

	// Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)

	distance2 = ((vNormal.x * vLine[1].x) +					// Ax +
		(vNormal.y * vLine[1].y) +					// Bx +
		(vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	// Now that we have 2 distances from the plane, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

	if (distance1 * distance2 >= 0)			// Check to see if both point's distances are both negative or both positive
		return false;						// Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...

	return true;							// The line intersected the plane, Return TRUE
}


vec3 Normal(vec3 vTriangle[])
{														// Get 2 vectors from the polygon (2 sides), Remember the order!
	vec3 vVector1 = vTriangle[2] - vTriangle[0];
	vec3 vVector2 = vTriangle[1] - vTriangle[0];

	vec3 vNormal = cross(vVector1, vVector2);		// Take the cross product of our 2 vectors to get a perpendicular vector

	// Now we have a normal, but it's at a strange length, so let's make it length 1.

	vNormal = normalize(vNormal);						// Use our function we created to normalize the normal (Makes it a length of one)

	return vNormal;										// Return our normal at our desired length
}



double AngleBetweenVectors(vec3 Vector1, vec3 Vector2)
{
	// Remember, above we said that the Dot Product of returns the cosine of the angle
	// between 2 vectors?  Well, that is assuming they are unit vectors (normalize vectors).
	// So, if we don't have a unit vector, then instead of just saying  arcCos(DotProduct(A, B))
	// We need to divide the dot product by the magnitude of the 2 vectors multiplied by each other.
	// Here is the equation:   arc cosine of (V . W / || V || * || W || )
	// the || V || means the magnitude of V.  This then cancels out the magnitudes dot product magnitudes.
	// But basically, if you have normalize vectors already, you can forget about the magnitude part.

	// Get the dot product of the vectors
	float dotProduct = dot(Vector1, Vector2);

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = length(Vector1) * length(Vector2);

	// Get the arc cosine of the (dotProduct / vectorsMagnitude) which is the angle in RADIANS.
	// (IE.   PI/2 radians = 90 degrees      PI radians = 180 degrees    2*PI radians = 360 degrees)
	// To convert radians to degress use this equation:   radians * (PI / 180)
	// TO convert degrees to radians use this equation:   degrees * (180 / PI)
	double angle = acos(dotProduct / vectorsMagnitude);

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate.
	// acos() thinks it's funny when it returns -1.#IND0000000.  If we don't do this check,
	// our collision results will sometimes say we are colliding when we aren't.  I found this
	// out the hard way after MANY hours and already wrong written tutorials :)  Usually
	// this value is found when the dot product and the maginitude are the same value.
	// We want to return 0 when this happens.
	if (_isnan(angle))
		return 0;

	// Return the angle in radians
	return(angle);
}


/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the intersection point of the line that intersects the plane
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

vec3 IntersectionPoint(vec3 vNormal, vec3 vLine[], double distance)
{
	vec3 vPoint =vec3(0.0f), vLineDir = vec3(0.0f);		// Variables to hold the point and the line's direction
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// Here comes the confusing part.  We need to find the 3D point that is actually
	// on the plane.  Here are some steps to do that:

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = vLine[1] - vLine[0];			    // Get the Vector of the line
	vLineDir = normalize(vLineDir);				// Normalize the lines vector


	// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the distance from one of our points to the plane.
	//    Here I just chose a arbitrary point as the point to find that distance.  You notice we negate that
	//    distance.  We negate the distance because we want to eventually go BACKWARDS from our point to the plane.
	//    By doing this is will basically bring us back to the plane to find our intersection point.
	Numerator = -(vNormal.x * vLine[0].x +		// Use the plane equation with the normal and the line
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	//    this will give us the cosine of the angle between the 2 (since they are both normalized - length 1).
	//    We will then divide our Numerator by this value to find the offset towards the plane from our arbitrary point.
	Denominator = dot(vNormal, vLineDir);		// Get the dot product of the line's vector and the normal of the plane

	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).  
	// In this case, we should just return any point on the line.

	if (Denominator == 0.0)						// Check so we don't divide by zero
		return vLine[0];						// Return an arbitrary point on the line

	// We divide the (distance from the point to the plane) by (the dot product)
	// to get the distance (dist) that we need to move from our arbitrary point.  We need
	// to then times this distance (dist) by our line's vector (direction).  When you times
	// a scalar (single number) by a vector you move along that vector.  That is what we are
	// doing.  We are moving from our arbitrary point we chose from the line BACK to the plane
	// along the lines vector.  It seems logical to just get the numerator, which is the distance
	// from the point to the line, and then just move back that much along the line's vector.
	// Well, the distance from the plane means the SHORTEST distance.  What about in the case that
	// the line is almost parallel with the polygon, but doesn't actually intersect it until half
	// way down the line's length.  The distance from the plane is short, but the distance from
	// the actual intersection point is pretty long.  If we divide the distance by the dot product
	// of our line vector and the normal of the plane, we get the correct length.  Cool huh?

	dist = Numerator / Denominator;				// Divide to get the multiplying (percentage) factor

	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	// This essentially moves the point along the vector to a certain distance.  This now gives
	// us the intersection point.  Yay!
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								// Return the intersection point
}






/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool InsidePolygon(vec3 vIntersection, vec3 Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.9999;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	vec3 vA, vB;						// Create temp vectors

	// Just because we intersected the plane, doesn't mean we were anywhere near the polygon.
	// This functions checks our intersection point to make sure it is inside of the polygon.
	// This is another tough function to grasp at first, but let me try and explain.
	// It's a brilliant method really, what it does is create triangles within the polygon
	// from the intersection point.  It then adds up the inner angle of each of those triangles.
	// If the angles together add up to 360 degrees (or 2 * PI in radians) then we are inside!
	// If the angle is under that value, we must be outside of polygon.  To further
	// understand why this works, take a pencil and draw a perfect triangle.  Draw a dot in
	// the middle of the triangle.  Now, from that dot, draw a line to each of the vertices.
	// Now, we have 3 triangles within that triangle right?  Now, we know that if we add up
	// all of the angles in a triangle we get 180° right?  Well, that is kinda what we are doing,
	// but the inverse of that.  Say your triangle is an equilateral triangle, so add up the angles
	// and you will get 180° degree angles.  60 + 60 + 60 is 360°.

	for (int i = 0; i < verticeCount; i++)		// Go in a circle to each vertex and get the angle between
	{
		vA = Poly[i] - vIntersection;	// Subtract the intersection point from the current vertex
										// Subtract the point from the next vertex
		vB = Poly[(i + 1) % verticeCount] - vIntersection;

		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}

	// Now that we have the total angles added up, we need to check if they add up to 360 degrees.
	// Since we are using the dot product, we are working in radians, so we check if the angles
	// equals 2*PI.  We defined PI in 3DMath.h.  You will notice that we use a MATCH_FACTOR
	// in conjunction with our desired degree.  This is because of the inaccuracy when working
	// with floating point numbers.  It usually won't always be perfectly 2 * PI, so we need
	// to use a little twiddling.  I use .9999, but you can change this to fit your own desired accuracy.

	if (Angle >= (MATCH_FACTOR * (2.0 * PI)))	// If the angle is greater than 2 PI, (360 degrees)
		return true;							// The point is inside of the polygon

	return false;								// If you get here, it obviously wasn't inside the polygon, so Return FALSE
}



/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks if a line is intersecting a polygon
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool IntersectedPolygon(vec3 vPoly[], vec3 vLine[], int verticeCount)
{
	vec3 vNormal = vec3(0.0f);
	float originDistance = 0;

	// First we check to see if our line intersected the plane.  If this isn't true
	// there is no need to go on, so return false immediately.
	// We pass in address of vNormal and originDistance so we only calculate it once

								    // Reference   // Reference
	if (!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
		return false;

	// Now that we have our normal and distance passed back from IntersectedPlane(), 
	// we can use it to calculate the intersection point.  The intersection point
	// is the point that actually is ON the plane.  It is between the line.  We need
	// this point test next, if we are inside the polygon.  To get the I-Point, we
	// give our function the normal of the plan, the points of the line, and the originDistance.

	vec3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// Now that we have the intersection point, we need to test if it's inside the polygon.
	// To do this, we pass in :
	// (our intersection point, the polygon, and the number of vertices our polygon has)

	if (InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;							// We collided!	  Return success


	// If we get here, we must have NOT collided

	return false;								// There was no collision, so return false
}



////////////////////////////// CLOSET POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the point on the line vA_vB that is closest to the point vPoint
/////
////////////////////////////// CLOSET POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

vec3 ClosestPointOnLine(vec3 vA, vec3 vB, vec3 vPoint)
{
	//cout << "WARNING" << endl;
	// This function takes a line segment, vA to vB, then a point, vPoint.
	// We want to find the closet point on the line segment to our vPoint
	// out in space.  Either it is going to be one of the end points of the line,
	// or it is going to be somewhere between vA and vB.  This is a important
	// function when dealing with collision detection.

	// Here is how it works, it's a bit confusing at first, so you will need
	// to contemplate it a bit.  First, we want to grab a vector from "vA" to the point.
	// Then we want to get a normalized vector from "vA" to "vB".  We don't need the
	// full length of the line segment vector, we just want a direction.  That is why 
	// we normalize it.  Remember, this is important because we are going to be using 
	// the dot product coming up next.  So, now we have 2 vectors that form a pseudo corner
	// of a triangle on the plane of the line segment and the point.
	//
	// Next, we want to find the distance or "magnitude" of the line segment.  This is
	// done with a simple distance formula.  Then we use the dot "vVector2" with "vVector1".
	// By using the dot product, we can essentially project vVector1 onto the
	// line segments normalized vector, "vVector2".  If the result of the dot product is
	// 0, that means the vectors were perpendicular and had a 90 degree angle between them.
	// The 0 part is the distance the new projected vector is from the starting of vVector2.
	// If the result is a negative number, that means the angle between the 2 vectors
	// is greater than 90 degrees, which means that the closest point must be "vA" because
	// it's projected vector is on the outside of the line.  So, if the result is a positive
	// number, the projected vector is on the right side of "vA", but could be past the right
	// side of vB.  To test this, we make sure that the result of the dot product is NOT
	// greater than the distance "d".  If it is, then the closest point on the plane is
	// obviously vB.  
	//
	// So, we can find the closest point easily if it's one of the end points of the line
	// segment, but how do we find the point between the 2 end points?  This is simple.
	// Since we have the distance "t" from point "vA" (given to us from the dot product 
	// of the 2 vectors), we just use our vector that is going the direction of the
	// line segment, "vVector2", and multiply it by the distance scalar "t".  This will
	// create a vector going in the direction of the line segment, with a distance
	// (or magnitude) of the projected vector, "vVector1", is from from "vA".  We then add
	// this vector to "vA", which gives us the point on the line that is closest to our
	// point out in space, vPoint!  
	//
	// This is probably pretty hard to visualize with just comments, unless you have a good 
	// grasp of linear algebra.  

	// Create the vector from end point vA to our point vPoint.
	vec3 vVector1 = vPoint - vA;

	// Create a normalized direction vector from end point vA to end point vB
	vec3 vVector2 = normalize(vB - vA);

	// Use the distance formula to find the distance of the line segment (or magnitude)
	float d = glm::distance(vA, vB);

	// Using the dot product, we project the vVector1 onto the vector vVector2.
	// This essentially gives us the distance from our projected vector from vA.
	float t = dot(vVector2, vVector1);

	// If our projected distance from vA, "t", is less than or equal to 0, it must
	// be closest to the end point vA.  We want to return this end point.
	if (t <= 0)
		return vA;

	// If our projected distance from vA, "t", is greater than or equal to the magnitude
	// or distance of the line segment, it must be closest to the end point vB.  So, return vB.
	if (t >= d)
		return vB;

	// Here we create a vector that is of length t and in the direction of vVector2
	vec3 vVector3 = vVector2 * t;

	// To find the closest point on the line segment, we just add vVector3 to the original
	// end point vA.  
	vec3 vClosestPoint = vA + vVector3;

	// Return the closest point on the line segment
	return vClosestPoint;
}


float Absolute(float num)
{
	// If num is less than zero, we want to return the absolute value of num.
	// This is simple, either we times num by -1 or subtract it from 0.
	if (num < 0)
		return (0 - num);

	// Return the original number because it was already positive
	return num;
}


////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns true if our sphere collides with the polygon passed in
/////
////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool SpherePolygonCollision(vec3 vPolygon[],
	vec3 &vCenter, int vertexCount, float radius)
{
	// This function is the only function we need to call for testing if a sphere
	// collides with a polygon.  The rest are just helper functions called within here.
	// The theory is actually quite difficult to understand, especially if you are
	// a beginner to collision detection and are following the tutorials in order, but
	// I will try to be as gentle and descriptive as possible.  Let go!
	// Basically, here is the overview:  
	//
	// 1) First you want to check if the sphere collides with the polygon's plane.
	//    Remember, that planes are infinite and you could be 500 units from the
	//    polygon and it's still going to trigger this first test.  We want to 
	//    write a function that classifies the sphere.  Either it's completely 
	//    in front of the plane (the side the normal is on), intersecting the
	//    plane or completely behind the plane.  Got it so far?  We created a 
	//    function called ClassifySphere() that returns BEHIND, FRONT or INTERSECTS.
	//    If ClassifySphere() returns INTERSECTS, then we move on to step 2, otherwise
	//    we did not collide with the polygon.
	// 
	// 2) The second step is to get an intersection point right in front of the sphere.
	//    This one of the tricky parts.  We know that once we have an intersection point
	//    on the plane of the polygon, we just need to use the InsidePolygon() function
	//    to see if that point is inside the dimensions of the polygon, just like we
	//    did with the Ray to Polygon Collision tutorial.  So, how do we get the point
	//    of intersection?  It's not as simple as it might sound.  Since a sphere infinite
	//    points, there would be a million points that it collided at.  You can't just
	//    draw a ray in the direction the sphere was moving because it could have just
	//    nicked the bottom of the polygon and your ray would find an intersection
	//    point that is outside of the polygon.  Well, it turns out that we need to
	//    first try and give it a shot.  We will try the first attempt a different way though.
	//    We know that we can find the normal vector of the polygon, which in essence
	//    tells us the direction that the polygon is facing.  From ClassifyPoly(),
	//	  it also returns the distance the center our sphere is from the plane.  That
	//    means we have a distance our sphere center is from the plane, and the normal
	//    tells us the direction the plane is in.  If we multiply the normal by the
	//    distance from the plane we get an offset.  This offset can then be subtracted
	//    from the center of the sphere.  Believe it or not, but we now have a position
	//    on the plane in the direction of the plane.  Usually, this intersection points
	//    works fine, but if we get around the edges of the polygon, this does not work.
	//    What we just did is also called "projecting the center of the sphere onto the plane".
	//    Another way to do this is to shoot out a ray from the center of the sphere in
	//    the opposite direction of the normal, then we find the intersection of that line
	//    and the plane.  My way just takes 3 multiplies and a subtraction.  You choose.
	//
	// 3) Once we have our psuedo intersection point, we just pass it into InsidePolygon(),
	//    along with the polygon vertices and the vertex count.  This will then return
	//    true if the intersection point was inside of the polygon, otherwise false.
	//    Remember, just because this returns false doesn't mean we stop there!  If
	//    we didn't collide yet, we need to skip to step 4.
	//
	// 4) If we get here, it's assumed that we tried our intersection point and it
	//    wasn't in the polygon's perimeter.  No fear!  There is hope!  If we get to step
	//    4, that's means that our center point is outside of the polygon's perimeter. Since
	//    we are dealing with a sphere, we could still be colliding because of the sphere's radius.
	//	  This last check requires us to find the point on each of the polygon's edges that
	//    is closest to the sphere's center.  We have a tutorial on finding this, so make sure
	//    you have read it or are comfortable with the concept.  If we are dealing with a
	//    triangle, we go through every side and get an edge vector, and calculate the closest
	//    point on those lines to our sphere's center.  After getting each closest point, we
	//    calculate the distance that point is from our sphere center.  If the distance is
	//    less than the radius of the sphere, there was a collision.  This way is pretty fast.  
	//    You don't need to calculate all three sides evey time, since the first closest point's 
	//    distance could be less than the radius and you return "true".
	//
	// That's the overview, *phew!*.  I bet you are reading this just wanting to cry because
	// that seems like so much math and theory to digest, so the code must be atrocious!
	// Well, you are partially right :)  It's not that bad actually, quite straight forward.
	// I will label the steps in the code so you can go back and forth to the overview and code.
	// I might mention that by having our vec3 class operator overloaded it cuts down the 
	// code tremendously.  If you are confused with this concept of C++, just create functions
	// to add, subtract and multiply vectors or scalars together.
	//

	// 1) STEP ONE - Finding the sphere's classification

	// Let's use our Normal() function to return us the normal to this polygon
	vec3 vNormal = Normal(vPolygon);

	// This will store the distance our sphere is from the plane
	float distance = 0.0f;

	// This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the plane
	// of the polygon.  We pass is our sphere center, the polygon's normal, a point on
	// the plane (vertex), the sphere's radius and an empty float to fill the distance with.
	int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);

	// If the sphere intersects the polygon's plane, then we need to check further,
	// otherwise the sphere did NOT intersect the polygon.  Pretty fast so far huh?
	if (classification == INTERSECTS)
	{
		// 2) STEP TWO - Finding the psuedo intersection point on the plane

		// Now we want to project the sphere's center onto the polygon's plane,
		// in the direction of the normal.  This is done by multiplying the "normal"
		// by the "distance" the sphere center is from the plane.  We got the distance
		// from the ClassifySphere() function call up above.  2 return values were given
		// through the "distance" variable being passed in as a reference.  If projecting
		// is confusing to you, just think of it as this: "I am starting at the center
		// of the sphere and I am going to just run into the plane.  I will move in the 
		// direction that is reverse from the normal.  When do I know when to stop?  Well,
		// I just go in that direction until my distance from the center is the same as
		// the distance the center of the sphere is from the plane."  By doing this
		// we get an offset to subtract from the center of the sphere.
		vec3 vOffset = vNormal * distance;

		// Once we have the offset to the plane, we just subtract it from the center
		// of the sphere.  "vPosition" now a point that lies on the plane of the polygon.
		// Whether it is inside the polygon's perimeter is another story.  Usually it
		// is though, unless we get near the edges of the polygon.
		vec3 vPosition = vCenter - vOffset;

		// 3) STEP THREE - Check if the intersection point is inside the polygons perimeter

		// This is the same function used in our previous tutorial on Ray to Polygon Collision.
		// If the intersection point is inside the perimeter of the polygon, it returns true.
		// We pass in the intersection point, the list of vertices and vertex count of the poly.
		if (InsidePolygon(vPosition, vPolygon, vertexCount))
			return true;	// We collided!
		else
		{
			// 4) STEP FOUR - Check the sphere to see if it intersects the polygon edges

			// If we get here, we didn't find an intersection point in the perimeter.
			// There is still one more chance to redeem our sphere that it can hit the mark.
			// If any part of the sphere intersects the edges of the polygon, we collided.  
			// This is only checked if the sphere's center point is outside the edges of the
			// polygon. We pass in the center of the sphere, the list of verts, the polygon 
			// vertex count and the sphere's radius.  If this returns true we have a collision.

			if (EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius))
			{
				return true;	// We collided! "And you doubted me..." - Sphere
			}
		}
	}

	// If we get here, there is obviously no collision happening up in this crib
	return false;
}



///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This tells if a sphere is BEHIND, in FRONT, or INTERSECTS a plane, also it's distance
/////
///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int ClassifySphere(vec3 &vCenter,
	vec3 &vNormal, vec3 &vPoint, float radius, float &distance)
{
	// First we need to find the distance our polygon plane is from the origin.
	// We need this for the distance formula below.
	float d = (float)PlaneDistance(vNormal, vPoint);

	// Here we use the famous distance formula to find the distance the center point
	// of the sphere is from the polygon's plane.  
	// Remember that the formula is Ax + By + Cz + d = 0 with ABC = Normal, XYZ = Point
	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	// Now we query the information just gathered.  Here is how Sphere Plane Collision works:
	// If the distance the center is from the plane is less than the radius of the sphere,
	// we know that it must be intersecting the plane.  We take the absolute value of the
	// distance when we do this check because once the center of the sphere goes behind
	// the polygon, the distance turns into negative numbers (with 0 being that the center
	// is exactly on the plane).  What do I mean when I say "behind" the polygon?  How do
	// we know which side is the front or back side?  Well, the side with the normal pointing
	// out from it is the front side, the other side is the back side.  This is all dependant
	// on the direction the vertices stored.  I recommend drawing them counter-clockwise.
	// if you go clockwise the normal with then point the opposite way and will screw up
	// everything.
	// So, if we want to find if the sphere is in front of the plane, we just make sure
	// the distance is greater than or equal to the radius.  let's say we have a radius
	// of 5, and the distance the center is from the plane is 6; it's obvious that the
	// sphere is 1 unit away from the plane.
	// If the sphere isn't intersecting or in front of the plane, it HAS to be BEHIND it.

	// If the absolute value of the distance we just found is less than the radius, 
	// the sphere intersected the plane.
	if (Absolute(distance) < radius)
		return INTERSECTS;
	// Else, if the distance is greater than or equal to the radius, the sphere is
	// completely in FRONT of the plane.
	else if (distance >= radius)
		return FRONT;

	// If the sphere isn't intersecting or in FRONT of the plane, it must be BEHIND
	return BEHIND;
}



///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns true if the sphere is intersecting any of the edges of the polygon
/////
///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool EdgeSphereCollision(vec3 &vCenter,
	vec3 vPolygon[], int vertexCount, float radius)
{
	vec3 vPoint;

	// This function takes in the sphere's center, the polygon's vertices, the vertex count
	// and the radius of the sphere.  We will return true from this function if the sphere
	// is intersecting any of the edges of the polygon.  How it works is, every edge line
	// segment finds the closest point on that line to the center of the sphere.  If the
	// distance from that closest point is less than the radius of the sphere, there was
	// a collision.  Otherwise, we are definately out of reach of the polygon.  This works
	// for triangles, quads, and any other convex polygons.

	// Go through all of the vertices in the polygon
	for (int i = 0; i < vertexCount; i++)
	{
		// This returns the closest point on the current edge to the center of the sphere.
		// Notice that we mod the second point of the edge by our vertex count.  This is
		// so that when we get to the last edge of the polygon, the second vertex of the
		// edge is the first vertex that we starting with.  
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);

		// Now, we want to calculate the distance between the closest point and the center
		float distance = glm::distance(vPoint, vCenter);

		// If the distance is less than the radius, there must be a collision so return true
		if (distance < radius)
			return true;
	}

	// The was no intersection of the sphere and the edges of the polygon
	return false;
}


///////////////////////////////// GET COLLISION OFFSET \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the offset to move the center of the sphere off the collided polygon
/////
///////////////////////////////// GET COLLISION OFFSET \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

vec3 GetCollisionOffset(vec3 &vNormal, float radius, float distance)
{
	vec3 vOffset = vec3(0, 0, 0);

	// Once we find if a collision has taken place, we need make sure the sphere
	// doesn't move into the wall.  In our app, the position will actually move into
	// the wall, but we check our collision detection before we render the scene, which
	// eliminates the bounce back effect it would cause.  The question is, how do we
	// know which direction to move the sphere back?  In our collision detection, we
	// account for collisions on both sides of the polygon.  Usually, you just need
	// to worry about the side with the normal vector and positive distance.  If 
	// you don't want to back face cull and have 2 sided planes, I check for both sides.
	//
	// Let me explain the math that is going on here.  First, we have the normal to
	// the plane, the radius of the sphere, as well as the distance the center of the
	// sphere is from the plane.  In the case of the sphere colliding in the front of
	// the polygon, we can just subtract the distance from the radius, then multiply
	// that new distance by the normal of the plane.  This projects that leftover
	// distance along the normal vector.  For instance, say we have these values:
	//
	//	vNormal = (1, 0, 0)		radius = 5		distance = 3
	//
	// If we subtract the distance from the radius we get: (5 - 3 = 2)
	// The number 2 tells us that our sphere is over the plane by a distance of 2.
	// So basically, we need to move the sphere back 2 units.  How do we know which
	// direction though?  This part is easy, we have a normal vector that tells us the
	// direction of the plane.  
	// If we multiply the normal by the left over distance we get:  (2, 0, 0)
	// This new offset vectors tells us which direction and how much to move back.
	// We then subtract this offset from the sphere's position, giving is the new
	// position that is lying right on top of the plane.  Ba da bing!
	// If we are colliding from behind the polygon (not usual), we do the opposite
	// signs as seen below:

	// If our distance is greater than zero, we are in front of the polygon
	if (distance > 0)
	{
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		float distanceOver = radius - distance;
		vOffset = vNormal * distanceOver;
	}
	else // Else colliding from behind the polygon
	{
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		float distanceOver = radius + distance;
		vOffset = vNormal * -distanceOver;
	}

	// There is one problem with check for collisions behind the polygon, and that
	// is if you are moving really fast and your center goes past the front of the
	// polygon, it will then assume you were colliding from behind and not let
	// you back in.  Most likely you will take out the if / else check, but I
	// figured I would show both ways in case someone didn't want to back face cull.

	// Return the offset we need to move back to not be intersecting the polygon.
	return vOffset;
}