#pragma once
#include "Entity.h"

class CameraSystem
{
private:
	Entity *_currentCamera;

	CameraSystem();
	~CameraSystem();
public:
	Entity *getCurrentCamera();
	void setCurrentCamera(Entity *newCamera);

	static CameraSystem& getCameraSystem();
	static void destroyCameraSystem();
};

