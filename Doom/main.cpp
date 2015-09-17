#include <iostream>
#include "GameManager.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace std;
using namespace glm;
//void test(int& numer)
//{
//	//numer++;
//	int *n;
//	n = &numer;
//	(*n)++;
//
//}


#include <vector>

int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();



	/*vector<int> wektor;

	wektor.push_back(2);
	wektor.clear();

	for (vector<int>::iterator iterator = wektor.begin(); iterator != wektor.end(); iterator++)
	{
		cout << "jestem" << endl;
	}*/

	//GLfloat max;

	//max = cmp::max(0.0f, 1.0f);

	/*GLfloat num = -0.0f;
	cout << glm::sign(num) << endl;*/

	/*GLfloat num = -0.0000f;
	cout << sign(num) << endl;*/
	//cout << signbit(num) << endl;


	//getchar();

	return 0;
}