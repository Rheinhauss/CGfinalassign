#include "MeteMgr.h"
#include "DestroyMgr.h"
#include "SceneMgr.h"

MeteMgr::MeteMgr()
{
}

MeteMgr::~MeteMgr()
{
}

//��ʯ�б�, ������ʯ���������б�
vector<Meteorite*> MeteMgr::Metes;
//��ʯ���Χ
vector<MeteRange*> MeteMgr::MeteRanges;
//ɾ����ʯ
void MeteMgr::DestroyMete(Meteorite* m) {
	DestroyMgr::add(m);
}
//��ʼ���߽����ʯ
void MeteMgr::Init() {
	//����2����ʯ��
	MeteRanges.push_back(new MeteRange(50, 80));
	MeteRanges.push_back(new MeteRange(120, 200));
	//����ʯ����������ʯ
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
	add(); add(); add(); add(); add();
}
void MeteMgr::add() {	
	//����������ʯ��
	auto p = new Meteorite(MeteRanges[SceneMgr::randint() % MeteRanges.size()]);
	//����Transform,λ������ʯ����,��תΪǰ������,����scale,ʹ��ͬ��ʯ��С��һ��
	//����scale��ʱ����Ҫ����minXYZ,maxXYZ
	double b = (SceneMgr::random(false) / 1.5) * ((SceneMgr::randint() % 2 == 0) ? 1.0 : -1.0) + 2.0;
	p->transform->scale = p->transform->scale * b;
	p->minXYZ = p->minXYZ * b;
	p->     maxXYZ = p->maxXYZ * b;
}
