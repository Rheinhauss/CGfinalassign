#pragma once
#include "Sun.h"
#include "Earth.h"
#include "SkyBox.h"

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

	//���������
	static double random();
	static int randint();

private:

};

