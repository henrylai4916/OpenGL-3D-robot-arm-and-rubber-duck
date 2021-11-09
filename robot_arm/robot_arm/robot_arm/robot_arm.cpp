#include "glut.h"
#include <iostream>
using namespace std;
static int base_angle = 0;
static int elbow_angle = 0;
static int wrist_rotation = 0;
static int lower_arm_h = 1;
static int upper_arm_h = 2;
static int claw_base_h = 2;
static float claw_tmp = 0;
static float claw_tmp2 = 0;

void base()
{
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0.0);
	glScalef(1.0, 0.5, 1.0);
	glColor3f(0.2, 0.8, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
}

void lower_arm()
{
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(0.4, 2.0, 0.4);
	glutWireCube(1.0);
	glColor3f(0.5, 0.5, 1.0);
	glPopMatrix();
}

void upper_arm()
{
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(0.4, 2.0, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void claw_base()
{
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glScalef(2.0, 0.5, 0.4);
	glColor3f(1.0, 0.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void claw_open_close_1()
{
	glPushMatrix();
	glTranslatef(0.7, 0.2, 0.0);
	glScalef(0.5, 0.5, 0.4);
	glColor3f(0.0, 0.0, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
}

void claw_open_close_2()
{
	glPushMatrix();
	glTranslatef(-0.7, 0.2, 0.0);
	glScalef(0.5, 0.5, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

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

	glTranslatef(-0.3, 0.5, 0.0);
	claw_open_close_1();


	glTranslatef(0, 0.0, 0.0);
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
		claw_tmp += 0.0;
		glutPostRedisplay();
		break;

	case 'r':
		claw_tmp += 0.5;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 10);
	glutInitWindowSize(1000, 600);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}