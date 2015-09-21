#pragma once
#include "Entity.h"
#include "Camera.h"

class CameraSystem
{
private:
	Camera *_currentCamera;

	CameraSystem();
	~CameraSystem();
public:
	Camera *getCurrentCamera();
	void setCurrentCamera(Camera *newCamera);
	void reactOnMap(Entity *entity);


	static CameraSystem& getCameraSystem();
	static void destroyCameraSystem();
};

