#pragma once
#include "glew.h"
#include "glut.h"
class TextureMgr
{
public:
	static void init();
	static GLuint textures[10];//��������
	static GLUquadricObj* e_tex;
};

