#include "Earth.h"

Earth::Earth()
{
	this->name = "earth";
	this->tag = "earth";
	this->radius = 400;
}

Earth::~Earth()
{
}

//���Ƶ�������+����������ͼ
void Earth::DrawEarth() {

}
//��̫����ת
void Earth::Move() {
	//̫��λ��ΪԲ��,����Բ���˶�
	//����pos
}
//��ת
void Earth::Rotate() {
	//����rot
}

//override
void Earth::Render() {
	DrawEarth();
}
void Earth::Update() {
	Move();
	Rotate();
}