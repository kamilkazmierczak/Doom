#include "CameraSystem.h"
#include "RenderSystem.h"


CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}


Camera* CameraSystem::getCurrentCamera()
{
	return _currentCamera;
}

void CameraSystem::setCurrentCamera(Camera *newCamera)
{
	_currentCamera = newCamera;
	RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
	renderSystem->setCurrentCamera(_currentCamera);
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