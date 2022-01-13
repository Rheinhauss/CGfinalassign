#include "CMatrix.h"

CMatrix::CMatrix()
{
}

CMatrix::~CMatrix()
{
}

CMatrix::CMatrix(float* p) {
	this->SetMatrix(p);
}
CMatrix::CMatrix(const CMatrix& p) {
	this->m00 = p.m00;
	this->m10 = p.m10;
	this->m20 = p.m20;
	this->m30 = p.m30;
	this->m01 = p.m01;
	this->m11 = p.m11;
	this->m21 = p.m21;
	this->m31 = p.m31;
	this->m02 = p.m02;
	this->m12 = p.m12;
	this->m22 = p.m22;
	this->m32 = p.m32;
	this->m03 = p.m03;
	this->m13 = p.m13;
	this->m23 = p.m23;
	this->m33 = p.m33;
}

//给矩阵16个元素赋值
void CMatrix::SetMatrix(float *p) {
	for (int i = 0; i < 16; ++i)
		(*this)[i] = p[i];
}

void CMatrix::ToIndentity() {
	for (int i = 0; i < 16; ++i)
		(*this)[i] = 0;
	this->m00 = this->m11 = this->m22 = this->m33 = 1;
}

//矩阵赋值
CMatrix CMatrix::operator=(CMatrix& p) {
	for (int i = 0; i < 16; ++i)
		(*this)[i] = p[i];
	return CMatrix(*this);
}

//矩阵数乘
CMatrix CMatrix::operator*(float d) {
	CMatrix t;
	for (int i = 0; i < 16; ++i)
		t[i] = (*this)[i] * d;
	return t;
}
CMatrix operator*(const float num, CMatrix& p) {
	return p*num;
}

//矩阵相乘
CMatrix CMatrix::operator*(CMatrix& p) {
	CMatrix t;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			t[i * 4 + j] = 0;
			for (int num = 0; num < 4; ++num)
				t[i * 4 + j] += (*this)[num * 4 + j] * p[i * 4 + num];
		}
	return t;
}

//矩阵与向量相乘
CVector CMatrix::vecMul(CVector& p) {//补0
	float tmp[4] = { p[0],p[1],p[2],0 };
	float temp[4];
	for (int j = 0; j < 4; ++j) {
		temp[j] = 0;
		for (int num = 0; num < 4; ++num)
			temp[j] += (*this)[num * 4 + j] * tmp[num];
	}
	CVector t(temp[0], temp[1], temp[2]);
	return t;
}

//矩阵与点相乘
CVector CMatrix::posMul(CVector& p) {//补1
	float tmp[4] = { p[0],p[1],p[2],1 };
	float temp[4];
	for (int j = 0; j < 4; ++j) {
		temp[j] = 0;
		for (int num = 0; num < 4; ++num)
			temp[j] += (*this)[num * 4 + j] * tmp[num];
	}
	CVector t(temp[0], temp[1], temp[2]);
	return t;
}

//设置为旋转矩阵
void CMatrix::SetRotate(float seta, CVector axis) {
	axis.Normalize();//转为单位向量
	float COSSeta = cosf(seta/180*PI);
	float SINSeta = sinf(seta/180*PI);
	(*this)[0 * 4 + 0] = axis.x*axis.x*(1 - COSSeta) + COSSeta;
	(*this)[1 * 4 + 0] = axis.x*axis.y*(1 - COSSeta) - axis.z*SINSeta;
	(*this)[2 * 4 + 0] = axis.x*axis.z*(1 - COSSeta) + axis.y*SINSeta;
	(*this)[3 * 4 + 0] = 0;
	(*this)[0 * 4 + 1] = axis.x*axis.y*(1 - COSSeta) + axis.z*SINSeta;
	(*this)[1 * 4 + 1] = axis.y*axis.y*(1 - COSSeta) + COSSeta;
	(*this)[2 * 4 + 1] = axis.z*axis.y*(1 - COSSeta) - axis.x*SINSeta;
	(*this)[3 * 4 + 1] = 0;
	(*this)[0 * 4 + 2] = axis.x*axis.z*(1 - COSSeta) - axis.y*SINSeta;
	(*this)[1 * 4 + 2] = axis.z*axis.y*(1 - COSSeta) + axis.x*SINSeta;
	(*this)[2 * 4 + 2] = axis.z*axis.z*(1 - COSSeta) + COSSeta;
	(*this)[3 * 4 + 2] = 0;
	(*this)[0 * 4 + 3] = 0;
	(*this)[1 * 4 + 3] = 0;
	(*this)[2 * 4 + 3] = 0;
	(*this)[3 * 4 + 3] = 1;
}

