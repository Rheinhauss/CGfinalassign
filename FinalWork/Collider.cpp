#include "Collider.h"
#include "CMatrix.h"

Collider::Collider()
{
	//������ײ�� �б�
	CollMgr::Colliders.push_back(this);
	//Ĭ�ϴ�С
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
//������ײʱ����,����Ϊ��ײ������,ʵ�ּ���,CollMgr�Զ�����
void Collider::Collision(Collider *col) {
	return;
}
//���A��B�Ƿ�����ײ,�����򷵻�true,���򷵻�false
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