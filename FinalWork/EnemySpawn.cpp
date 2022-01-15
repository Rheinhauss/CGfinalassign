#include "EnemySpawn.h"
#include "EnemyMgr.h"

EnemySpawn::EnemySpawn(CVector&v)
{
	CMatrix m;
	m.SetRotate(0, CVector(0, 1, 0));
	this->transform->position = v;
	this->transform->rotation = m.ToCQuaternion();
	EnemyMgr::EnemySpawns.push_back(this);
}

EnemySpawn::~EnemySpawn()
{
}