#include "SceneMgr.h"
#include <ctime>
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

//���������
double SceneMgr::random() {
	srand((int)time(0)); 
	return rand() % (10000) / (double)10000;
}