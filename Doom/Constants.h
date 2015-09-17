#pragma once
#include  <GLFW\glfw3.h>
const GLuint WIDTH = 800, HEIGHT = 600;
const GLfloat UpdatesPerSecond = 60.0f;
const vec3 CameraPosition = vec3(0.0f, 0.0f, 2.0f);
//const GLfloat CameraSpeed = 2.0f;
const bool FpsCamera = false;
const bool Show_Bounding_Boxes = true;
const GLfloat BulletSpeed = 0.08f;

/*
#error C1189: #error :  gl.h included before glew.h
- Entity musi byc zadeklarowane przed Vector3 i Vector4 
- dla bezpieczenstwa <GLFW\glfw3.h> dodawac jako ostatni





*/