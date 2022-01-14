#pragma once
#include "Object.h"
#include <vector>
using namespace std;

class DestroyMgr
{
public:
	DestroyMgr();
	~DestroyMgr();

	static vector<Object*> objs;
	static void DestroyObj();
	static void add(Object*);

private:

};
