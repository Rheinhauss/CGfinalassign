#include "EnemyMgr.h"
#include "SceneMgr.h"
#include "DestroyMgr.h"

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
int EnemyMgr::maxEnemyNum = 8;
//敌机生成时间间隔
double EnemyMgr::timeInterval = 1;
//敌机生成计时器
Timer* EnemyMgr::timer;
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
	add();
	timer->start();//从0开始计时
	
}
//删除敌机
void EnemyMgr::DestroyEnemy(Enemy* e) {
	DestroyMgr::add(e);
}

//初始化,开始生成一定数量敌机生成点和敌机
void EnemyMgr::Init() {
	new EnemySpawn(CVector(80, 0, 80));
	new EnemySpawn(CVector(-80, 0, 80));
	timer = new Timer();
	timer->start();
	add(); add(); add(); add();
	add(); add(); add(); add();
}
void EnemyMgr::add() {
	int n = (int)EnemyMgr::EnemySpawns.size();
	int index = (int)(SceneMgr::random(false) * n);
	Enemy* e = new Enemy();
	e->transform->position =
		EnemyMgr::EnemySpawns[index]->transform->position;
	//float seta = SceneMgr::random(false) * 360.0;
	//CMatrix m;
	//m.SetRotate(seta)
	e->transform->rotation =
		EnemyMgr::EnemySpawns[index]->transform->rotation;
}