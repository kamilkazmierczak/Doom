#include <iostream>
#include "GameManager.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <math.h>
#include <time.h>  
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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>


#include <vector>
#include <string>

int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();


	//GLfloat ammo = 1123.56123f;



	//string text = to_string(ammo).substr(0, to_string(ammo).find_last_of("."));


	//cout << text << endl;


	/*vec3 rr = vec3(0.0f, 0.0f, 0.0f);
	vec3 tt = vec3(0.0f, 1.0f, 1.0f);


	GLfloat dis = glm::distance(rr, tt);

	cout << dis << endl;*/

	//glfwInit();
	//GLfloat lastTime = glfwGetTime();
	//while (true)
	//{
	//	if (lastTime + 5.0f < glfwGetTime())
	//	{
	//		cout << "minelo 5s" << endl;
	//	}
	//}




	//srand(time(NULL));
	//
	//while (true)
	//{
	//	cout << rand() % 90 + 1 << endl;
	//	Sleep(100);
	//}

	//vec2 u = vec2(1.0f, 1.0f);
	//GLfloat angle = 90.0f;
	//vec2 v = -vec2(u.x * cos(glm::radians(angle)) - u.y * sin(glm::radians(angle)), u.x * sin(glm::radians(angle)) + u.y * cos(glm::radians(angle)));

	//cout << "new vector" << endl;
	//cout << to_string(v) << endl;

	//vec2 v = vec2(1.0f, 1.0f);
	//GLfloat angle = -1 * 180 / pi<GLfloat>() * fmodf(atan2(u.x*v.y - v.x*u.y, u.x*v.x + u.y*v.y), 2 * pi<GLfloat>());

	//vec2 v;

	//mat2 rotationM;
	//rotationM = rotate(rotationM, radians(angle), vec2(1.0f, 0.0f));

		//model = rotate(model, radians(angle), vec2(1.0f, 0.0f));
	//model = translate(model, vec3(entity->getPosition().x, entity->getPosition().y, entity->getPosition().z));

	//v.x = cos(angle);
//	v.y = sin(angle);




	
	//cout << to_string(v) << endl;
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