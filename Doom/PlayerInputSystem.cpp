#include "PlayerInputSystem.h"
#include "GameManager.h"
#include "Constants.h"

using namespace std;

PlayerInputSystem::PlayerInputSystem() 
:_window(glfwGetCurrentContext()), _mouseLastX(WIDTH / 2.0), _mouseLastY(HEIGHT / 2.0), _firstMouse(true),
_deltaTime(0.0f), _lastFrame(0.0f)
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
	

	//OLD
	/* 
	if (_currentPlayer != NULL && glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) 
	{
		if (glfwGetKey(_window, GLFW_KEY_W)){
			_currentPlayer->setPosition(addVector3(_currentPlayer->getPosition(),
				scalerMultiplyVector3(_eyeVector,0.07f)));
		}

		if (glfwGetKey(_window, GLFW_KEY_S)){
			_currentPlayer->setPosition(subtractVector3(_currentPlayer->getPosition(),
				scalerMultiplyVector3(_eyeVector, 0.07f)));
		}

		if (glfwGetKey(_window, GLFW_KEY_A)){
			_currentPlayer->setPosition(subtractVector3(_currentPlayer->getPosition(),//up vector? why not
				scalerMultiplyVector3(crossProductVector3(_eyeVector,makeVector3(0.0f, 1.0f,0.0f)), 0.07f)));
		}

		if (glfwGetKey(_window, GLFW_KEY_D)){
			_currentPlayer->setPosition(addVector3(_currentPlayer->getPosition(),//up vector? why not
				scalerMultiplyVector3(crossProductVector3(_eyeVector, makeVector3(0.0f, 1.0f, 0.0f)), 0.07f)));
		}

		Vector2 currentMousePosition;
		glfwGetCursorPos(_window, &currentMousePosition.x, &currentMousePosition.y);
																		//45stopni? w radianach ?
		_eyeVector = transformVector3(_eyeVector, makeRotationMatrix3((3.14f / (4.0f*45.0f))*-
			(currentMousePosition.x - _lastMousePosition.x), 0.0f, 1.0f, 0.0f));
											//for horizontal rotate around up vector 

		glfwGetCursorPos(_window, &_lastMousePosition.x, &_lastMousePosition.y);

		_currentPlayer->setEyeVector(addVector3(_currentPlayer->getPosition(), _eyeVector));
		}

		*/ 
		//OLD
	
}

/*
void PlayerInputSystem::setCurrentPlayer(Entity *newPlayer)
{
	_currentPlayer = newPlayer;
	_eyeVector = normalizeVector3(newPlayer->getEyeVector());
}
*/


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

void PlayerInputSystem::mouseCallbackFun(GLFWwindow* window, double xpos, double ypos)
{
	PlayerInputSystem *playerInputSystem = &getPlayerInputSystem();
	playerInputSystem->mouseCallback(window, xpos, ypos);
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