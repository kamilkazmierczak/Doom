#pragma once
#include <GLFW/glfw3.h>

const GLfloat ShootingMultiplier = 5.0f; //nie wiem czemu nie da sie zaincludowac Constants.h

class LevelSystem
{
private:
	GLuint _currentLevel;
	GLuint _maxLevel;
	GLfloat _shootingVariable;
	bool _finalRound;

	LevelSystem();
	~LevelSystem();
public:

	void setLevel(GLuint level);
	GLfloat getShootingVariable();
	GLuint getCurrentLevel();
	GLuint getMaxLevel();
	bool getFinalRoundStatus();
	
	static LevelSystem& getLevelSystem();
	static void destroyLevelSystem();

};