//设置为平移矩阵
void CMatrix::SetTrans(CVector trans) {
	(*this)[0 * 4 + 0] = 1;
	(*this)[0 * 4 + 1] = 0;
	(*this)[0 * 4 + 2] = 0;
	(*this)[0 * 4 + 3] = 0;
	(*this)[1 * 4 + 0] = 0;
	(*this)[1 * 4 + 1] = 1;
	(*this)[1 * 4 + 2] = 0;
	(*this)[1 * 4 + 3] = 0;
	(*this)[2 * 4 + 0] = 0;
	(*this)[2 * 4 + 1] = 0;
	(*this)[2 * 4 + 2] = 1;
	(*this)[2 * 4 + 3] = 0;
	(*this)[3 * 4 + 0] = trans.x;
	(*this)[3 * 4 + 1] = trans.y;
	(*this)[3 * 4 + 2] = trans.z;
	(*this)[3 * 4 + 3] = 1;
}

//设置为缩放矩阵
void CMatrix::SetScale(CVector p) {
	(*this)[0 * 4 + 0] = p.x;
	(*this)[1 * 4 + 0] = 0;
	(*this)[2 * 4 + 0] = 0;
	(*this)[3 * 4 + 0] = 0;
	(*this)[0 * 4 + 1] = 0;
	(*this)[1 * 4 + 1] = p.y;
	(*this)[2 * 4 + 1] = 0;
	(*this)[3 * 4 + 1] = 0;
	(*this)[0 * 4 + 2] = 0;
	(*this)[1 * 4 + 2] = 0;
	(*this)[2 * 4 + 2] = p.z;
	(*this)[3 * 4 + 2] = 0;
	(*this)[0 * 4 + 3] = 0;
	(*this)[1 * 4 + 3] = 0;
	(*this)[2 * 4 + 3] = 0;
	(*this)[3 * 4 + 3] = 1;
}

float Det3(float *p) {
	return p[0 * 3 + 0] * (p[1 * 3 + 1] * p[2 * 3 + 2] - p[2 * 3 + 1] * p[1 * 3 + 2]) +
		p[1 * 3 + 0] * (p[2 * 3 + 1] * p[0 * 3 + 2] - p[0 * 3 + 1] * p[2 * 3 + 2]) +
		p[2 * 3 + 0] * (p[0 * 3 + 1] * p[1 * 3 + 2] - p[1 * 3 + 1] * p[0 * 3 + 2]);
}
//返回行列式的值
float CMatrix::Det4() {
	float det = 0;
	float p1[9] = {
		(*this)[1 * 4 + 1],(*this)[2 * 4 + 1],(*this)[3 * 4 + 1],
		(*this)[1 * 4 + 2],(*this)[2 * 4 + 2],(*this)[3 * 4 + 2],
		(*this)[1 * 4 + 3],(*this)[2 * 4 + 3],(*this)[3 * 4 + 3],
	};
	float p2[9] = {
		(*this)[0 * 4 + 1],(*this)[2 * 4 + 1],(*this)[3 * 4 + 1],
		(*this)[0 * 4 + 2],(*this)[2 * 4 + 2],(*this)[3 * 4 + 2],
		(*this)[0 * 4 + 3],(*this)[2 * 4 + 3],(*this)[3 * 4 + 3],
	};
	float p3[9] = {
		(*this)[0 * 4 + 1],(*this)[1 * 4 + 1],(*this)[3 * 4 + 1],
		(*this)[0 * 4 + 2],(*this)[1 * 4 + 2],(*this)[3 * 4 + 2],
		(*this)[0 * 4 + 3],(*this)[1 * 4 + 3],(*this)[3 * 4 + 3],
	};
	float p4[9] = {
		(*this)[0 * 4 + 1],(*this)[1 * 4 + 1],(*this)[2 * 4 + 1],
		(*this)[0 * 4 + 2],(*this)[1 * 4 + 2],(*this)[2 * 4 + 2],
		(*this)[0 * 4 + 3],(*this)[1 * 4 + 3],(*this)[2 * 4 + 3],
	};
	det = (*this)[0*4] * Det3(p1) - (*this)[1*4] * Det3(p2) + (*this)[2*4] * Det3(p3) - (*this)[3*4] * Det3(p4);
	return det;
}


//矩阵求逆，成功返回行列式的值，否则返回0，改变自身
float CMatrix::Inverse() {
	float det = this->Det4();
	if (det == 0)
		return 0;
	CMatrix Adjoint_Matrix;

	float p[9];
	//i行 ，j列
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			int r = 0, c = 0;
			for (int x = 0; x < 3; ++x) {
				for (int y = 0; y < 3; ++y) {
					if (r == i) {
						--x;
						break;
					}
					if (c == j) {
						++c;
						--y;
						continue;
					}
					p[x * 3 + y] = (*this)[c * 4 + r];
					++c;
				}
				++r;
				c = 0;
			}
			Adjoint_Matrix[i * 4 + j] = Det3(p) / det;
			Adjoint_Matrix[i * 4 + j] *= (i + j) % 2 == 1 ? -1 : 1;
		}

	*this = Adjoint_Matrix;
	return det;
}

