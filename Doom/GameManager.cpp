#include "GameManager.h"
#include "Constants.h"
// Window dimensions



GameManager::GameManager(bool running)
	:_running(running), _window(glfwGetCurrentContext()), _renderSystem(&RenderSystem::getRenderSystem()),
	_resourceManager(&ResourceManager::getResourceManager()), _movementSystem(&MovementSystem::getMovementSystem()),
	_cameraSystem(&CameraSystem::getCameraSystem()), _scene(new Scene), _playerInputSystem(&PlayerInputSystem::getPlayerInputSystem())
{

}


GameManager::~GameManager()
{
	ResourceManager::destroyResourceManager();
	CameraSystem::destroyCameraSystem();
	RenderSystem::destroyRenderSystem();
	PlayerInputSystem::destroyPlayerInputSystem();
}


void GameManager::runGameLoop()
{
	// Deltatime
	GLfloat lastTime = glfwGetTime(); 
	_deltaTime = 0.0f; // Time between current frame and last frame

	while (_running){
		
		GLfloat currentTime = glfwGetTime();
		_deltaTime += (currentTime - lastTime) * UpdatesPerSecond;
		lastTime = currentTime;
		
		while (_deltaTime >= 1.0f){
			_running = !glfwWindowShouldClose(_window);
			_movementSystem->update(_scene->getChildren());
			_playerInputSystem->update();

			--_deltaTime;
		}

		_renderSystem->render(_scene->getChildren());
		
	}
}


GLfloat GameManager::getDeltaTime()
{
	return _deltaTime;
}


GameManager& GameManager::getGameManager()
{
	static GameManager *gameManager = NULL;

	if (gameManager == NULL){

		// Init GLFW
		glfwInit();

		
		// Set all the required options for GLFW
		
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_SAMPLES, 16); //wygladzenie krawedzi
		

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		

		// Create a GLFWwindow object that we can use for GLFW's functions
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "DOOM", nullptr, nullptr);
		glfwMakeContextCurrent(window);



		glewExperimental = GL_TRUE;
		glewInit();

		gameManager = new GameManager(true);
		cout << "GameManager stworzony" << endl;
	}
	return *gameManager;
}

void GameManager::destroyGameManager()
{
	GameManager *gameManager = &getGameManager();
	delete gameManager;
	cout << "GameManager zniszczony" << endl;

	GLFWwindow* window = glfwGetCurrentContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}


void GameManager::hi()
{
	//hi
}