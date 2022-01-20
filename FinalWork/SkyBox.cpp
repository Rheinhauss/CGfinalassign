#include "SkyBox.h"

SkyBox::SkyBox() {

}

SkyBox::SkyBox(char *front, char *back, char *top, char *bottom, char *left, char *right) {
	m_vertical = -50;
	m_size = 100000;
	m_front = front;
	m_top = top;
	m_bottom = bottom;
	m_back = back;
	m_left = left;
	m_right = right;
	//SetCurrentDirectory(dir);
	LoadBitMapTexture(m_front, m_texture[SKY_FRONT]);
	LoadBitMapTexture(m_bottom, m_texture[SKY_BOTTOM]);
	LoadBitMapTexture(m_top, m_texture[SKY_TOP]);
	LoadBitMapTexture(m_back, m_texture[SKY_BACK]);
	LoadBitMapTexture(m_right, m_texture[SKY_RIGHT]);
	LoadBitMapTexture(m_left, m_texture[SKY_LEFT]);
}

SkyBox::~SkyBox() {
	delete m_front;
	delete m_back;
	delete m_top;
	delete m_bottom;
	delete m_left;
	delete m_right;
	for (int i = 0; i < 6; ++i) {
		glDeleteTextures(6, &m_texture[i]);
	}
}

void SkyBox::CreateSkyBox() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glFrontFace(GL_CW);
	//�ײ�
	{
		texture(m_texture[SKY_BOTTOM]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(m_size, -m_size, m_size);
		glEnd();

		//ǰ��
		texture(m_texture[SKY_FRONT]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glEnd();

		//����
		texture(m_texture[SKY_BACK]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glEnd();

		//����
		texture(m_texture[SKY_RIGHT]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(m_size, -m_size, m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(m_size, -m_size, -m_size);
		glEnd();

		//����
		texture(m_texture[SKY_LEFT]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, -m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_size, m_size, m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, -m_size, m_size);
		glEnd();

		//����
		texture(m_texture[SKY_TOP]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-m_size, m_size, -m_size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(m_size, m_size, -m_size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(m_size, m_size, m_size);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_size, m_size, m_size);
		glEnd();
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);
	glPopMatrix();
}

bool SkyBox::LoadBitMapTexture(char *filename, GLuint &texture) {
	//AUX_RGBImageRec *pImage = NULL;
	//pImage = auxDIBImageLoad(filename);     // װ��λͼ
	//if (pImage == NULL)
	//	return false;     // λͼûװ�뷵�ش���
	//glGenTextures(1, &texture);             // ������ͼ(����)
	//glBindTexture(GL_TEXTURE_2D, texture);// ����ͼ
	//									  //gluBuild2DMipmaps֧������ֱ���λͼ�ļ�
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4,   //
	//	pImage->sizeX,     // ͼ�ο�
	//	pImage->sizeY,     // ͼ�θ�
	//	GL_RGB, GL_UNSIGNED_BYTE,
	//	pImage->data       // ͼ������
	//	);
	//free(pImage->data);                  // �ͷ�λͼ����ռ�ݵ��ڴ���Դ
	//free(pImage);
	//return true;                         // ���سɹ�

	CImage img;
	HRESULT hResult = img.Load(filename);
	if (FAILED(hResult))
	{
		cout << filename << endl;
		return 0;
	}
	glGenTextures(1, &texture);					// Create The Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	// Generate The Texture
	int pitch = img.GetPitch();
	if (pitch < 0)
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetPixelAddress(0, img.GetHeight() - 1));
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, img.GetBPP() / 8, img.GetWidth(), img.GetHeight(), GL_BGR, GL_UNSIGNED_BYTE, img.GetBits());
	//filter ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filteringd
																				
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);	//��ɫֱ�����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//
																	//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_BLEND);
	float col[4] = { 1,1,1 };
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, col);	//��ɫֱ�����
	return TRUE;
}

void SkyBox::texture(GLuint &tex) {
	glBindTexture(GL_TEXTURE_2D, tex);// ����ͼ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�Ŵ���������˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);//ѡ�����ڽ���mip�㣬ʹ�����Թ���

}

void SkyBox::setSkyBox(float vertical, float size) {
	m_vertical = vertical;
	m_size = size;
}
