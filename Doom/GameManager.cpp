#include "GameManager.h"
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


GameManager::GameManager(bool running) 
	:_running(running), _window(glfwGetCurrentContext()), _renderSystem(&RenderSystem::getRenderSystem()),
	_resourceManager(&ResourceManager::getResourceManager())
{
	
}


GameManager::~GameManager()
{
	ResourceManager::destroyResourceManager();
	RenderSystem::destroyRenderSystem();
}


void GameManager::runGameLoop()
{
	while (_running){
		
		_running = !glfwWindowShouldClose(_window);

		_renderSystem->render((_resourceManager->getVertexBufferArray())->at(0), (_resourceManager->getShaderArray())->at(0));

		
	}
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