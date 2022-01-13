#pragma once
#include "glew.h"
#include "glut.h"
#include <atlimage.h>
#include <iostream>
using namespace std;

class SkyBox {
public:
	SkyBox(char *front, char *back, char *top, char *bottom, char *left, char *right);
	SkyBox();
	~SkyBox();
	void CreateSkyBox();
	void setSkyBox(float vertical, float size);
private:
	bool LoadBitMapTexture(char* filename, GLuint &texture);
	void texture(GLuint &texture);
	float m_vertical;//纵向高度的调整
	float m_size;
	GLuint m_texture[6];
	char* m_front, *m_back, *m_top, *m_bottom, *m_left, *m_right;
	enum {
		SKY_TOP,
		SKY_BOTTOM,
		SKY_FRONT,
		SKY_BACK,
		SKY_LEFT,
		SKY_RIGHT
	};
};