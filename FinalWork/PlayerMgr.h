#pragma once
#include "Aircraft.h"
#include "Bullet.h"
#include "Camera.h"
#include <vector>

class PlayerMgr
{
public:
	PlayerMgr();
	~PlayerMgr();

	//��Ҳ��ݵķɻ�
	static Aircraft *Player;
	//�ӵ��б�, ���з�����ӵ������ڴ˵Ǽ�
	static vector<Bullet*> bullets;
	//��ײ��ʯ����
	static int colMeteNum;
	//��ײ�л�����
	static int colEnemyNum;
	//���ел�����
	static int hitEnemyNum;
	//��Ϸ��ʱ
	static Timer* timeUsed;

	static Camera* camera;

	static bool isChasing;


	//ɾ���ӵ�
	static void DestroyBullet(Bullet* b);
	static bool raypicking(int window_x, int window_y, int width, int height);


private:

};

