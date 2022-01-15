#include "CollMgr.h"
#include "SceneMgr.h"
#include"DestroyMgr.h"
CollMgr::CollMgr()
{
}

CollMgr::~CollMgr()
{
}

//´æ´¢ËùÓÐCollider¶ÔÏó
vector<Collider*> CollMgr::Colliders;
//Åö×²¼ì²âº¯Êý,±éÀúColliders,½øÐÐÅö×²¼ì²â
void CollMgr::CollisionDetec() {
	if (CollMgr::Colliders.empty()) {
		return;
	}
	for (vector<Collider*>::iterator it = CollMgr::Colliders.begin(); it != CollMgr::Colliders.end(); ++it)
	{
		for (vector<Collider*>::iterator it2 = it + 1; it2 != CollMgr::Colliders.end(); ++it2)
		{
			//Ì«ÑôµØÇò(Åö×²Çò)µ¥¶À¼ì²âÅö×²
			if ((*it2)->tag == "sun") {
				CVector PA[8] = {
					CVector((*it)->minXYZ.x, (*it)->minXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->minXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->maxXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->maxXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->minXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->minXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->maxXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->maxXYZ.y, (*it)->maxXYZ.z),
				};

				CMatrix m = (*it)->transform->rotation.ToCMatrix();
				for (int i = 0; i < 8; ++i) {
					PA[i] = m.posMul(PA[i]);
					PA[i] = PA[i] + (*it)->transform->position;
					if ((PA[i] - SceneMgr::sun->transform->position).len() <= SceneMgr::sun->radius) {
						(*it)->Collision(*it2);
					}
				}
			}
			else if ((*it2)->tag == "earth") {
				CVector PA[8] = {
					CVector((*it)->minXYZ.x, (*it)->minXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->minXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->maxXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->minXYZ.x, (*it)->maxXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->minXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->minXYZ.y, (*it)->maxXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->maxXYZ.y, (*it)->minXYZ.z),
					CVector((*it)->maxXYZ.x, (*it)->maxXYZ.y, (*it)->maxXYZ.z),
				};
				CMatrix m = (*it)->transform->rotation.ToCMatrix();
				for (int i = 0; i < 8; ++i) {
					PA[i] = m.posMul(PA[i]);
					PA[i] = PA[i] + (*it)->transform->position;
					if ((PA[i] - SceneMgr::earth->transform->position).len() <= SceneMgr::earth->radius) {
						//cout << "it2 = earth" << endl; 
						(*it)->Collision(*it2);
					}
				}
			}
			else if ((*it)->tag == "earth") {
				CVector PA[8] = {
					CVector((*it2)->minXYZ.x, (*it2)->minXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->minXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->maxXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->maxXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->minXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->minXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->maxXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->maxXYZ.y, (*it2)->maxXYZ.z),
				};

				CMatrix m = (*it2)->transform->rotation.ToCMatrix();
				for (int i = 0; i < 8; ++i) {
					PA[i] = m.posMul(PA[i]);
					PA[i] = PA[i] + (*it2)->transform->position;
					if ((PA[i] - SceneMgr::earth->transform->position).len() <= SceneMgr::earth->radius) {
						//cout << "it1 = earth" << endl; 
						(*it2)->Collision(*it);
					}
				}
			}
			else if ((*it)->tag == "sun") {
				CVector PA[8] = {
					CVector((*it2)->minXYZ.x, (*it2)->minXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->minXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->maxXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->minXYZ.x, (*it2)->maxXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->minXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->minXYZ.y, (*it2)->maxXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->maxXYZ.y, (*it2)->minXYZ.z),
					CVector((*it2)->maxXYZ.x, (*it2)->maxXYZ.y, (*it2)->maxXYZ.z),
				};

				CMatrix m = (*it2)->transform->rotation.ToCMatrix();
				for (int i = 0; i < 8; ++i) {
					PA[i] = m.posMul(PA[i]);
					PA[i] = PA[i] + (*it2)->transform->position;
					if ((PA[i] - SceneMgr::sun->transform->position).len() <= SceneMgr::sun->radius) {
						(*it2)->Collision(*it);
					}
				}
			}
			//·¢ÉúÅö×²
			else if (Collider::Collide(*it, *it2)) {
				(*it)->Collision(*it2);
				(*it2)->Collision(*it);
			}
		}
	}
}
//É¾³ýÅö×²Æ÷
void CollMgr::DestroyCollider(Collider* col) {
	DestroyMgr::add(col);
}