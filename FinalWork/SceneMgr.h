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

	static CMatrix ProjMatrix,ViewMatrix;
	static float ProjMatrixArrPtr[16],ViewMatrixArrPtr[16];

	static int w, h;
	//���������
	static double random(bool);
	static int randint();
	static void InitTexture();
	static void updateProjMatrixInThis();	
	static void updateViewMatrixInThis();

private:

};

