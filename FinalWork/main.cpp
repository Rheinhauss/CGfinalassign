#include "engine.h"
#include <time.h>
#include <string>
#include "Draw.h"
/*
	FPS:60
*/
Camera *camera;
time_t begin_t, finish_t;
void myDisplay();
void myTimerFunc(int val);
void myReshape(int w,int h);
void SpecialKey(GLint key, GLint x, GLint y);
void SpecialKeyUp(GLint key, GLint x, GLint y);
void myKeyboardUpFunc(unsigned char key, int x, int y);
void myKeyboardFunc(unsigned char key, int x, int y);
void SetRC();
void Update();
void SetView();
void Init();//游戏的所有初始化操作
void SetLight();
void myMouseFunc(int button, int state, int x, int y);


int main(int argc, char *argv[])
{


	glutInit(&argc, argv);//初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//指定窗口显示模式的类型
	glutInitWindowPosition(150, 50);//设置初始窗口的位置
	glutInitWindowSize(1024, 768);//设置窗口初始大小
	glutCreateWindow("FinalWork");//设置窗口标题
	Init();
	glutDisplayFunc(&myDisplay);//glutDisplayFunc(&display)在程序运行时是自动调用的，即程序会自动调用display函数重绘窗口
	glutTimerFunc(17, myTimerFunc, 0);
	glutReshapeFunc(&myReshape);
	glutSpecialFunc(&SpecialKey);//上下左右方向键
	glutSpecialUpFunc(&SpecialKeyUp);
	glutKeyboardUpFunc(&myKeyboardUpFunc);//键盘按键检测
	glutKeyboardFunc(&myKeyboardFunc);//响应键盘控制
	glutMouseFunc(&myMouseFunc);
	SetRC();//清屏
	begin_t = clock();
	glutMainLoop();//循环
    return 0;
}

void Init() {
	SceneMgr::InitTexture();
	//生成摄像机
	camera = new Camera();
	////生成天空盒
	//SceneMgr::skybox = new SkyBox((char *) "../run/skybox\\siege_ft.bmp", (char *) "../run/skybox\\siege_bk.bmp",
	//	(char *) "../run/skybox\\siege_up.bmp", (char *) "../run/skybox\\siege_dn.bmp",
	//	(char *) "../run/skybox\\siege_rt.bmp", (char *) "../run/skybox\\siege_lf.bmp");
	//SceneMgr::skybox->setSkyBox(-10, 10);
	
	//生成太阳
	SceneMgr::sun = new Sun();
	//生成地球
	SceneMgr::earth = new Earth();
	//生成陨石带和陨石
	MeteMgr::Init();
	//生成敌机
	EnemyMgr::Init();
	//生成玩家飞机
	PlayerMgr::Player = new Aircraft();
	PlayerMgr::timeUsed = new Timer();
	PlayerMgr::timeUsed->start();
}


