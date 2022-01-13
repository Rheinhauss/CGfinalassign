#pragma once
#include <vector>
#include "Collider.h"
class Collider;

class CollMgr
{
public:
	CollMgr();
	~CollMgr();

	//存储所有Collider对象
	static vector<Collider*> Colliders;
	//碰撞检测函数,遍历Colliders,进行碰撞检测
	static void CollisionDetec();
	//删除碰撞器
	static void DestroyCollider(Collider *col);

private:

};

