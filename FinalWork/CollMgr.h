#pragma once
#include <vector>
#include "Collider.h"
class Collider;

class CollMgr
{
public:
	CollMgr();
	~CollMgr();

	//�洢����Collider����
	static vector<Collider*> Colliders;
	//��ײ��⺯��,����Colliders,������ײ���
	static void CollisionDetec();
	//ɾ����ײ��
	static void DestroyCollider(Collider *col);

private:

};

