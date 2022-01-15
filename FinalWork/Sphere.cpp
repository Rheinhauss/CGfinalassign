#include "glew.h"
#include "glut.h"
#include "Sphere.h"
#include <cmath>
#include "CVector.h"
#include "CMatrix.h"
GLfloat(*Sphere::vert)[3] = 0, (*Sphere::norm)[3] = 0;
int Sphere::nVert = 0;
void Sphere::CalculateNormal(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[])
{
	GLfloat dirv2_v1[3], dirv2_v3[3];
	for (int i = 0; i < 3; i++)
	{
		dirv2_v1[i] = v1[i] - v2[i];
		dirv2_v3[i] = v3[i] - v2[i];
	}
	//叉乘计算法线方向
	normal[0] = dirv2_v1[1] * dirv2_v3[2] - dirv2_v1[2] * dirv2_v3[1];
	normal[1] = dirv2_v1[2] * dirv2_v3[0] - dirv2_v1[0] * dirv2_v3[2];
	normal[2] = dirv2_v1[0] * dirv2_v3[1] - dirv2_v1[1] * dirv2_v3[0];
}
void Sphere::normalize(GLfloat* v)
{
	GLfloat dis = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (dis > 0)
	{
		v[0] /= dis;
		v[1] /= dis;
		v[2] /= dis;
	}
}

void Sphere::applyUV(GLfloat* norm) {
	auto d = CVector(-norm[0], -norm[1], -norm[2]);
	d.Normalize();
	float u = 0.5 + atan2f(d.y, d.x) / (2 * PI), v = 0.5 - asinf(d.z) / PI;
	glTexCoord2f(u, v);
}
void Sphere::Draw(GLfloat radius, int lon, int lat, GLuint text)	//使用经度分割lon,维度分割lat,半径radius绘制一个球。
{
	GLfloat lonCur, lonStep = 2 * PI / lon, latCur, latStep = PI / lat;
	GLfloat normal[3];
	int i, j, k = 0;
	if (!vert)
	{
		vert = new GLfloat[lon * (lat + 1)][3];
		norm = new GLfloat[lon * (lat + 1)][3];
		//计算所有点的位置
		for (lonCur = 0, i = 0; i < lon; lonCur += lonStep, i++)	//经度
		{
			for (latCur = -PI / 2, j = 0; j <= lat; latCur += latStep, j++)	//维度
			{
				vert[nVert][2] = radius * cos(latCur) * sin(lonCur);
				vert[nVert][0] = radius * cos(latCur) * cos(lonCur);
				vert[nVert][1] = radius * sin(latCur);

				norm[nVert][0] = norm[nVert][1] = norm[nVert][2] = 0;
				nVert++;
			}
		}
		for (i = 0; i < lon - 1; i++)	//经度
		{
			for (j = 0; j < lat; j++)	//维度
			{
				int index[4];//相邻四个点的索引
				index[0] = i * (lat + 1) + j;
				if (i == lon - 1)
					index[1] = j;
				else
					index[1] = index[0] + lat + 1;
				index[2] = index[1] + 1;
				index[3] = index[0] + 1;
				CalculateNormal(vert[index[0]], vert[index[1]], vert[index[2]], normal);
				for (k = 0; k < 3; k++)
				{
					norm[index[0]][k] += normal[k];
					norm[index[1]][k] += normal[k];
					norm[index[2]][k] += normal[k];
				}
				CalculateNormal(vert[index[2]], vert[index[3]], vert[index[0]], normal);
				for (k = 0; k < 3; k++)
				{
					norm[index[2]][k] += normal[k];
					norm[index[3]][k] += normal[k];
					norm[index[0]][k] += normal[k];
				}
			}
		}
		nVert = 0;
		for (lonCur = 0, i = 0; i < lon; lonCur += lonStep, i++)	//经度
		{
			for (latCur = -PI / 2, j = 0; j <= lat; latCur += latStep, j++)	//维度
			{
				normalize(norm[nVert]);
				nVert++;
			}
		}
	}
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glActiveTexture(text);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < lon; i++)	//经度
	{
		for (j = 0; j < lat; j++)	//维度
		{
			int index[4];//相邻四个点的索引
			index[0] = i * (lat + 1) + j;
			if (i == lon - 1)
				index[1] = j;
			else
				index[1] = index[0] + lat + 1;
			index[2] = index[1] + 1;
			index[3] = index[0] + 1;
			glNormal3fv(norm[index[0]]);
			applyUV(norm[index[0]]);
			glVertex3fv(vert[index[0]]);
			glNormal3fv(norm[index[1]]);
			applyUV(norm[index[1]]);
			glVertex3fv(vert[index[1]]);
			glNormal3fv(norm[index[2]]);
			applyUV(norm[index[2]]);
			glVertex3fv(vert[index[2]]);

			glNormal3fv(norm[index[2]]);
			applyUV(norm[index[2]]);
			glVertex3fv(vert[index[2]]);
			glNormal3fv(norm[index[3]]);
			applyUV(norm[index[3]]);
			glVertex3fv(vert[index[3]]);
			glNormal3fv(norm[index[0]]);
			applyUV(norm[index[0]]);
			glVertex3fv(vert[index[0]]);
		}
	}
	glEnd();
	glFrontFace(GL_CCW);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

}
