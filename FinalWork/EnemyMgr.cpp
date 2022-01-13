#include "EnemyMgr.h"
#include "SceneMgr.h"

EnemyMgr::EnemyMgr()
{
}

EnemyMgr::~EnemyMgr()
{
}


//敌机生成点列表, 所有敌机生成点均需在此登记
vector<EnemySpawn*> EnemyMgr::EnemySpawns;
//敌机列表, 所有生成的敌机均需在此登记
vector<Enemy*> EnemyMgr::Enemys;
//当前敌机数
int EnemyMgr::curEnemyNum = 0;
//最大敌机数
int EnemyMgr::maxEnemyNum = 20;
//敌机生成时间间隔
double EnemyMgr::timeInterval = 5;
//敌机生成计时器
Timer* EnemyMgr::timer = new Timer();
//每帧调用
void EnemyMgr::CreateEnemy() {
	if (EnemyMgr::curEnemyNum >= EnemyMgr::maxEnemyNum) {
		return;
	}
	//计时器时间 >= 间隔
	//是则生成
	if (timer->time < EnemyMgr::timeInterval) {
		return;
	}
	int n = (int)EnemyMgr::EnemySpawns.size();
	int index = (int)(SceneMgr::random() * n);
	Enemy* e = new Enemy();
	e->transform->position = EnemyMgr::EnemySpawns[index]->transform->position;
	e->transform->rotation = EnemyMgr::EnemySpawns[index]->transform->rotation;
	timer->start();//从0开始计时
}
//删除敌机
void EnemyMgr::DestroyEnemy(Enemy* e) {
	delete e;
}

//初始化,开始生成一定数量敌机生成点和敌机
void EnemyMgr::Init() {
	//产生一定数量的敌机生成点,并设置好位置与方位
	//new
	//set Transform,不需要手动加入列表

	//产生一定数量的初始化敌机
	//不需要更改当前数量
}