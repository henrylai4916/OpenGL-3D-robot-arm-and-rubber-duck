
#include<iostream>
//#include "glut.h"
#include "SMFLoader.h"	// (1)  Include header file
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/freeglut.h"
#include <ctime> 

using namespace std;

SMFLoader loader;

bool mouseDown = false;
int x_r = 10;
int y_r = 10;
int x_c = 0;
int y_c = 0;
int click_r = 0;
int light_choose = 0;
int base_angle = 0;
int elbow_angle = 0;
int wrist_rotation = 0;
int lower_arm_h = 100;
int upper_arm_h = 200;
int claw_base_h = 200;
float claw_tmp = 0;
float claw_tmp2 = 0;
int base_move_x = 0;
int base_move_y = 0;
int claw_open_close = 1;
float spot_light_move = 0;
float spot_light_move2 = 0;
GLfloat sun_light_position[] = { -50.0f, -50.0f, -50.0f, 1.0f };
GLfloat spotlight_position[4] = { 0.0, 600.0, 0.0, 1.0 };
GLfloat spotlight_direction[3] = { 0.0, -1.0, 0.0 };

void base()
{
	glPushMatrix();
	glTranslatef(0.0, 50, 0.0);
	glScalef(200.0, 280.0, 200.0);
	glColor3f(0.2, 0.8, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void lower_arm()
{
	glPushMatrix();
	glTranslatef(0.0, 100.0, 0.0);
	glScalef(40.0, 200.0, 40.0);
	glutSolidCube(1.0);
	glColor3f(0.5, 0.5, 1.0);
	glPopMatrix();
}

void upper_arm()
{
	glPushMatrix();
	glTranslatef(0.0, (1.0  )*100.0, 0.0);
	glScalef(0.4*100.0, 2.0 * 100.0, 0.4 * 100.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void claw_base()
{
	glPushMatrix();
	glTranslatef(0.0, (0.2) * 100.0, 0.0);
	glScalef(2.0 * 100.0, 0.5 * 100.0, 0.4 * 100.0);
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void claw_open_close_1()
{
	glPushMatrix();
	glTranslatef(70.0, 20.0, 0.0);
	glScalef(50.0, 50.0, 40.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void claw_open_close_2()
{
	glPushMatrix();
	glTranslatef(-0.7*100, 0.2*100.0, 0.0);
	glScalef(0.5 * 100, 0.5 * 100, 0.4 * 100);
	glutSolidCube(1.0);
	glPopMatrix();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'G':
			base_move_x += 5;
			glutPostRedisplay();
			break;

		case 'B':
			base_move_x -= 5;
			glutPostRedisplay();
			break;
		case 'H':
			base_move_y += 5;
			glutPostRedisplay();
			break;
		case 'N':
			base_move_y -= 5;
			glutPostRedisplay();
			break;

		case 'Z':
			base_angle = (base_angle + 5) % 360;
			glutPostRedisplay();
			break;

		case 'A':
			base_angle = (base_angle - 5) % 360;
			glutPostRedisplay();
			break;

		case 'X':
			elbow_angle = (elbow_angle + 5) % 360;
			glutPostRedisplay();
			break;

		case 'S':
			elbow_angle = (elbow_angle - 5) % 360;
			glutPostRedisplay();
			break;

		case 'C':
			wrist_rotation = (wrist_rotation + 5) % 360;
			glutPostRedisplay();
			break;

		case 'D':
			wrist_rotation = (wrist_rotation - 5) % 360;
			glutPostRedisplay();
			break;
		
		case 'F':
			if (claw_open_close)
			{
				claw_tmp -= 0.5;
				claw_tmp2 += 0.8;
				claw_open_close = 0;
			}
			glutPostRedisplay();
			break;

		case 'V':
			if (claw_open_close == 0)
			{
				claw_tmp += 0.5;
				claw_tmp2 -= 0.8;
				claw_open_close = 1;
			}
			glutPostRedisplay();
			break;

		case 'R':
			claw_tmp -= 0.5;
			claw_tmp2 += 0.8;
			click_r = 1;
			glutPostRedisplay();
			break;

		case 'Q':
			exit(1);
			break;

		case 'L':
			light_choose += 1;
			break;

		case 'J':
			spot_light_move += 10;
			break;
		case 'M':
			spot_light_move -= 10;
			break;

		case 'I':
			spot_light_move2 += 10;
			break;
		case 'K':
			spot_light_move2 -= 10;
			break;
			

		default:
			break;
	}
}

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

		glNormal3f(normal[0] , normal[1] , normal[2] );
		if (color)
			glColor3f(1.0, 1.0, 0);
		glVertex3f(vertex[0]-300, vertex[1] , vertex[2] + 100);


		glNormal3f(normal[3] , normal[4] , normal[5] );
		if (color)
			glColor3f(1.0, 1.0, 0);
		glVertex3f(vertex[3] - 300, vertex[4] , vertex[5] + 100);


		glNormal3f(normal[6] , normal[7] , normal[8] );
		if (color)
			glColor3f(1.0, 1.0, 0);
		glVertex3f(vertex[6] - 300, vertex[7] , vertex[8] + 100);

		glEnd();
	}
}

void draw_floor()
{
	for (float idx_i = -500.0; idx_i < 500.0; idx_i += 10)
	{
		for (float idx_j = -500.0; idx_j < 500.0; idx_j += 10)
		{
			glBegin(GL_QUADS);
			glColor3f(0.5, 0.3, 0.1);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(idx_i, -80, idx_j);
			glVertex3f(idx_i + 10.0, -80, idx_j);
			glVertex3f(idx_i + 10.0, -80, idx_j + 10.0);
			glVertex3f(idx_i, -80, idx_j + 10.0);
			glEnd();
		}
	}
}

void sun_light_set()
{
	GLfloat sun_light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat sun_light_diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glEnable(GL_LIGHT0);
}

void spot_light_set()
{
	if (light_choose % 4 == 0) //W
	{
		GLfloat spotlight_ambient[4] = { 0.1, 0.1, 0.1, 1.0 };
		GLfloat spotlight_diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat spotlight_specular[4] = { 1.05, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);
		glutPostRedisplay();
	}
	else if (light_choose % 4 == 1) //G
	{
		GLfloat spotlight_ambient[4] = { 0.1, 0.1 * 5, 0.1, 1.0 };
		GLfloat spotlight_diffuse[4] = { 1.0, 1.0 * 5, 1.0, 1.0 };
		GLfloat spotlight_specular[4] = { 1.05, 1.0 * 5, 1.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);
		glutPostRedisplay();
	}
	else if (light_choose % 4 == 2) //B
	{
		GLfloat spotlight_ambient[4] = { 0.1, 0.1, 0.1 * 5, 1.0 };
		GLfloat spotlight_diffuse[4] = { 1.0, 1.0, 1.0 * 5, 1.0 };
		GLfloat spotlight_specular[4] = { 1.05, 1.0, 1.0 * 5, 1.0 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);
		glutPostRedisplay();
	}
	else //R
	{
		GLfloat spotlight_ambient[4] = { 0.1 * 5, 0.1, 0.1, 1.0 };
		GLfloat spotlight_diffuse[4] = { 1.0 * 5, 1.0, 1.0, 1.0 };
		GLfloat spotlight_specular[4] = { 1.05 * 5, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);
		glutPostRedisplay();
	}

	spotlight_position[2] = spot_light_move;
	spotlight_position[0] = spot_light_move2;

	glLightfv(GL_LIGHT1, GL_POSITION, spotlight_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 32.0);
	glEnable(GL_LIGHT1);
}

void draw_arm()
{
	glPushMatrix();

	glTranslatef(0.0 + base_move_x, 0.0, 0.0 + base_move_y);
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

	glTranslatef((-0.05 + claw_tmp) * 100, 50.0, 0.0);

	claw_open_close_1();

	glTranslatef((0.05 + claw_tmp2) * 100, 0.0, 0.0);
	claw_open_close_2();

	if (click_r)
	{
		claw_tmp += 0.5;
		claw_tmp2 -= 0.8;
		click_r = 0;
		Sleep(200);
		glutPostRedisplay();
	}
	glPopMatrix();
}

void display(void)
{
	glClearColor(0, 150, 150, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(600.0, 600.0, 600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(x_r, 1.0f, 0.0f, 0.0f);
	glRotatef(y_r, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlight_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight_direction);
	
	sun_light_set();
	spot_light_set();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	draw_duck();
	draw_arm();
	draw_floor();
	glutSwapBuffers();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
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
}

void My_Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		x_c = x - y_r;
		y_c = -y + x_r;
	}
	else
		mouseDown = false;
}

void Mouse_Moving(int x, int y)
{
	if (mouseDown)
	{
		y_r = x - x_c;
		x_r = y + y_c;
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1200);
	glutCreateWindow("HW3");
	init();
	glutReshapeFunc(My_Reshape);
	glutDisplayFunc(display);
	glutMouseFunc(My_Mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(Mouse_Moving);
	glutMainLoop();
	return 0;
}