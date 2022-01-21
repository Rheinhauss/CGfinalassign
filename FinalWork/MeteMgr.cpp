#include "MeteMgr.h"
#include "DestroyMgr.h"
#include "SceneMgr.h"

MeteMgr::MeteMgr()
{
}

MeteMgr::~MeteMgr()
{
}

//陨石列表, 所有陨石均需加入此列表
vector<Meteorite*> MeteMgr::Metes;
//陨石活动范围
vector<MeteRange*> MeteMgr::MeteRanges;
//删除陨石
void MeteMgr::DestroyMete(Meteorite* m) {
	DestroyMgr::add(m);
}
//初始化边界和陨石
void MeteMgr::Init() {
	//生成2个陨石带
	MeteRanges.push_back(new MeteRange(50, 80));
	MeteRanges.push_back(new MeteRange(120, 200));
	//在陨石带中生成陨石
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
}
void MeteMgr::add() {	
	//设置所属陨石带
	auto p = new Meteorite(MeteRanges[SceneMgr::randint() % MeteRanges.size()]);
	//设置Transform,位置在陨石带内,旋转为前进方向,设置scale,使不同陨石大小不一致
	//更改scale的时候还需要更改minXYZ,maxXYZ
	double b = (SceneMgr::random(false) / 1.5) * ((SceneMgr::randint() % 2 == 0) ? 1.0 : -1.0) + 2.0;
	p->transform->scale = p->transform->scale * b;
	p->minXYZ = p->minXYZ * b;
	p->     maxXYZ = p->maxXYZ * b;
}
