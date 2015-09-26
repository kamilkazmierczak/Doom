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


void CameraSystem::reactOnMap(Entity *entity)
{
	vector <ThreeVertices> *realCurrentVertices = entity->getRealVertices();
	if (entity->getType() != ENTITY_BULLET &&
		!(entity->getVertexBuffer() != NULL &&
		entity->getVertexBuffer()->getTextureLoader() != NULL &&
		entity->getVertexBuffer()->getTextureLoader()->getTextureType() == TX_SKYBOX))
	{
		if (entity->getRealVertices() == nullptr)
			cout << "Cos jest nie tak #Camera_1" << endl;

		for (vector<ThreeVertices>::iterator iterator = realCurrentVertices->begin(); iterator != realCurrentVertices->end(); iterator++)
		{
			vec3 *real[3];
			//przelec po wszystkich trojkatach danego obiektu
			for (int k = 0; k < realCurrentVertices->size(); k++)
			{
				real[0] = &realCurrentVertices->at(k).a;
				real[1] = &realCurrentVertices->at(k).b;
				real[2] = &realCurrentVertices->at(k).c;

				_currentCamera->CheckCameraCollision(*real, 3);
			}
		}
	}
}


void CameraSystem::setCurrentCamera(Camera *newCamera)
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