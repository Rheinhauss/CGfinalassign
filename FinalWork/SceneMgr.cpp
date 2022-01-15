#include "SceneMgr.h"

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
//���������
double SceneMgr::random() {
	return distribution_int(generator) / (double)9999;
}
//%10000
int SceneMgr::randint() {
	return distribution_int(generator);
}