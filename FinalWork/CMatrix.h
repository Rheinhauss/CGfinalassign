#pragma once
#include "CVector.h"
#include "CEuler.h"
class CEuler;
#include "CQuaternion.h"
class CQuaternion;

class CMatrix
{
public:
	CMatrix();
	CMatrix(float* p);
	CMatrix(const CMatrix& p);
	~CMatrix();

	
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;

	//������16��Ԫ�ظ�ֵ
	void SetMatrix(float *p);
	//����ֵ
	CMatrix operator=(CMatrix& p);
	//��������
	CMatrix operator*(float d);
	friend CMatrix operator*(const float num, CMatrix& p);//���� * ������ ��������
	//�������
	CMatrix operator*(CMatrix& p);
	//�������������
	CVector vecMul(CVector& p);
	//����������
	CVector posMul(CVector& p);
	//����Ϊ��ת����
	void SetRotate(float seta, CVector axis);
	//����Ϊƽ�ƾ���
	void SetTrans(CVector trans);
	//����Ϊ���ž���
	void SetScale(CVector p);
	//�������棬�ɹ���������ʽ��ֵ�����򷵻�0���ı�����
	float Inverse();
	//��������󣬲��ı�����
	CMatrix GetInverse();
	//�仯Ϊ��λ����
	void ToIndentity();

	//��������ʽ��ֵ
	float Det4();

	//����תŷ����
	CEuler ToCEuler();
	//����ת��Ԫ��
	CQuaternion ToCQuaternion();

	operator float*() {
		return &m00;
	}

private:

};

