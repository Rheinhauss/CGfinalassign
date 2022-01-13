#include "Transform.h"
#include "CEuler.h"

Transfrom::Transfrom()
{
	this->position = CVector(0, 0, 0);
	this->rotation = CEuler(0, 0, 0).ToQuaternion();
	this->scale = CVector(1, 1, 1);
}

Transfrom::~Transfrom()
{
}
