#pragma once

#include <vector>
#include "Constants.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CollisionDetection.h"


enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 5.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;
const GLfloat RADIUS = 1.0f;


class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;
	GLfloat _radius;


	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), _radius(RADIUS)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), _radius(RADIUS)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}


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

	void resetCamera()
	{
		this->Position.x = CameraPosition.x;
		this->Position.y = CameraPosition.y;
		this->Position.z = CameraPosition.z;
		this->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		this->Yaw = YAW;
		this->Pitch = PITCH;
		this->updateCameraVectors();
	}

	glm::vec3 getPositionFront()
	{
		return (this->Position + this->Front);
	}

	glm::vec3 getUp()
	{
		return this->Up;
	}

	GLfloat getRadius()
	{
		return _radius;
	}

	
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = this->MovementSpeed * deltaTime;
		if (direction == FORWARD)
		{
			this->Position += this->Front * velocity;
		}
		if (direction == BACKWARD)
		{
			this->Position -= this->Front * velocity;
		}
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;

		if (FpsCamera)
		 this->Position.y = 0.0f;
	}

	
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		this->updateCameraVectors();
	}

	void ProcessMouseScroll(GLfloat yoffset)
	{
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}



	void CheckCameraCollision(vec3 *pVertices, int numOfVerts)
	{


		for (int i = 0; i < numOfVerts; i += 3)
		{
		
			vec3 vTriangle[3] = { pVertices[i], pVertices[i + 1], pVertices[i + 2] };

			vec3 vNormal = Normal(vTriangle);

			float distance = 0.0f;

			int classification = ClassifySphere(this->Position, vNormal, vTriangle[0], _radius, distance);

			if (classification == INTERSECTS)
			{

				vec3 vOffset = vNormal * distance;

				vec3 vIntersection = this->Position - vOffset;

				if (InsidePolygon(vIntersection, vTriangle, 3) ||
					EdgeSphereCollision(this->Position, vTriangle, 3, _radius))
				{
					vOffset = GetCollisionOffset(vNormal, _radius, distance);
					this->Position = this->Position + vOffset;
				}
			}
		}
	}


private:

	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}

	void jogging()
	{
		GLfloat lastTime = 0;
		GLfloat joggingAngle = 0;
	}



};

