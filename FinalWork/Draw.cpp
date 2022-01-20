#include "Draw.h"
GLuint Earth_texture[1] = { 0 };//定义纹理
GLfloat(*vert)[3] = 0, (*norm)[3] = 0;
int nVert = 0;
void CalculateNormal(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[])
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
void normalize(GLfloat* v)
{
	GLfloat dis = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (dis > 0)
	{
		v[0] /= dis;
		v[1] /= dis;
		v[2] /= dis;
	}
}
void Draw::drawEarth(GLfloat radius, int lon, int lat) {
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
	Draw::LoadEarth_GLTextures();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Earth_texture[0]);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
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
			glVertex3fv(vert[index[0]]);
			glNormal3fv(norm[index[1]]);
			glVertex3fv(vert[index[1]]);
			glNormal3fv(norm[index[2]]);
			glVertex3fv(vert[index[2]]);

			glNormal3fv(norm[index[2]]);
			glVertex3fv(vert[index[2]]);
			glNormal3fv(norm[index[3]]);
			glVertex3fv(vert[index[3]]);
			glNormal3fv(norm[index[0]]);
			glVertex3fv(vert[index[0]]);
		}
	}
	glEnd();
	glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

}
// Load And Convert To Textures
int Draw::LoadEarth_GLTextures() {
	CImage img;
	HRESULT hResult = img.Load("Earth.bmp");
	if (FAILED(hResult))
	{
		return 0;
	}
	glGenTextures(1, &Earth_texture[0]);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, Earth_texture[0]);
	// Generate The Texture
	int pitch = img.GetPitch();
	if (pitch < 0)
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetPixelAddress(0, img.GetHeight() - 1));
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetBits());
	//filter 参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd
																					//glDisable(GL_CULL_FACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//颜色直接相乘
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//
																	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
	float col[4] = { 1,1,1 };
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, col);	//颜色直接相乘
	return TRUE;
}