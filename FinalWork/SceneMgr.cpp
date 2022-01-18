#include "SceneMgr.h"
#include "TextureMgr.h"

using namespace std;

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

//̫��
Sun* SceneMgr::sun;
//����
Earth* SceneMgr::earth;
//��պ�
SkyBox* SceneMgr::skybox;
std::uniform_int_distribution<int> SceneMgr::distribution_int 
					= std::uniform_int_distribution<int>(0,9999);
std::default_random_engine SceneMgr::generator;
CMatrix SceneMgr::ProjMatrix;
float SceneMgr::ProjMatrixArrPtr[16] = {};
CMatrix SceneMgr::ViewMatrix;
float SceneMgr::ViewMatrixArrPtr[16] = {};

int SceneMgr::w;
int SceneMgr::h;
//���������
double SceneMgr::random(bool sign = false) {
	if (sign)
		return ((distribution_int(generator)%2 == 0) ? 1.0 : -1.0)
				* distribution_int(generator) / (double)9999;
	return distribution_int(generator) / (double)9999;
}
//%10000
int SceneMgr::randint() {
	return distribution_int(generator);
}

void SceneMgr::InitTexture() {
	TextureMgr::init();
}
void SceneMgr::updateProjMatrixInThis() {
	glGetFloatv(GL_PROJECTION_MATRIX, SceneMgr::ProjMatrixArrPtr);
	SceneMgr::ProjMatrix = CMatrix(ProjMatrixArrPtr);
}
void SceneMgr::updateViewMatrixInThis() {
	glGetFloatv(GL_MODELVIEW_MATRIX, SceneMgr::ViewMatrixArrPtr);
	SceneMgr::ViewMatrix = CMatrix(ViewMatrixArrPtr);
}