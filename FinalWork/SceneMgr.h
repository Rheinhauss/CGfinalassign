#pragma once
#include "Sun.h"
#include "Earth.h"
#include "SkyBox.h"

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	//太阳
	static Sun *sun;
	//地球
	static Earth *earth;
	//天空盒
	static SkyBox *skybox;

	//返回随机数
	static double random();
	static int randint();

private:

};

