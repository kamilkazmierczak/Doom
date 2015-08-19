#include <iostream>
#include "GameManager.h"
using namespace std;



int main(int argc, char **argv)
{

	//nowe zmiany
	
	
	cout << "Co tam ciekawego !!" << endl;
	//wiecej zmian
	//<ciczior>

	//WIELKIE ZMIANY

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();
	return 0;
}