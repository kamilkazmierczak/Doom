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


#include <vector>

int main(int argc, char **argv)
{

	GameManager *gameManager = &GameManager::getGameManager();
	gameManager->runGameLoop();
	GameManager::destroyGameManager();

	//vector<int>* wektor = new vector<int>();

	//wektor->push_back(10);
	//wektor->push_back(11);
	//wektor->push_back(12);
	//wektor->push_back(13);



	//int distance = 0;

	//for (vector<int>::iterator iterator = wektor->begin(); iterator != wektor->end(); iterator++)
	//{
	//	//cout <<  *iterator << endl;
	//	//(*iterator) += 5;
	//	cout << std::distance(wektor->begin(), iterator) << endl;
	//	distance = std::distance(wektor->begin(), iterator);

	//	for (vector<int>::iterator iterator = wektor->begin(); iterator != wektor->end(); iterator++)
	//	{
	//		if (distance != std::distance(wektor->begin(), iterator))
	//		{
	//			if (*iterator == 12)
	//			{
	//				//cout << "O nie ! to 12" << endl;
	//				continue;
	//			}
	//			cout << *iterator << endl;
	//		}


	//		
	//	}

	//}

	/*for (vector<int>::iterator iterator = wektor->begin(); iterator != wektor->end(); iterator++)
	{
		cout << *iterator << endl;
	}*/









	//int i;
	//i = 5;

	//cout << i << endl;
	//cout << "test" << endl;
	//test(i);
	//cout << i << endl;


	//getchar();

	return 0;
}