//返回逆矩阵，不改变自身
CMatrix CMatrix::GetInverse() {
	float det = this->Det4();
	CMatrix Adjoint_Matrix;
	float p[9];
	//i行 ，j列
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			int r = 0, c = 0;
			for (int x = 0; x < 3; ++x) {
				for (int y = 0; y < 3; ++y) {
					if (r == i) {
						--x;
						break;
					}
					if (c == j) {
						++c;
						--y;
						continue;
					}
					p[x * 3 + y] = (*this)[c * 4 + r];
					++c;
				}
				++r;
				c = 0;
			}
			Adjoint_Matrix[i * 4 + j] = Det3(p) / det;
			Adjoint_Matrix[i * 4 + j] *= (i + j) % 2 == 1 ? -1 : 1;
		}

	return Adjoint_Matrix;
}

//矩阵转欧拉角
CEuler CMatrix::ToCEuler() {
	//float y = atan2f(*this[0 * 4 + 2], sqrtf(*this[1 * 4 + 2] * *this[1 * 4 + 2] + *this[2 * 4 + 2] * *this[2 * 4 + 2]));
	//float x = atan2f(*this[1 * 4 + 2], *this[2 * 4 + 2]);
	//float z = atan2f(*this[0 * 4 + 1], *this[0 * 4 + 0]);
	//return CEuler(x, y, z);
	CMatrix t = *this;
	float p = asinf(-t[2 * 4 + 1]);
	if (fabsf(cosf(p)) < 0.001f) {
		float h = atan2f(-t[0 * 4 + 2], t[0 * 4 + 0]);
		return CEuler(h / PI * 180, p / PI * 180, 0);
	}
	else {
		float h = atan2f(t[2 * 4 + 0], t[2 * 4 + 2]);
		float b = atan2f(t[0 * 4 + 1], t[1 * 4 + 1]);
		return CEuler(h / PI * 180, p / PI * 180, b / PI * 180);
	}
}

//矩阵转四元数
CQuaternion CMatrix::ToCQuaternion() {
	CMatrix t = *this;
	float w = sqrtf(1 + t[0 * 4 + 0] + t[1 * 4 + 1] + t[2 * 4 + 2]) / 2;
	//w趋近于0
	if (fabs(w - 0) < 0.001f) {
		int flag = 0;
		if ((t[0 * 4 + 0] - t[1 * 4 * 1]) > 0.001f) {
			if ((t[0 * 4 + 0] - t[2 * 4 * 2]) > 0.001f) {
				flag = 0;//0最大
			}
			else {
				flag = 2;//2最大
			}
		}
		else {
			if ((t[2 * 4 + 2] - t[1 * 4 * 1]) > 0.001f) {
				flag = 2;//2最大
			}
			else {
				flag = 1;//1最大
			}
		}

		if (flag == 0) {
			float tmp  = sqrtf(1 + t[0 * 4 + 0] - t[1 * 4 * 1] - t[2 * 4 + 2]);
			w = (t[1 * 4 + 2] - t[2 * 4 + 1]) / tmp;
			float x = tmp / 4;
			float y = (t[2 * 4 + 0] - t[0 * 4 + 2]) / tmp;
			float z = (t[1 * 4 + 0] - t[0 * 4 + 1]) / tmp;
			return CQuaternion(x, y, z, w);

		}
		else if (flag == 1) {
			float tmp = sqrtf(1 - t[0 * 4 + 0] + t[1 * 4 * 1] - t[2 * 4 + 2]);
			w = (t[2 * 4 + 0] - t[0 * 4 + 2]) / tmp;
			float x = (t[1 * 4 + 0] - t[0 * 4 + 1]) / tmp;
			float y = tmp / 4;
			float z = (t[1 * 4 + 2] - t[2 * 4 + 1]) / tmp;
			return CQuaternion(x, y, z, w);
		}
		else {
			float tmp = sqrtf(1 - t[0 * 4 + 0] - t[1 * 4 * 1] + t[2 * 4 + 2]);
			w = (t[0 * 4 + 1] - t[1 * 4 + 0]) / tmp;
			float x = (t[2 * 4 + 0] - t[0 * 4 + 2]) / tmp;
			float y = (t[2 * 4 + 1] - t[1 * 4 + 2]) / tmp;
			float z =  tmp / 4;
			return CQuaternion(x, y, z, w);
		}
	}
	else {
		float x = (t[1 * 4 + 2] - t[2 * 4 + 1]) / (4 * w);
		float y = (t[2 * 4 + 0] - t[0 * 4 + 2]) / (4 * w);
		float z = (t[0 * 4 + 1] - t[1 * 4 + 0]) / (4 * w);
		return CQuaternion(x, y, z, w);
	}
}
