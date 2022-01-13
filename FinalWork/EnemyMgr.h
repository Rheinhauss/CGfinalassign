#pragma once
#include <vector>
#include "EnemySpawn.h"
#include "Enemy.h"

class EnemyMgr
{
public:
	EnemyMgr();
	~EnemyMgr();

	//敌机生成点列表, 所有敌机生成点均需在此登记
	static vector<EnemySpawn*> EnemySpawns;
	//敌机列表, 所有生成的敌机均需在此登记
	static vector<Enemy*> Enemys;
	//当前敌机数
	static int curEnemyNum;
	//最大敌机数
	static int maxEnemyNum;
	//敌机生成时间间隔
	static double timeInterval;
	//敌机生成计时器
	static Timer* timer;
	//每帧调用
	static void CreateEnemy();
	//删除敌机
	static void DestroyEnemy(Enemy *e);
	//初始化,开始生成一定数量敌机生成点和敌机
	static void Init();

private:

};

