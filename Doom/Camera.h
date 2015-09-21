

#pragma once

// Std. Includes
#include <vector>
#include "Constants.h"

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CollisionDetection.h"


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;
const GLfloat RADIUS = 1.0f;


// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;
	GLfloat _radius;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), _radius(RADIUS)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), _radius(RADIUS)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	glm::vec3 getCenter()
	{
		return this->Front;
	}
	glm::vec3 getPosition()
	{
		return this->Position;
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
		{
			//this->Position.y += 0.1f;
			this->Position += this->Front * velocity;
		}
		if (direction == BACKWARD)
		{
			this->Position -= this->Front * velocity;
			//this->Position.y -= 1.0f*velocity;

		}
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;

		//FPS CAMERA
		if (FpsCamera)
		 this->Position.y = 0.0f;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset)
	{
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}




//DETEKCJA KOLIZJI

	void CheckCameraCollision(vec3 *pVertices, int numOfVerts)
	{
		// This function is pretty much a direct rip off of SpherePolygonCollision()
		// We needed to tweak it a bit though, to handle the collision detection once 
		// it was found, along with checking every triangle in the list if we collided.  
		// pVertices is the world data. If we have space partitioning, we would pass in 
		// the vertices that were closest to the camera. What happens in this function 
		// is that we go through every triangle in the list and check if the camera's 
		// sphere collided with it.  If it did, we don't stop there.  We can have 
		// multiple collisions so it's important to check them all.  One a collision 
		// is found, we calculate the offset to move the sphere off of the collided plane.

		// Go through all the triangles
		for (int i = 0; i < numOfVerts; i += 3)
		{
			// Store of the current triangle we testing
			vec3 vTriangle[3] = { pVertices[i], pVertices[i + 1], pVertices[i + 2] };

			// 1) STEP ONE - Finding the sphere's classification

			// We want the normal to the current polygon being checked
			vec3 vNormal = Normal(vTriangle);

			// This will store the distance our sphere is from the plane
			float distance = 0.0f;

			// This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the plane
			int classification = ClassifySphere(this->Position, vNormal, vTriangle[0], _radius, distance);

			// If the sphere intersects the polygon's plane, then we need to check further
			if (classification == INTERSECTS)
			{
				// 2) STEP TWO - Finding the psuedo intersection point on the plane

				// Now we want to project the sphere's center onto the triangle's plane
				vec3 vOffset = vNormal * distance;

				// Once we have the offset to the plane, we just subtract it from the center
				// of the sphere.  "vIntersection" is now a point that lies on the plane of the triangle.
				vec3 vIntersection = this->Position - vOffset;

				// 3) STEP THREE - Check if the intersection point is inside the triangles perimeter

				// We first check if our intersection point is inside the triangle, if not,
				// the algorithm goes to step 4 where we check the sphere again the polygon's edges.

				// We do one thing different in the parameters for EdgeSphereCollision though.
				// Since we have a bulky sphere for our camera, it makes it so that we have to 
				// go an extra distance to pass around a corner. This is because the edges of 
				// the polygons are colliding with our peripheral view (the sides of the sphere).  
				// So it looks likes we should be able to go forward, but we are stuck and considered 
				// to be colliding.  To fix this, we just pass in the radius / 2.  Remember, this
				// is only for the check of the polygon's edges.  It just makes it look a bit more
				// realistic when colliding around corners.  Ideally, if we were using bounding box 
				// collision, cylinder or ellipses, this wouldn't really be a problem.

				if (InsidePolygon(vIntersection, vTriangle, 3) ||
					EdgeSphereCollision(this->Position, vTriangle, 3, _radius))
				{
					// If we get here, we have collided!  To handle the collision detection
					// all it takes is to find how far we need to push the sphere back.
					// GetCollisionOffset() returns us that offset according to the normal,
					// radius, and current distance the center of the sphere is from the plane.
					vOffset = GetCollisionOffset(vNormal, _radius, distance);

					// Now that we have the offset, we want to ADD it to the position and
					// view vector in our camera.  This pushes us back off of the plane.  We
					// don't see this happening because we check collision before we render
					// the scene.
					this->Position = this->Position + vOffset;
					//this->Front = this->Front + vOffset;
				}
			}
		}
	}










private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}

	void jogging()
	{
		GLfloat lastTime = 0;
		// Used to make us "jog" up and down as we move forward.
		GLfloat joggingAngle = 0;
		/*
		function animate() {
			var timeNow = new Date().getTime();
			if (lastTime != 0) {
				var elapsed = timeNow - lastTime;
				*/
	}



};

