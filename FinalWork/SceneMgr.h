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

	//̫��
	static Sun *sun;
	//����
	static Earth *earth;
	//��պ�
	static SkyBox *skybox;
	static std::default_random_engine generator;
	static std::uniform_int_distribution<int> distribution_int;
	static std::uniform_int_distribution<float> distribution_fp;


	//���������
	static double random();
	static int randint();

private:

};

