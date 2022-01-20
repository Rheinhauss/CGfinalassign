#pragma once
#include "CVector.h"
#include "CQuaternion.h"

class Transform
{
public:
	Transform();
	~Transform();

	CVector position;
	CQuaternion rotation;
	CVector scale;

private:

};

