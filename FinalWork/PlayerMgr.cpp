#include "PlayerMgr.h"
#include "DestroyMgr.h"
PlayerMgr::PlayerMgr()
{
}

PlayerMgr::~PlayerMgr()
{
}

//��Ҳ��ݵķɻ�
Aircraft* PlayerMgr::Player;
//�ӵ��б�, ���з�����ӵ������ڴ˵Ǽ�
vector<Bullet*> PlayerMgr::bullets;
//��ײ��ʯ����
int PlayerMgr::colMeteNum = 0;
//��ײ�л�����
int PlayerMgr::colEnemyNum = 0;
//���ел�����
int PlayerMgr::hitEnemyNum = 0;

//ɾ���ӵ�
void PlayerMgr::DestroyBullet(Bullet* b) {
	DestroyMgr::add(b);
}
 