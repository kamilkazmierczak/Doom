#include <iostream>
#include "GameManager.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <math.h>
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
//#define PI 3.1415926535897932

#include <vector>

int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();


	//vec2 u = vec2(0.0f, 1.0f);
	//vec2 v = vec2(1.0f, 1.0f);
	//GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());
	//cout << "angle" << endl;
	//cout << angle << endl;






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