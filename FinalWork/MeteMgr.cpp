#include "MeteMgr.h"
#include "DestroyMgr.h"

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
	//����2 - 3����ʯ��,���ʵ���ֵ����

	//����ʯ����������ʯ
	//new
	//Meteorite* m = new Meteorite();
	//����������ʯ��
	//����Transform,λ������ʯ����,��תΪǰ������,����scale,ʹ��ͬ��ʯ��С��һ��
	//����scale��ʱ����Ҫ����minXYZ,maxXYZ
}
