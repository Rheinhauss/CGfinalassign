#pragma once
#include "Sun.h"
#include "Earth.h"
#include "SkyBox.h"
#include <random>

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
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution_int;
	static std::uniform_int_distribution<float> distribution_fp;


	//返回随机数
	static double random();
	static int randint();

private:

};

