#include "stdafx.h"
#include <windows.h>
#include <gl/glut.h>

GLfloat window_width;
GLfloat window_height;

//4사각형을 그리기 위해 전역변수를 설정해준다.
GLfloat x1 = -90.0f;
GLfloat y1 = -60.0f;
GLfloat x1_inner = -90.0f;
GLfloat y1_inner = -60.0f;
GLfloat x1step = 1.0f;
GLfloat y1step = 1.0f;

GLfloat x2 = -50.0f;
GLfloat y2 = 60.0f;
GLfloat x2_inner = -50.0f;
GLfloat y2_inner = 60.0f;
GLfloat x2step = 1.0f;
GLfloat y2step = 1.0f;

GLfloat x3 = -20.0f;
GLfloat y3 = -60.0f;
GLfloat x3_inner = -20.0f;
GLfloat y3_inner = -60.0f;
GLfloat x3step = 1.0f;
GLfloat y3step = 1.0f;

GLfloat x4 = 30.0f;
GLfloat y4 = 60.0f;
GLfloat x4_inner = 30.0f;
GLfloat y4_inner = 60.0f;
GLfloat x4step = 1.0f;
GLfloat y4step = 1.0f;

GLsizei rsize = 30.0f;
GLsizei rsize_inner = 15.0f;


GLfloat padding = (rsize - rsize_inner) / 2;

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//1
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x1 + rsize, y1 + rsize);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(x1_inner + padding, y1_inner + padding, x1_inner + rsize - padding, y1_inner + rsize - padding);

	//2
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x2, y2, x2 + rsize, y2 + rsize);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(x2_inner + padding, y2_inner + padding, x2_inner + rsize - padding, y2_inner + rsize - padding);

	//3
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(x3, y3, x3 + rsize, y3 + rsize);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x3_inner + padding, y3_inner + padding, x3_inner + rsize - padding, y3_inner + rsize - padding);

	//4
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(x4, y4, x4 + rsize, y4 + rsize);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x4_inner + padding, y4_inner + padding, x4_inner + rsize - padding, y4_inner + rsize - padding);

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	//1번 사각형을 이동
	if (x1 > window_width - rsize || x1 < -window_width)
		x1step = -x1step;

	if (y1 > window_height - rsize || y1 < -window_height)
		y1step = -y1step;

	x1 += x1step;
	x1_inner += x1step;
	y1 += y1step;
	y1_inner += y1step;

 	//2번 사각형을 이동
 	if (x2 > window_width - rsize || x2 < -window_width)
 		x2step = -x2step;
 
 	if (y2 > window_height - rsize || y2 < -window_height)
 		y2step = -y2step;
 
 	x2 -= x2step;
 	x2_inner -= x2step;
 	y2 += y2step;
 	y2_inner += y2step;

	//3번 사각형을 이동
	if (x3 > window_width - rsize || x3 < -window_width)
		x3step = -x3step;

	if (y3 > window_height - rsize || y3 < -window_height)
		y3step = -y3step;

	x3 += x3step;
	x3_inner += x3step;
	y3 -= y3step;
	y3_inner -= y3step;

	//4번 사각형을 이동
	if (x4 > window_width - rsize || x4 < -window_width)
		x4step = -x4step;

	if (y4 > window_height - rsize || y4 < -window_height)
		y4step = -y4step;

	x4 -= x4step;
	x4_inner -= x4step;
	y4 -= y4step;
	y4_inner -= y4step;

	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);
}

void ChangeWindowSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f*h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//정사각형 view로 설정하면 대각선으로만 움직인다.
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("BounceRectangle");
	//윈도우의 크기가 변할 때
	glutReshapeFunc(ChangeWindowSize); 
	glutDisplayFunc(RenderScene); 
	glutTimerFunc(20, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}