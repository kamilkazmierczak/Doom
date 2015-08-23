#include "CameraSystem.h"


CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}


Entity* CameraSystem::getCurrentCamera()
{
	return _currentCamera;
}

void CameraSystem::setCurrentCamera(Entity *newCamera)
{
	_currentCamera = newCamera;
}

CameraSystem& CameraSystem::getCameraSystem()
{
	static CameraSystem *cameraSystem = NULL;

	if (cameraSystem == NULL){
		
		cameraSystem = new CameraSystem();
	}
	return *cameraSystem;
}

void CameraSystem::destroyCameraSystem()
{
	CameraSystem *cameraSystem = &getCameraSystem();
	delete cameraSystem;
}