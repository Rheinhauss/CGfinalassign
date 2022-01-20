#pragma once
#include "glew.h"
#include "glut.h"
#include <atlimage.h>
#include "CEuler.h"
class Draw{
public:
	static void drawEarth(GLfloat radius, int lon, int lat);
	static int LoadEarth_GLTextures();

};

