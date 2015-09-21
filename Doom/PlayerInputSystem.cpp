#include "PlayerInputSystem.h"
#include "GameManager.h"
#include "Constants.h"
#include <algorithm>
#include "BulletObject.h"
#include "Player.h"



using namespace std;

PlayerInputSystem::PlayerInputSystem() 
:_window(glfwGetCurrentContext()), _mouseLastX(WIDTH / 2.0), _mouseLastY(HEIGHT / 2.0), _firstMouse(true),
_deltaTime(0.0f), _lastFrame(0.0f), _lastShootTime(glfwGetTime())
{
	//glfwGetCursorPos(_window, &_lastMousePosition.x, &_lastMousePosition.y);
	/*
	_mouseLastX = WIDTH / 2.0;
	_mouseLastY = HEIGHT / 2.0;
	_firstMouse = true;
	_deltaTime = 0.0f;
	_lastFrame = 0.0f;
	*/
}


PlayerInputSystem::~PlayerInputSystem()
{
}

void PlayerInputSystem::update()
{//poruszanie sie
	
	GLfloat currentFrame = glfwGetTime();
	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;

	
	if (_currentCamera != NULL && glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
	{
		// Camera controls
		if (glfwGetKey(_window, GLFW_KEY_W))
			_currentCamera->ProcessKeyboard(FORWARD, _deltaTime);	
		if (glfwGetKey(_window, GLFW_KEY_S))
			_currentCamera->ProcessKeyboard(BACKWARD, _deltaTime);
		if (glfwGetKey(_window, GLFW_KEY_A))
			_currentCamera->ProcessKeyboard(LEFT, _deltaTime);
		if (glfwGetKey(_window, GLFW_KEY_D))
			_currentCamera->ProcessKeyboard(RIGHT, _deltaTime);
	}
	

	
	
}



void PlayerInputSystem::setCurrentCamera(Camera *newCamera)
{
_currentCamera = newCamera;
}


void PlayerInputSystem::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

		if (GLFW_CURSOR_DISABLED == glfwGetInputMode(_window, GLFW_CURSOR)) {
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	
}



void PlayerInputSystem::keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	playerInputSystem->keyCallback(window, key, scancode, action, mode);
}


void PlayerInputSystem::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	
	if (_firstMouse)
	{
		_mouseLastX = xpos;
		_mouseLastY = ypos;
		_firstMouse = false;
	}

	GLfloat xoffset = xpos - _mouseLastX;
	GLfloat yoffset = _mouseLastY - ypos;  // Reversed since y-coordinates go from bottom to left

	_mouseLastX = xpos;
	_mouseLastY = ypos;

	

	_currentCamera->ProcessMouseMovement(xoffset, yoffset);
	
}

void PlayerInputSystem::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Player *player = &Player::getPlayer();

	if ((_lastShootTime + ReloadTime < glfwGetTime()) && player->getAmmo() > 0)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			//cout << "nacisnieto LPM" << endl;
			ResourceManager *resourceManager = &ResourceManager::getResourceManager();
			RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
			CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
			Player *player = &Player::getPlayer();
			//dostep do wektorow
			//gameManager->getScene()->getChildren()
			//renderSystem->getNewObjects()


			//tworzenie naboju 
			vec3 center = cameraSystem->getCurrentCamera()->getCenter();
			vec3 position = cameraSystem->getCurrentCamera()->getPosition();
			vec3 viewDirection = cameraSystem->getCurrentCamera()->getCenter();
			//position += viewDirection * 2.0f;


			IObject *sphere = new BulletObject(resourceManager->getBullet(), BU_PLAYER);

			Entity *entity = new Entity(sphere, makeVector3(position.x, position.y, position.z), ENTITY_BULLET);


			//GLfloat bulletSpeed = 0.008f;
			GLfloat max = std::max(std::abs(center.x), std::max(std::abs(center.y), std::abs(center.z)));

			if (max != 0)
			{
				entity->setVelocity(makeVector3((center.x / max)*BulletSpeed,
					(center.y / max)*BulletSpeed,
					(center.z / max)*BulletSpeed));
			}
			else
			{
				cout << "patrzysz na srodek" << endl;
				//chyba
				entity->setVelocity(makeVector3(BulletSpeed, BulletSpeed, BulletSpeed));
			}

			renderSystem->getNewObjects()->push_back(entity);
			_lastShootTime = glfwGetTime();
			player->setAmmo(-1.0f);

			cout << "Ammo left:" << endl;
			cout << player->getAmmo() << endl;

		}
	} 
}

void PlayerInputSystem::mouseCallbackFun(GLFWwindow* window, double xpos, double ypos)
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	playerInputSystem->mouseCallback(window, xpos, ypos);
}

void PlayerInputSystem::mouseButtonCallbackFun(GLFWwindow* window, int button, int action, int mods)
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	playerInputSystem->mouseButtonCallback(window, button, action, mods);
}


void PlayerInputSystem::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	_currentCamera->ProcessMouseScroll(yoffset);
}

void PlayerInputSystem::scrollCallbackFun(GLFWwindow* window, double xoffset, double yoffset)
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	playerInputSystem->scrollCallback(window, xoffset, yoffset);
}


PlayerInputSystem& PlayerInputSystem::getPlayerInputSystem()
{
	static PlayerInputSystem *playerInputSystem = NULL;

	if (playerInputSystem == NULL)
	{
		glfwSetKeyCallback(glfwGetCurrentContext(), *keyCallbackFun);
		glfwSetScrollCallback(glfwGetCurrentContext(), *scrollCallbackFun);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), *mouseCallbackFun);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), *mouseButtonCallbackFun);


		//glfwSetMouseallback(glfwGetCurrentContext(), *mouseCallbackFun);
		//glfwSetKeyCallback();
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		playerInputSystem = new PlayerInputSystem();
	}

	return *playerInputSystem;
}

void PlayerInputSystem::destroyPlayerInputSystem()
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	delete playerInputSystem;
}