#pragma once
#include <iostream>
#define GLFW_INCLUDE_GLU //raczej zakazane bo chyba to gluLookAt

#include <vector>
#include "ShaderInterface.h"
#include "VertexBuffer.h"
#include <GLFW/glfw3.h>
//#include "GameManager.h" //po wysokosc i szerokosc do raczej zakazanych funkcji
using namespace std;

class RenderSystem
{

private:

	GLFWwindow *_window;

	vector<ShaderInterface *> *shaderArray;

	RenderSystem();
	~RenderSystem();

public:

	void render(VertexBuffer *vertexBuffer);
	static RenderSystem& getRenderSystem();
	static void destroyRenderSystem();

};

