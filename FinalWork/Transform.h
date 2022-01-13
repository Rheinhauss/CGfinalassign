#pragma once
#include "CVector.h"
#include "CQuaternion.h"

class Transfrom
{
public:
	Transfrom();
	~Transfrom();

	CVector position;
	CQuaternion rotation;
	CVector scale;

private:

};

