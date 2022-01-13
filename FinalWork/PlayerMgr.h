#pragma once
#include "Aircraft.h"
#include "Bullet.h"
#include <vector>

class PlayerMgr
{
public:
	PlayerMgr();
	~PlayerMgr();

	//玩家操纵的飞机
	static Aircraft *Player;
	//子弹列表, 所有发射的子弹均需在此登记
	static vector<Bullet*> bullets;
	//碰撞陨石次数
	static int colMeteNum;
	//碰撞敌机次数
	static int colEnemyNum;
	//击中敌机次数
	static int hitEnemyNum;

	//删除子弹
	static void DestroyBullet(Bullet* b);

private:

};

