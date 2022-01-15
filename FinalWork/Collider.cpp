#include "Collider.h"
#include "CMatrix.h"

Collider::Collider()
{
	//加入碰撞器 列表
	CollMgr::Colliders.push_back(this);
	//默认大小
	minXYZ = CVector(-1, -1, -1);
	maxXYZ = CVector(1, 1, 1);
}

Collider::~Collider()
{
	for (vector<Collider*>::iterator it = CollMgr::Colliders.begin(); it != CollMgr::Colliders.end(); )
	{
		if (*it == this)
		{
			it = CollMgr::Colliders.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}
//发生碰撞时调用,参数为碰撞的物体,实现即可,CollMgr自动调用
void Collider::Collision(Collider *col) {
	return;
}
//检测A、B是否发生碰撞,发生则返回true,否则返回false
bool Collider::Collide(Collider *A, Collider *B) {
	CVector PA[8] = {
		CVector(A->minXYZ.x, A->minXYZ.y, A->minXYZ.z),
		CVector(A->minXYZ.x, A->minXYZ.y, A->maxXYZ.z),
		CVector(A->minXYZ.x, A->maxXYZ.y, A->minXYZ.z),
		CVector(A->minXYZ.x, A->maxXYZ.y, A->maxXYZ.z),
		CVector(A->maxXYZ.x, A->minXYZ.y, A->minXYZ.z),
		CVector(A->maxXYZ.x, A->minXYZ.y, A->maxXYZ.z),
		CVector(A->maxXYZ.x, A->maxXYZ.y, A->minXYZ.z),
		CVector(A->maxXYZ.x, A->maxXYZ.y, A->maxXYZ.z),
	};

	CVector Bmax = B->maxXYZ;
	CVector Bmin = B->minXYZ;
	CMatrix mB = B->transform->rotation.ToCMatrix();
	Bmax = mB.posMul(Bmax);
	Bmin = mB.posMul(Bmin);
	Bmax = Bmax + B->transform->position;
	Bmin = Bmin + B->transform->position;
	
	CMatrix mA = A->transform->rotation.ToCMatrix();
	for (int i = 0; i < 8; ++i) {
		PA[i] = mA.posMul(PA[i]);
		PA[i] = PA[i] + A->transform->position;
		if (PA[i].x <= Bmax.x && PA[i].x >= Bmin.x) {
			if (PA[i].y <= Bmax.y && PA[i].y >= Bmin.y) {
				if (PA[i].z <= Bmax.z && PA[i].z >= Bmin.z) {
					return true;
				}
			}
		}
	}
	return false;
}