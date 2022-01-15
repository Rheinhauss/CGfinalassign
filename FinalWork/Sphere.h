#pragma once
#include "glut.h"
class Sphere
{
	static void CalculateNormal(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]);
	static void normalize(GLfloat* v);
	static void applyUV(GLfloat* norm);

	static int nVert;
	static GLfloat(*vert)[3], (*norm)[3];

public:
	static void Draw(GLfloat radius, int lon, int lat, GLuint text);
};