void SetView() {
	//为过渡态,直接采用摄像机的Transform,绝对变换
	if (camera->isTrans == true) {
		CEuler rot = camera->transform->rotation.ToCEuler();
		CVector pos = camera->transform->position;
		glRotatef(-rot.b, 0, 0, 1);
		glRotatef(-rot.p, 1, 0, 0);
		glRotatef(-rot.h, 0, 1, 0);
		glTranslatef(-pos.x, -pos.y, -pos.z);
	}
	//非过渡态
	else {
		//上帝视角模式,不绑定,绝对变换
		CEuler rot = camera->transform->rotation.ToCEuler();
		CVector pos = camera->transform->position;
		glRotatef(-rot.b, 0, 0, 1);
		glRotatef(-rot.p, 1, 0, 0);
		glRotatef(-rot.h, 0, 1, 0);
		glTranslatef(-pos.x, -pos.y, -pos.z);
		//驾驶模式,绑定,相对变换
		if (PlayerMgr::Player->pattern == true) {
			CEuler rot = PlayerMgr::Player->transform->rotation.ToCEuler();
			CVector pos = PlayerMgr::Player->transform->position;
			glRotatef(-rot.b, 0, 0, 1);
			glRotatef(-rot.p, 1, 0, 0);
			glRotatef(-rot.h, 0, 1, 0);
			glTranslatef(-pos.x, -pos.y, -pos.z);
		}
	}
	SceneMgr::updateViewMatrixInThis();
	SceneMgr::updateProjMatrixInThis();
}
void drawCoordinates(void)
{
	glLineWidth(3.0f);
	glColor3f(1.0f, 0.0f, 0.0f); //画红色的x轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();
	glColor3f(0.0, 1.0, 0.0); //画绿色的y轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();
	glColor3f(0.0, 0.0, 1.0); //画蓝色的z轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	//设置摄像机
	SetView();

	//glPushMatrix();
	////天空盒
	//glTranslatef(0, 0, -100);
	////SceneMgr::skybox->CreateSkyBox();
	//glPopMatrix();
	drawCoordinates();


	//设置光源属性
	SetLight();
	//设置材质属性
	GLfloat amb[4] = { 0.4f,0.4f,0.4f,1 };
	GLfloat dif[4] = { 1,1,1,1 };
	GLfloat spe[4] = { 0.1f,0.1f,0.1f,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	//绘制物体	
	//glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, TextureMgr::textures[3]);

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glFrontFace(GL_CW);
 //   glutSolidCube(90);
	//glFrontFace(GL_CCW);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable(GL_TEXTURE_GEN_T);

	//glDisable(GL_TEXTURE_2D);
	//glPushMatrix();
	//glScalef(1.1, 1.1, 1.1);
	//glTranslatef(10, 10, 10);
	//glRotatef(10, 1, 1, 1);
	//Draw::drawEarth(1, 10, 10);
	//glPopMatrix();
	int len = (int)Object::objs.size();
	for (int i = 0; i < len; ++i) {
		//转为物体的变换
		glPushMatrix();
		CVector pos = Object::objs[i]->transform->position;
		CVector scale = Object::objs[i]->transform->scale;
		CMatrix rot = Object::objs[i]->transform->rotation.ToCMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(scale.x, scale.y, scale.z);
		glMultMatrixf(rot);
		Object::objs[i]->Render();
		glPopMatrix();
	}
	glPopMatrix();

	//begin 屏幕空间文字显示
	string s = "enemy hit: " + to_string(PlayerMgr::hitEnemyNum)
		+ "    meteor crash: " + to_string(PlayerMgr::colMeteNum)
		+ "    time now: " + to_string(PlayerMgr::timeUsed->time);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos3f(-1,0.9,0);
	glColor3f(1., 1., 1.);
	for (int i = 0; i < s.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	//end
	glutSwapBuffers();
}
void myTimerFunc(int val) {
	//绘制
	// to do 
	myDisplay();
	finish_t = clock();
	double time = ((double)(finish_t - begin_t))/ CLOCKS_PER_SEC;
	if (time < 1 / 40)
		time = 1 / 40;
	TimeMgr::deltaTime = time;
	TimeMgr::currentTime += time;
	begin_t = clock();
	//计算
	Update();
	glutTimerFunc(25, myTimerFunc, 0);
}
void Update() {
	//计时
	TimeMgr::TIMER();
	//生成敌机
	EnemyMgr::CreateEnemy();
	//碰撞检测
	CollMgr::CollisionDetec();
	//运行Update
	int len = (int)Object::objs.size();
	for (int i = 0; i < len; ++i) {
		Object::objs[i]->Update();
	}
	DestroyMgr::DestroyObj();
}
void myReshape(int w, int h) {
	SceneMgr::w = w;
	SceneMgr::h = h;
	GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLfloat(w) / h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SpecialKeyUp(GLint key, GLint x, GLint y) {
	if (key == GLUT_KEY_UP) {
		InputManager::KEY_UP = false;
	}
	else if (key == GLUT_KEY_DOWN) {
		InputManager::KEY_DOWN = false;
	}
	else if (key == GLUT_KEY_LEFT) {
		InputManager::KEY_LEFT = false;
	}
	else if (key == GLUT_KEY_RIGHT) {
		InputManager::KEY_RIGHT = false;
	}
	else if (key == GLUT_KEY_F1) {
		InputManager::KEY_F1 = false;
	}
	else if (key == GLUT_KEY_F2) {
		InputManager::KEY_F2 = false;
	}
	else if (key == GLUT_KEY_F3) {
		InputManager::KEY_F3 = false;
	}
	else if (key == GLUT_KEY_F4) {
		InputManager::KEY_F4 = false;
	}
	else if (key == GLUT_KEY_F5) {
		InputManager::KEY_F5 = false;
	}
	else if (key == GLUT_KEY_F6) {
		InputManager::KEY_F6 = false;
	}
	else if (key == GLUT_KEY_F7) {
		InputManager::KEY_F7 = false;
	}
	else if (key == GLUT_KEY_F8) {
		InputManager::KEY_F8 = false;
	}
	else if (key == GLUT_KEY_F9) {
		InputManager::KEY_F9 = false;
	}
}
void SpecialKey(GLint key, GLint x, GLint y) {
	if (key == GLUT_KEY_UP) {
		InputManager::KEY_UP = true;
	}
	else if (key == GLUT_KEY_DOWN) {
		InputManager::KEY_DOWN = true;
	}
	else if (key == GLUT_KEY_LEFT) {
		InputManager::KEY_LEFT = true;
	}
	else if (key == GLUT_KEY_RIGHT) {
		InputManager::KEY_RIGHT = true;
	}
	else if (key == GLUT_KEY_F1) {
		InputManager::KEY_F1 = true;
	}
	else if (key == GLUT_KEY_F2) {
		InputManager::KEY_F2 = true;
	}
	else if (key == GLUT_KEY_F3) {
		InputManager::KEY_F3 = true;
	}
	else if (key == GLUT_KEY_F4) {
		InputManager::KEY_F4 = true;
	}
	else if (key == GLUT_KEY_F5) {
		InputManager::KEY_F5 = true;
	}
	else if (key == GLUT_KEY_F6) {
		InputManager::KEY_F6 = true;
	}
	else if (key == GLUT_KEY_F7) {
		InputManager::KEY_F7 = true;
	}
	else if (key == GLUT_KEY_F8) {
		InputManager::KEY_F8 = true;
	}
	else if (key == GLUT_KEY_F9) {
		InputManager::KEY_F9 = true;
	}
}
void myKeyboardUpFunc(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q': {
		InputManager::KEY_Q = false;
		break;
	}
	case 'w': {
		InputManager::KEY_W = false;
		break;
	}
	case 'e': {
		InputManager::KEY_E = false;
		break;
	}
	case 'r': {
		InputManager::KEY_R = false;
		break;
	}
	case 't': {
		InputManager::KEY_T = false;
		break;
	}
	case 'y': {
		InputManager::KEY_Y = false;
		break;
	}
	case 'u': {
		InputManager::KEY_U = false;
		break;
	}
	case 'i': {
		InputManager::KEY_I = false;
		break;
	}
	case 'o': {
		InputManager::KEY_O = false;
		break;
	}
	case 'p': {
		InputManager::KEY_P = false;
		break;
	}
	case 'a': {
		InputManager::KEY_A = false;
		break;
	}
	case 's': {
		InputManager::KEY_S = false;
		break;
	}
	case 'd': {
		InputManager::KEY_D = false;
		break;
	}
	case 'f': {
		InputManager::KEY_F = false;
		break;
	}
	case 'g': {
		InputManager::KEY_G = false;
		break;
	}
	case 'h': {
		InputManager::KEY_H = false;
		break;
	}
	case 'j': {
		InputManager::KEY_J = false;
		break;
	}
	case 'k': {
		InputManager::KEY_K = false;
		break;
	}
	case 'l': {
		InputManager::KEY_L = false;
		break;
	}
	case 'z': {
		InputManager::KEY_Z = false;
		break;
	}
	case 'x': {
		InputManager::KEY_X = false;
		break;
	}
	case 'c': {
		InputManager::KEY_C = false;
		break;
	}
	case 'v': {
		InputManager::KEY_V = false;
		break;
	}
	case 'b': {
		InputManager::KEY_B = false;
		break;
	}
	case 'n': {
		InputManager::KEY_N = false;
		break;
	}
	case 'm': {
		InputManager::KEY_M = false;
		break;
	}
	case '1': {
		InputManager::KEY_1 = false;
		break;
	}
	case '2': {
		InputManager::KEY_2 = false;
		break;
	}
	case '3': {
		InputManager::KEY_3 = false;
		break;
	}
	case '4': {
		InputManager::KEY_4 = false;
		break;
	}
	case '5': {
		InputManager::KEY_5 = false;
		break;
	}
	case '6': {
		InputManager::KEY_6 = false;
		break;
	}
	case '7': {
		InputManager::KEY_7 = false;
		break;
	}
	case '8': {
		InputManager::KEY_8 = false;
		break;
	}
	case '9': {
		InputManager::KEY_9 = false;
		break;
	}
	case '0': {
		InputManager::KEY_0 = false;
		break;
	}
	case ' ': {
		InputManager::KEY_SPACE = false;
		break;
	}
	}
}

void myKeyboardFunc(unsigned char key, int x, int y) {
	switch (key)
	{
	case '[': {
		camera->moveSpeed *= 0.9f;
		break;
	}
	case ']': {
		camera->moveSpeed /= 0.9f;
		break;
	}
	case '{': {
		camera->rotSpeed *= 0.9f;
		break;
	}
	case '}': {
		camera->rotSpeed /= 0.9f;
		break;
	}
	case 'q': {
		InputManager::KEY_Q = true;
		break;
	}
	case 'w': {
		InputManager::KEY_W = true;
		break;
	}
	case 'e': {
		InputManager::KEY_E = true;
		break;
	}
	case 'r': {
		InputManager::KEY_R = true;
		break;
	}
	case 't': {
		InputManager::KEY_T = true;
		break;
	}
	case 'y': {
		InputManager::KEY_Y = true;
		break;
	}
	case 'u': {
		InputManager::KEY_U = true;
		break;
	}
	case 'i': {
		InputManager::KEY_I = true;
		break;
	}
	case 'o': {
		InputManager::KEY_O = true;
		break;
	}
	case 'p': {
		InputManager::KEY_P = true;
		break;
	}
	case 'a': {
		InputManager::KEY_A = true;
		break;
	}
	case 's': {
		InputManager::KEY_S = true;
		break;
	}
	case 'd': {
		InputManager::KEY_D = true;
		break;
	}
	case 'f': {
		InputManager::KEY_F = true;
		break;
	}
	case 'g': {
		InputManager::KEY_G = true;
		break;
	}
	case 'h': {
		InputManager::KEY_H = true;
		break;
	}
	case 'j': {
		InputManager::KEY_J = true;
		break;
	}
	case 'k': {
		InputManager::KEY_K = true;
		break;
	}
	case 'l': {
		InputManager::KEY_L = true;
		break;
	}
	case 'z': {
		InputManager::KEY_Z = true;
		break;
	}
	case 'x': {
		InputManager::KEY_X = true;
		break;
	}
	case 'c': {
		InputManager::KEY_C = true;
		break;
	}
	case 'v': {
		InputManager::KEY_V = true;
		break;
	}
	case 'b': {
		InputManager::KEY_B = true;
		break;
	}
	case 'n': {
		InputManager::KEY_N = true;
		break;
	}
	case 'm': {
		InputManager::KEY_M = true;
		break;
	}
	case '1': {
		InputManager::KEY_1 = true;
		break;
	}
	case '2': {
		InputManager::KEY_2 = true;
		break;
	}
	case '3': {
		InputManager::KEY_3 = true;
		break;
	}
	case '4': {
		InputManager::KEY_4 = true;
		break;
	}
	case '5': {
		InputManager::KEY_5 = true;
		break;
	}
	case '6': {
		InputManager::KEY_6 = true;
		break;
	}
	case '7': {
		InputManager::KEY_7 = true;
		break;
	}
	case '8': {
		InputManager::KEY_8 = true;
		break;
	}
	case '9': {
		InputManager::KEY_9 = true;
		break;
	}
	case '0': {
		InputManager::KEY_0 = true;
		break;
	}
	case ' ': {
		InputManager::KEY_SPACE = true;
		//cout << "KEY_SPACE" << endl;
		break;
	}

	//esc退出
	case 27: {
		exit(0);
	}

	}
}
void SetRC() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_LINE_SMOOTH);//过虑线段的锯齿

	glEnable(GL_DEPTH_TEST);
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 

	//	glDisable(GL_DEPTH_TEST);
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}


//光源
void SetLight() {
	GLfloat amb[4] = { 1,1,1,1 };
	GLfloat dif[4] = { 1,1,1,1 };
	GLfloat spe[4] = { 0.2f,0.2f,0.2f,1 };
	GLfloat pos[4] = { 0,0,0,1 };
	GLfloat static seta = 0;
	seta += 1;
	glPushMatrix();
	glTranslatef(100, 0, -200.0f);
	glRotatef(seta, 1, 1, 1);
	glTranslatef(pos[0], pos[1], pos[2]);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.1f, 10, 10);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spe);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void myMouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	cout << "x: " << x << "\ty: " << y << endl;
	float ix = double(x) / double(SceneMgr::w);
	float iy = double(y) / double(SceneMgr::h);
		for (auto enemy : EnemyMgr::Enemys) {
			if (enemy->ScreenMaxXY.x >= ix &&
				enemy->ScreenMinXY.x <= ix &&
				enemy->ScreenMaxXY.y >= iy &&
				enemy->ScreenMinXY.y <= iy) {
				cout << "enemy!" << endl;
			}
		}
	}
}