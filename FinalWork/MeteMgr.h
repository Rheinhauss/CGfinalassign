#pragma once
#include <vector>
#include "MeteRange.h"
#include "Meteorite.h"

class MeteMgr
{
public:
	MeteMgr();
	~MeteMgr();

	//陨石列表, 所有陨石均需加入此列表
	static vector<Meteorite*> Metes;
	//陨石活动范围
	static vector<MeteRange*> MeteRanges;
	//删除陨石
	static void DestroyMete(Meteorite* m);
	//初始化边界和陨石
	static void Init();

private:

};

