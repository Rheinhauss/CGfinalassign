#include "Path.h"
const static int PATH_MAX_LEN = 300;
Path::Path() {
	this->name = "path";
	this->tag = "path";
}
Path::~Path(){}

void Path::Render() {
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0.5, 0.5);
	glLineWidth(0.3);
	for (int i = 0; i < this->pathnodes.size(); i++) {
		glVertex3f(this->pathnodes[i].x, this->pathnodes[i].y, this->pathnodes[i].z);
	}
	glEnd();
}
void Path::Update() { return; }

void Path::update_path(CVector v) {
	if (pathnodes.size() < PATH_MAX_LEN)
		pathnodes.push_back(v);
	else {
		pathnodes.pop_front();
		pathnodes.push_back(v);
	}
}