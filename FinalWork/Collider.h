#pragma once
#include "Object.h"
#include "CVector.h"
#include "CollMgr.h"
class CollMgr;

class Collider : public Object
{
public:
	Collider();
	~Collider();

	CVector minXYZ;
	CVector maxXYZ;
	//发生碰撞时调用,参数为碰撞的物体,实现即可,CollMgr自动调用
	virtual void Collision(Collider *col);
	//检测A、B是否发生碰撞,发生则返回true,否则返回false
	static bool Collide(Collider *A, Collider *B);

private:

};

