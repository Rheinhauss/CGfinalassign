#include "EnemySpawn.h"
#include "EnemyMgr.h"

EnemySpawn::EnemySpawn()
{
	EnemyMgr::EnemySpawns.push_back(this);
}

EnemySpawn::~EnemySpawn()
{
}