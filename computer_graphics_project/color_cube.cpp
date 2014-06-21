#include "stdafx.h"
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

// 키보드 입력을 받기 위해 두가지 전역 변수를 설정해준다. (초기값은 모두 0)
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// 정육면체의 각 면에 색을 설정해준다.

	// 1
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);
	glEnd();

	// 2
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);
	glEnd();

	// 3
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glEnd();

	// 4
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);
	glEnd();

	// 5
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glEnd();

	// 6
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);
	glEnd();

	// 명령어들을 하나씩 처리해준다. flush!
	glPopMatrix();
	glutSwapBuffers();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Color_Cube");
	//윈도우의 크기가 변할 때
	glutReshapeFunc(ChangeWindowSize);
	glutDisplayFunc(RenderScene);
	//키보드 조작에 따라 바뀌는 뷰
	glutSpecialFunc(ControlObject);
	SetupRC();
	glutMainLoop();
}