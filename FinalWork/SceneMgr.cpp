#include "SceneMgr.h"
#include <ctime>
using namespace std;

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
}

//太阳
Sun* SceneMgr::sun;
//地球
Earth* SceneMgr::earth;
//天空盒
SkyBox* SceneMgr::skybox;

//返回随机数
double SceneMgr::random() {
	srand((int)time(0)); 
	return rand() % (10000) / (double)10000;
}
//%10000
int SceneMgr::randint() {
	srand((int)(time(0)*1000));
	return rand() % (10000);
}