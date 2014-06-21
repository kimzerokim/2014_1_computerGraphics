#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.14f

// 키보드 입력을 받기 위해 두가지 전역 변수를 설정해준다. (초기값은 모두 0)
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//초록색 점을 만든다.
	glColor3f(0.0f, 1.0f, 0.0f);
	glFlush();
}

// 키보드 조작에 따라 바뀌는 모양
void ControlObject(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 10.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 10.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 10.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 10.0f;

	// xRot, yRot가 바뀔 때 마다 새로 디스플레이 해준다.
	glutPostRedisplay();
}

void ChangeWindowSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-100.0f, 100.0f, -100.0f*h / w, 100.0f*h / w, 100.0, -100.0);
	}
	else
	{
		glOrtho(-100.0f*w / h, 100.0f*w / h, -100.0f, 100.0f, 100.0, -100.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	GLfloat x, y, z, angle;
	GLfloat r = 0.1f;
	GLfloat rstep = 0.1f;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); //(angle)
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	z = 0.0f;

	for (angle = 0.0f; angle <= (2.0f*GL_PI)*5.0f; angle += 0.1f) 
	{
		//극좌표를 이용하여 angle을 일정하게 증가시켜주며 뿌린다.
		x = r*sin(angle);
		y = r*cos(angle);
		glVertex3f(x, y, z);
		r += rstep;
		r = r *1.007;		
	}

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Vertigo");

	//윈도우의 크기가 변할 때
	glutReshapeFunc(ChangeWindowSize);
	glutDisplayFunc(RenderScene);
	//키보드 조작에 따라 바뀌는 뷰
	glutSpecialFunc(ControlObject);
	SetupRC();
	glutMainLoop();
}