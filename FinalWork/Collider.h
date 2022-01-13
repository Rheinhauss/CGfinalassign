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
	//������ײʱ����,����Ϊ��ײ������,ʵ�ּ���,CollMgr�Զ�����
	virtual void Collision(Collider *col);
	//���A��B�Ƿ�����ײ,�����򷵻�true,���򷵻�false
	static bool Collide(Collider *A, Collider *B);

private:

};

