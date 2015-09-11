#include <iostream>
#include "GameManager.h"
using namespace std;


//void test(int& numer)
//{
//	//numer++;
//	int *n;
//	n = &numer;
//	(*n)++;
//
//}


int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();


	//int i;
	//i = 5;

	//cout << i << endl;
	//cout << "test" << endl;
	//test(i);
	//cout << i << endl;


	//getchar();

	return 0;
}