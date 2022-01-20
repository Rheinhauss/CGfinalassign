#include "Meteorite.h"
#include "SceneMgr.h"
#include "MeteMgr.h"
#include "TimeMgr.h"
#include "DestroyMgr.h"
#include "TextureMgr.h"
#include "Sphere.h"

Meteorite::Meteorite(MeteRange*_mr):mr(_mr)
{
	this->name = "meteorite";
	this->tag = "meteorite";
	this->timer = new Timer();
	timer->start();
	//始终在y=0平面内
	this->direction = CVector((float)SceneMgr::random(true), 0, (float)SceneMgr::random(true));
	this->moveSpeed = 0.03;
	MeteMgr::Metes.push_back(this);
	float _r = mr->minRange + SceneMgr::random(false) * (mr->maxRange - mr->minRange),
		_s = SceneMgr::random(false) * 360.0;
	this->transform->position = CVector(_r * cos(_s / 180.0 * PI), 0, _r * sin(_s / 180.0 * PI));
	/*
	根据绘制的模型,设置碰撞盒范围
	this->maxXYZ
	this->minXYZ
	*/
	//const float t = 0.5;
	const float t = 0.5;
	this->maxXYZ = CVector(t, t, t);
	this->minXYZ = CVector(-t, -t, -t);
}

Meteorite::~Meteorite()
{
	for (vector<Meteorite*>::iterator it = MeteMgr::Metes.begin(); it != MeteMgr::Metes.end(); )
	{
		if (*it == this)
		{
			it = MeteMgr::Metes.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	delete this->timer;
}

//绘制陨石
void Meteorite::DrawMeteorite() {
	glPushMatrix();
	////glEnable(GL_TEXTURE_2D);
	////glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[2]);
	////glEnable(GL_TEXTURE_GEN_S);
	////glEnable(GL_TEXTURE_GEN_T);
	////glutSolidSphere(1, 5, 5);
	//Sphere::Draw(1, 10, 10, TextureMgr::textures[2]);
	////glDisable(GL_TEXTURE_GEN_S);
	////glDisable(GL_TEXTURE_GEN_T);
	////glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHT0);
	//GLfloat sun_mat_ambient[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //定义材质的环境光颜色，为0
	//GLfloat sun_mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5f };  //定义材质的漫反射光颜色，为0
	//GLfloat sun_mat_specular[] = { 0.5f, 0.5f, 0.5f, 0.5f };   //定义材质的镜面反射光颜色，为0
	//GLfloat sun_mat_emission[] = { 0.5f, 0.5f, 0.5f, 0.5f };   //定义材质的辐射广颜色，为偏红色
	//GLfloat sun_mat_shininess = 0.0f;
	//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	gluQuadricTexture(TextureMgr::e_tex, GLU_TRUE);
	//glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[2]);
	gluSphere(TextureMgr::e_tex, 1, 30, 30);
	//cout << gluErrorString(glGetError()) << endl;
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(TextureMgr::e_tex, GLU_FALSE);
	//glutSolidSphere(this->radius, 100, 100);'
	//Sphere::Draw(this->radius, 100, 100, TextureMgr::textures[0]);
	glPopMatrix();
}

//移动, 每隔interval更改一次随机移动方向, 如果到达边界, 则移动方向变为相反方向并从0开始计时
void Meteorite::Move() {
	if (this->timer->time >= interval) {
		this->direction = CVector((float)SceneMgr::random(true), 0, (float)SceneMgr::random(true));
		timer->start();
	}

	//this->Transform->position更改位置 速度*forward*deltaTime
	this->transform->position = this->transform->position + moveSpeed * direction * TimeMgr::deltaTime;

	//判断是否到达边界 圆环带 MeteRange* mr
	//如果到达边界, 则删除
	double _x = this->transform->position.x - Sun::pos.x,
		   _z = this->transform->position.z - Sun::pos.z,
		   _r = sqrt(_x * _x + _z * _z);
	if (mr->minRange >= _r || mr->maxRange <= _r) {
		DestroyMgr::add(this);
		MeteMgr::add();
	}

	//是否超出边界,是则消失,在边界处重新生成
}

//override
void Meteorite::Render() {
	this->DrawMeteorite();
}
void Meteorite::Update() {
	this->Move();
}
void Meteorite::Collision(Collider *col) {
	if (col->tag == "Aircraft") {
		//消失,出现在活动范围边界处
	}
	else if (col->tag == "meteorite") {
		//向相反方向运动,从0开始计时
	}
}