#include<iostream>
#include <GL/glut.h>
#include "SMFLoader.h"	// (1)  Include header file 
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

static int lower_arm_h = 1;

static int base_angle = 0;



void display(void)
{
	glClearColor(0, 150, 150, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(0.0f, 45.0f, 0.0f, 0.0f);

	glOrtho(-500, 500, -500, 500, -500, 500);

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

		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[0], color[1], color[2]);
	//if(normal)
	//	glNormal3f(normal[0], normal[1], normal[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);

		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[3], color[4], color[5]);
	//if (normal)
	//	glNormal3f(normal[3], normal[4], normal[5]);
		glVertex3f(vertex[3], vertex[4], vertex[5]);

		if (color)
			glColor3f(255, 255, 0);
		//glColor3f(color[6], color[7], color[8]);
	//if (normal)
	//	glNormal3f(normal[6], normal[7], normal[8]);
		glVertex3f(vertex[6], vertex[7], vertex[8]);

		glEnd();
		//glFlush();

	}



	glutSwapBuffers();
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
	glutDisplayFunc(display);

	/*
	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutTimerFunc(30, update, 0);
	*/

	glutMainLoop();


	return 0;
}

















/*


#include <GL/glut.h>
void ChangeSize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(1.0f, 2.0f, 1.0f);
	glutWireCube(1.0);
	glutSwapBuffers();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Effects Demo");
	glutReshapeFunc(ChangeSize);
	//glutKeyboardFunc(KeyPressFunc);
	glutDisplayFunc(RenderScene);

	//SetupRC();

	glutMainLoop();
	//glDeleteTextures(4,textures);
	return 0;
}

*/