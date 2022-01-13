#pragma once
#include "Aircraft.h"
#include "Bullet.h"
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

	//ɾ���ӵ�
	static void DestroyBullet(Bullet* b);

private:

};

