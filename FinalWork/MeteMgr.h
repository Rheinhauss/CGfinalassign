#pragma once
#include <vector>
#include "MeteRange.h"
#include "Meteorite.h"

class MeteMgr
{
public:
	MeteMgr();
	~MeteMgr();

	//��ʯ�б�, ������ʯ���������б�
	static vector<Meteorite*> Metes;
	//��ʯ���Χ
	static vector<MeteRange*> MeteRanges;
	//ɾ����ʯ
	static void DestroyMete(Meteorite* m);
	//��ʼ���߽����ʯ
	static void Init();

private:

};

