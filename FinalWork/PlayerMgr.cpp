#include"glew.h"
#include "glut.h"
#include "CEuler.h"
#include"CMatrix.h"
#include "CVector.h"
#include"CQuaternion.h"
#include "PlayerMgr.h"
#include "DestroyMgr.h"
#include "SceneMgr.h"
#include "EnemyMgr.h"
#include "Camera.h"
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
//游戏开始后经过时间
Timer* PlayerMgr::timeUsed;

Camera* PlayerMgr::camera;

//删除子弹
void PlayerMgr::DestroyBullet(Bullet* b) {
	DestroyMgr::add(b);
}

bool PlayerMgr::raypicking(int mouse_x, int mouse_y, int width, int height) {
	float x = (2.0f * mouse_x) / width - 1.0f;
	float y = 1.0f - (2.0f * mouse_y) / height;
	float z = 1.0f;
	CVector ray_nds(x, y, z);
	CVector ray_clip(x, y, -1.0);//point
	CMatrix proj; 
	glGetFloatv(GL_PROJECTION_MATRIX, proj);
	CVector ray_eye = proj.GetInverse().posMul(ray_clip);
	ray_eye = CVector(ray_eye.x, ray_eye.y, -1.0);//vector
	CVector ray_wor = (SceneMgr::ViewMatrix.GetInverse().vecMul(ray_eye)).Normalized();
	CVector ray_pos = camera->transform->position; 
	Enemy* enemy_picked = nullptr;
	bool found = false;
	for (auto e: EnemyMgr::Enemys) {
		CVector Amax = e->maxXYZ;
		CVector Amin = e->minXYZ;
		CMatrix mA = e->transform->rotation.ToCMatrix();
		Amax = mA.posMul(Amax);
		Amin = mA.posMul(Amin);
		Amax = Amax + e->transform->position;
		Amin = Amin + e->transform->position;
		CVector AAmax, AAmin;
		AAmax.x = max(Amax.x, Amin.x);
		AAmax.y = max(Amax.y, Amin.y);
		AAmax.z = max(Amax.z, Amin.z);
		AAmin.x = min(Amax.x, Amin.x);
		AAmin.y = min(Amax.y, Amin.y);
		AAmin.z = min(Amax.z, Amin.z);
		Amax = AAmax;
		Amin = AAmin;

		float t1 = (Amin.x - ray_pos.x) / ray_wor.x;
		float t2 = (Amax.x - ray_pos.x) / ray_wor.x;
		float t3 = (Amin.y - ray_pos.y) / ray_wor.y;
		float t4 = (Amax.y - ray_pos.y) / ray_wor.y;
		float t5 = (Amin.z - ray_pos.z) / ray_wor.z;
		float t6 = (Amax.z - ray_pos.z) / ray_wor.z;

		float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
		float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

		// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behinding us
		if (tmax < 0) {
			continue;
		}

		// if tmin > tmax, ray doesn't intersect AABB
		if (tmin > tmax) {
			continue;
		}
		found = true;
		enemy_picked = e;
	}
	if (found) {
		cout << "found!" << endl;
		PlayerMgr::Player->target = enemy_picked;
		PlayerMgr::Player->isChasing = true;
	}
	return found;
}