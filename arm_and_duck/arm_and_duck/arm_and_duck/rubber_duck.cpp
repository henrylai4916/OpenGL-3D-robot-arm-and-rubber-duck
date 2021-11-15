
#include<iostream>
#include <GL/glut.h>
#include "SMFLoader.h"	// (1)  Include header file
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/freeglut.h"


using namespace std;

SMFLoader loader;

bool mouseDown = false;

int xrot = 10;
int yrot = 10;

int xdiff = 0;
int ydiff = 0;

//GLfloat light_position[] = { 100.0 , 100.0 , 0.0, 0.0 };

void draw_duck()
{
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
			//glColor3f(255, 255, 0);
			glColor3f(color[0], color[1], color[2]);
		glVertex3f(vertex[0], vertex[1], vertex[2]);


		glNormal3f(normal[3], normal[4], normal[5]);
		if (color)
			//glColor3f(255, 255, 0);
			glColor3f(color[3], color[4], color[5]);
		glVertex3f(vertex[3], vertex[4], vertex[5]);


		glNormal3f(normal[6], normal[7], normal[8]);
		if (color)
			//glColor3f(255, 255, 0);
			glColor3f(color[6], color[7], color[8]);
		glVertex3f(vertex[6], vertex[7], vertex[8]);

		glEnd();
	}
}

void draw_floor()
{
	glBegin(GL_QUADS);
	glColor3f(255, 0, 255);

	glVertex3f(-200, -80, -200);
	glVertex3f(200, -80, -200);
	glVertex3f(200, -80, 200);
	glVertex3f(-200, -80, 200);

	glEnd();
}

void light_set()
{
	GLfloat light_position[] = { 5.0 , 5.0 , 5.0, 0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// 啟動材質
	glEnable(GL_COLOR_MATERIAL);
}

void display(void)
{



	glClearColor(0, 150, 150, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_viewMatrix);

	glLoadIdentity();

	light_set();

	gluLookAt(250.0, 250.0, 250.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(magnitude, angle, 0.0, 250.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);



	draw_floor();
	draw_duck();


	glutSwapBuffers();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	char file_name[] = "rubber_duck.smf";
	char* tmp = file_name;
	loader.load(tmp);
}

void My_Reshape(int  width, int  height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 10.0f, 2000.0f);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(250.0, 250.0, 250.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void My_Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
		//std::cout << "xdiff:" << xdiff << "\tydiff" << ydiff << std::endl;
	}
	else
		mouseDown = false;
}

void Mouse_Moving(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;
		std::cout << "yrot:" << yrot << "\txrot" << xrot << std::endl;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	init();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1200);
	glutCreateWindow("HW3");
	glutReshapeFunc(My_Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(My_Mouse);
	glutMotionFunc(Mouse_Moving);
	glutMainLoop();
	return 0;
}