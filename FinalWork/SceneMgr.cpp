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