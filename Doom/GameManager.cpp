#include "GameManager.h"
#include "Constants.h"
#include <time.h>
// Window dimensions



GameManager::GameManager(bool running)
	:_running(running), _window(glfwGetCurrentContext()), _renderSystem(&RenderSystem::getRenderSystem()),
	_resourceManager(&ResourceManager::getResourceManager()), _movementSystem(&MovementSystem::getMovementSystem()),
	_cameraSystem(&CameraSystem::getCameraSystem()), _scene(new Scene), _playerInputSystem(&PlayerInputSystem::getPlayerInputSystem()),
	_pause(true), _restart(false)
{
	TextRender *textRender = &TextRender::getTextRender();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textRender->renderText("PRESS ENTER", (WIDTH / 2) - 290.0f, HEIGHT / 2, 2.0f, glm::vec3(1.0, 0.7f, 0.2f));
	glfwSwapBuffers(_window);
}


GameManager::~GameManager()
{
	ResourceManager::destroyResourceManager();
	CameraSystem::destroyCameraSystem();
	RenderSystem::destroyRenderSystem();
	PlayerInputSystem::destroyPlayerInputSystem();
}


void GameManager::restartGame()
{
	vector<Entity*> *entityArray = _scene->getChildren();
	ResourceManager *resourceManager = &ResourceManager::getResourceManager();
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
	EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();
	Player *player = &Player::getPlayer();

	player->setAmmo(MaxAmmo);
	player->changeHealth(MaxHealth);

	//cameraSystem->getCurrentCamera()->setPosition(vec3(CameraPosition.x, CameraPosition.y, CameraPosition.z));
	
	cameraSystem->getCurrentCamera()->resetCamera();
	renderSystem->setFreshRender();
	environment->resetInformation();

	//usuniecie pozostalosci
	for (vector<Entity *>::iterator iterator = entityArray->begin(); iterator != entityArray->end();/**/)
	{
		Entity *entity = *iterator;
		bool destroy = false;

		if (entity->getType() == ENTITY_ENEMY)
		{
			ModelObject *enemyObj = nullptr;
			try { enemyObj = dynamic_cast<ModelObject*>(entity->getObject()); }
			catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }
			

			destroy = true;
			
		}

		if (entity->getType() == ENTITY_BULLET)
		{
			BulletObject *sphereObj = nullptr;
			try { sphereObj = dynamic_cast<BulletObject*>(entity->getObject()); }
			catch (bad_cast& bc){ cerr << "bad_cast caught: " << bc.what() << endl; }

			destroy = true;
		}

		if (destroy)
		{
			delete entity;
			iterator = entityArray->erase(iterator);
		}
		else
		{
			++iterator;
		}
	}
	//end of usuwanie pozostalosci


	//dalek1
	IObject *model = new ModelObject(resourceManager->getDalekArray()->at(0), new EnemyIntelligence());
	Entity *entity = new Entity(model, makeVector3(-5.0f, -1.5f, -8.5f), ENTITY_ENEMY);
	vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	vec2 v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	entityArray->push_back(entity);

	//dalek2
	model = new ModelObject(resourceManager->getDalekArray()->at(1), new EnemyIntelligence());
	entity = new Entity(model, makeVector3(5.0f, -1.5f, -8.5f), ENTITY_ENEMY);
	u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	entityArray->push_back(entity);







	setRestartState(false);
}





void GameManager::runGameLoop()
{
	// Deltatime
	GLfloat lastTime = glfwGetTime(); 
	_deltaTime = 0.0f; // Time between current frame and last frame

	

	while (_running)
	{	
			GLfloat currentTime = glfwGetTime();
			_deltaTime += (currentTime - lastTime) * UpdatesPerSecond;
			lastTime = currentTime;

			while (_deltaTime >= 1.0f)
			{
				_running = !glfwWindowShouldClose(_window);
				_movementSystem->update(_scene->getChildren());
				_playerInputSystem->update();

				--_deltaTime;
			}

			if (_pause == false)	
				_renderSystem->render(_scene->getChildren());
			

			if (getRestartState() == true)
			{
				restartGame();
			}
			


			glfwPollEvents();
	}
}


GLfloat GameManager::getDeltaTime()
{
	return _deltaTime;
}

Scene* GameManager::getScene()
{
	return _scene;
}


GameManager& GameManager::getGameManager()
{
	static GameManager *gameManager = NULL;

	if (gameManager == NULL){

		// Init GLFW
		glfwInit();

		srand(time(NULL));
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

		//do wyswietlania tekstu
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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


bool GameManager::getPauseState()
{
	return _pause;
}

void GameManager::setPauseState(bool option)
{
	_pause = option;
}


bool GameManager::getRestartState()
{
	return _restart;
}


void GameManager::setRestartState(bool option)
{
	_restart = option;
}


void GameManager::hi()
{
	//hi
}