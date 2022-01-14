#include "MeteMgr.h"
#include "DestroyMgr.h"

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
	//生成2 - 3个陨石带,合适的数值即可

	//在陨石带中生成陨石
	//new
	//Meteorite* m = new Meteorite();
	//设置所属陨石带
	//设置Transform,位置在陨石带内,旋转为前进方向,设置scale,使不同陨石大小不一致
	//更改scale的时候还需要更改minXYZ,maxXYZ
}
