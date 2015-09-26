#include <iostream>
#include "GameManager.h"
#include <cmath>
#include <math.h>
#include <time.h>  
#include <vector>
#include <string>

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();

	return 0;
}