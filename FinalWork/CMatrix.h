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

	//给矩阵16个元素赋值
	void SetMatrix(float *p);
	//矩阵赋值
	CMatrix operator=(CMatrix& p);
	//矩阵数乘
	CMatrix operator*(float d);
	friend CMatrix operator*(const float num, CMatrix& p);//重载 * 操作符 向量数乘
	//矩阵相乘
	CMatrix operator*(CMatrix& p);
	//矩阵与向量相乘
	CVector vecMul(CVector& p);
	//矩阵与点相乘
	CVector posMul(CVector& p);
	//设置为旋转矩阵
	void SetRotate(float seta, CVector axis);
	//设置为平移矩阵
	void SetTrans(CVector trans);
	//设置为缩放矩阵
	void SetScale(CVector p);
	//矩阵求逆，成功返回行列式的值，否则返回0，改变自身
	float Inverse();
	//返回逆矩阵，不改变自身
	CMatrix GetInverse();
	//变化为单位矩阵
	void ToIndentity();

	//返回行列式的值
	float Det4();

	//矩阵转欧拉角
	CEuler ToCEuler();
	//矩阵转四元数
	CQuaternion ToCQuaternion();

	operator float*() {
		return &m00;
	}

private:

};

