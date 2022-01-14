#include "PlayerMgr.h"
#include "DestroyMgr.h"
PlayerMgr::PlayerMgr()
{
}

PlayerMgr::~PlayerMgr()
{
}

//玩家操纵的飞机
Aircraft* PlayerMgr::Player;
//子弹列表, 所有发射的子弹均需在此登记
vector<Bullet*> PlayerMgr::bullets;
//碰撞陨石次数
int PlayerMgr::colMeteNum = 0;
//碰撞敌机次数
int PlayerMgr::colEnemyNum = 0;
//击中敌机次数
int PlayerMgr::hitEnemyNum = 0;

//删除子弹
void PlayerMgr::DestroyBullet(Bullet* b) {
	DestroyMgr::add(b);
}
 