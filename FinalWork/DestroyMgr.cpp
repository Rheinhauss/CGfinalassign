#include "DestroyMgr.h"

DestroyMgr::DestroyMgr()
{
}

DestroyMgr::~DestroyMgr()
{
}

vector<Object*> DestroyMgr::objs;
void DestroyMgr::DestroyObj() {
	for (vector<Object*>::iterator it = objs.begin(); it != objs.end(); ++it) {
		delete (*it);
	}
	objs.clear();
}
void DestroyMgr::add(Object*a) {
	for (auto v : DestroyMgr::objs) {
		if (v == a)
			return;
	}
 	DestroyMgr::objs.push_back(a);
}