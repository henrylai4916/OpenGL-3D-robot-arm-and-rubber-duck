#include<iostream>
#include <GL/glut.h>
#include "SMFLoader.h"	// (1)  Include header file 
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;


static int base_angle = 0;
static int elbow_angle = 0;
static int wrist_rotation = 0;
static int lower_arm_h = 1;
static int upper_arm_h = 2;
static int claw_base_h = 2;
static float claw_tmp = 0;
static float claw_tmp2 = 0;

void floor()
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(50, 50, 50);
	glColor3f(0.5, 0.5, 0.5);
	// 畫實體
	glutSolidCube(1.0);
	// 畫線
	//glutWireCube(1.0);
	glPopMatrix();
}

void base()
{
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	//glScalef(1.0, 0.5, 1.0);
	glScalef(1000.0, 500, 1000.0);
	glColor3f(0.2, 0.8, 0.3);
	// 畫實體
	glutSolidCube(1.0);
	// 畫線
	//glutWireCube(1.0);
	glPopMatrix();
}

void lower_arm()
{
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(0.4, 2.0, 0.4);
	glutSolidCube(1.0);
	//glutWireCube(1.0);
	glColor3f(0.5, 0.5, 1.0);
	glPopMatrix();
}

void upper_arm()
{
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(0.4, 2.0, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1.0);
	//glutWireCube(1.0);
	glPopMatrix();
}

void claw_base()
{
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glScalef(2.0, 0.5, 0.4);
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(1.0);
	//glutWireCube(1.0);
	glPopMatrix();
}

void claw_open_close_1()
{
	glPushMatrix();
	glTranslatef(0.7, 0.2, 0.0);
	glScalef(0.5, 0.5, 0.4);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(1.0);
	//glutWireCube(1.0);
	glPopMatrix();
}

void claw_open_close_2()
{
	glPushMatrix();
	glTranslatef(-0.7, 0.2, 0.0);
	glScalef(0.5, 0.5, 0.4);
	//glutWireCube(1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void display(void)
{
	glClearColor(0, 150, 150, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(0.0f, 45.0f, 0.0f, 0.0f);

	//glOrtho(-500, 500, -500, 500, -500, 500);
	glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);

	glBegin(GL_QUADS);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0, -300, 100);
	glVertex3f(200, 300, -100);
	glVertex3f(0, 300, 200);
	glVertex3f(0, 200, 200);

	glEnd();

	SMFLoader loader;   //(2) declare SMFLoader

	char file_name[] = "rubber_duck.smf";
	char* tmp = file_name;
	loader.load(tmp);	// (3) Load model file contant

	//****** (助教提供 loader使用方法) 在OnDraw時使用以下方法畫出model ******\		(4) Draw model
	//幫助各位同學畫出model模型
	//請參考以下程式碼
	//請自行加入 normal畫法

	float* vertex = NULL;
	float* color = NULL;
	float* normal = NULL;

	for (int i = 0; i < loader.getFaceSize(); i++)	//每一迴圈畫一個三角面
	{
		// 得到一個面上的3個點  總共9個數值
		// { x1,y1,z1,x2,y2,z2,x3,y3,z3 }
		vertex = loader.getFace(i);


		// 得到一個面上的每個點的顏色 總共9個數值
		// { r1,g1,b1,r2,g2,b2,r3,g3,b3 }
		color = loader.getFaceColor(i);

		normal = loader.getFaceNormal(i);

		glBegin(GL_TRIANGLES);

		glNormal3f(normal[0], normal[1], normal[2]);
		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[0], color[1], color[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);



		glNormal3f(normal[3], normal[4], normal[5]);
		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[3], color[4], color[5]);
		glVertex3f(vertex[3], vertex[4], vertex[5]);


		glNormal3f(normal[6], normal[7], normal[8]);
		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[6], color[7], color[8]);
		glVertex3f(vertex[6], vertex[7], vertex[8]);

		glEnd();
		//glFlush();

	}


	glPushMatrix();


	/*

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	*/

	/*
		void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
		angle：为旋转的角度，单位为度。
		x, y, z：为对应xyz轴的布尔值变量
		x,y,z表达的意思并不是坐标点，而是要围绕哪个坐标轴旋转。
		即其实这里的x,y,z值相当于一个布尔值，0.0表示假，而非零参数则表示真。
		所以如果你想让当前的几何图形围绕着z轴旋转，那么x和y都设为0，而z设为非零值即可。
		https://www.cnblogs.com/1024Planet/p/5647224.html
	*/

	//glRotatef(base_angle, 0.0, 1.0, 0.0);

	floor();
	base();

	glTranslatef(0.0, lower_arm_h, 0.0);
	glRotatef(base_angle, 0.0, 1.0, 0.0);
	lower_arm();

	glTranslatef(0.0, upper_arm_h, 0.0);
	glRotatef(elbow_angle, 0.0, 0.0, 1.0);
	glRotatef(wrist_rotation, 0.0, 1.0, 0.0);
	upper_arm();

	glTranslatef(0.0, claw_base_h, 0.0);
	claw_base();

	glTranslatef(-0.05 + claw_tmp, 0.5, 0.0);
	claw_open_close_1();


	glTranslatef(0.05 + claw_tmp2, 0.0, 0.0);
	claw_open_close_2();

	glPopMatrix();
	glutSwapBuffers();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, -3.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
			base_angle = (base_angle + 5) % 360;
			glutPostRedisplay();
			break;

		case 'Q':
			base_angle = (base_angle - 5) % 360;
			glutPostRedisplay();
			break;

		case 'w':
			elbow_angle = (elbow_angle + 5) % 360;
			glutPostRedisplay();
			break;

		case 'W':
			elbow_angle = (elbow_angle - 5) % 360;
			glutPostRedisplay();
			break;

		case 'e':
			wrist_rotation = (wrist_rotation + 5) % 360;
			glutPostRedisplay();
			break;

		case 'E':
			wrist_rotation = (wrist_rotation - 5) % 360;
			glutPostRedisplay();
			break;

		case 'R':
			claw_tmp -= 0.5;
			claw_tmp2 += 0.8;
			glutPostRedisplay();
			break;

		case 'r':
			claw_tmp += 0.5;
			claw_tmp2 -= 0.8;
			glutPostRedisplay();
			break;

		default:
			break;
	}
}

int main(int argc, char* argv[])
{
	//初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	// 設定WindowSize  column與row在Game.h可以調整
	glutInitWindowSize(1000, 1000);
	//設定視窗顯示名稱
	glutCreateWindow("HW3");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}