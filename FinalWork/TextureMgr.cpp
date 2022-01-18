#include "TextureMgr.h"
#include <atlimage.h>
#include <cstring>
#include <iomanip>
#include <locale>
#include "glew.h"
#include "glut.h"
GLuint TextureMgr::textures[10]{};
void TextureMgr::init() {
	char name[4][10]{
		"Sun.bmp",
		"Earth.bmp",
		"Mete.bmp",
		"logo.bmp"
	};
	for (int i = 0; i < 4; i++) {
		CImage img;
		HRESULT hResult = img.Load(name[i]);
		if (FAILED(hResult))
		{
			return;
		}
		
		//glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		int pitch = img.GetPitch();
		if (pitch < 0)
			gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetPixelAddress(0, img.GetHeight() - 1));
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetBits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);	
		//float zPlane1[4] = { 0.2,0,0,0 };
		//float zPlane2[4] = { 0,0,0.2,0 };
		//glTexGenfv(GL_S, GL_OBJECT_PLANE, zPlane1);
		//glTexGenfv(GL_T, GL_OBJECT_PLANE, zPlane2);

		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//
	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
	float col[4] = { 1,1,1 };
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, col);	//颜色直接相乘
}