#include <stdlib.h>
#include "GameManager.h"
#include "Constants.h"
#include "AudioSystem.h"
#include "R2D2Audio.h"
#include "EnemyAudio.h"
#include <time.h>


GameManager::GameManager(bool running)
	:_running(running), _window(glfwGetCurrentContext()), _renderSystem(&RenderSystem::getRenderSystem()),
	_resourceManager(&ResourceManager::getResourceManager()), _movementSystem(&MovementSystem::getMovementSystem()),
	_cameraSystem(&CameraSystem::getCameraSystem()), _scene(new Scene), _playerInputSystem(&PlayerInputSystem::getPlayerInputSystem()),
	_pause(true), _restart(false)
{
	TextRender *textRender = &TextRender::getTextRender();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	textRender->renderText("PRESS ENTER", (_Width / 2) - 290.0f, _Height / 2, 2.0f, glm::vec3(1.0, 0.7f, 0.2f));
	glfwSwapBuffers(_window);



}


GameManager::~GameManager()
{
	ResourceManager::destroyResourceManager();
	CameraSystem::destroyCameraSystem();
	RenderSystem::destroyRenderSystem();
	PlayerInputSystem::destroyPlayerInputSystem();
}

GLuint GameManager::_Width = 0;
GLuint GameManager::_Height = 0;

void GameManager::restartGame()
{
	AudioSystem *audioSystem = &AudioSystem::getAudioSystem();
	vector<Entity*> *entityArray = _scene->getChildren();
	ResourceManager *resourceManager = &ResourceManager::getResourceManager();
	CameraSystem *cameraSystem = &CameraSystem::getCameraSystem();
	RenderSystem *renderSystem = &RenderSystem::getRenderSystem();
	EnvironmentReactions *environment = &EnvironmentReactions::getEnvironmentReactions();
	Player *player = &Player::getPlayer();

	audioSystem->stopAllSounds();

	player->setAmmo(MaxAmmo);
	player->changeHealth(MaxHealth);

	
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

	GLfloat time = glfwGetTime();
	//dalek1
	IObject *model = new ModelObject(resourceManager->getDalekArray()->at(0), new EnemyIntelligence());
	Entity *entity = new Entity(model, makeVector3(-5.0f, -1.5f, -8.5f), ENTITY_ENEMY, new EnemyAudio(time));
	vec2 u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	vec2 v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	entityArray->push_back(entity);

	//dalek2
	model = new ModelObject(resourceManager->getDalekArray()->at(1), new EnemyIntelligence());
	entity = new Entity(model, makeVector3(5.0f, -1.5f, -8.5f), ENTITY_ENEMY, new EnemyAudio(time + 7.0f));
	u = vec2(0.0f, 1.0f); //wektor wskazujacy kierunek wzroku modelu
	v = normalize(vec2(CameraPosition.x, CameraPosition.z) - vec2(entity->getPosition().x, entity->getPosition().z));
	angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	entity->setRotation(makeVector3(0.0f, entity->getRotation().y + angle, 0.0f));
	entity->setScale(makeVector3(0.007f, 0.007f, 0.007f));
	entityArray->push_back(entity);

	
	audioSystem->playMusic(vec3(-9.2f, -1.5f, 5.5f));
	setRestartState(false);
}





void GameManager::runGameLoop()
{
	// Deltatime
	GLfloat lastTime = glfwGetTime(); 
	_deltaTime = 0.0f;

	while (_running)
	{	
			GLfloat currentTime = glfwGetTime();
			_deltaTime += (currentTime - lastTime) * UpdatesPerSecond;
			lastTime = currentTime;

			while (_deltaTime >= 1.0f)
			{
				if (_pause == false)
				{
					_running = !glfwWindowShouldClose(_window);
					_movementSystem->update(_scene->getChildren());
					_playerInputSystem->update();
				}
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

		glfwInit();

		srand(time(NULL));
		
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
		

		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		GLfloat monitorWidth = mode->width;
		GLfloat monitorHeight = mode->height;
		GLfloat centerX = monitorWidth / 2;
		GLfloat centerY = monitorHeight / 2;

		char decision;
	
		do{
			system("cls");
			cout << "Save R2D2 from army of Daleks" << endl;
			cout << "In every level you have to kill 10 daleks" << endl;
			cout << "There are 10 levels" << endl << endl;
			cout << "Movement: WSAD + Mouse" << endl;
			cout << "Shooting: Mouse or Space" << endl;
			cout << "Restart: R" << endl;
			cout << "Pause: P" << endl << endl;
			cout << "Fullscreen? (y/n)" << endl;
			cin >> decision;
		} while ((decision != 'y') && (decision != 'n'));

		if (decision == 'y')
		{
			GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "DOOM", glfwGetPrimaryMonitor(), nullptr);
			glfwMakeContextCurrent(window);		
			_Width = monitorWidth;
			_Height = monitorHeight;
		}
		else if (decision == 'n')
		{
			GLFWwindow* window = glfwCreateWindow(DefaultWidth, DefaultHeight, "DOOM", nullptr , nullptr);
			glfwSetWindowPos(window, centerX - (DefaultWidth / 2), centerY - (DefaultHeight / 2));
			glfwMakeContextCurrent(window);
			_Width = DefaultWidth;
			_Height = DefaultHeight;
		}
	
		AudioSystem *audioSystem = &AudioSystem::getAudioSystem();

		//do wyswietlania tekstu
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glewExperimental = GL_TRUE;
		glewInit();

		gameManager = new GameManager(true);
	}
	return *gameManager;
}

void GameManager::destroyGameManager()
{
	GameManager *gameManager = &getGameManager();
	delete gameManager;

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