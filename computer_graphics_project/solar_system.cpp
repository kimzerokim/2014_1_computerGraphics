#include "stdafx.h"
#include <gl/glut.h>
#include <windows.h>
#include <math.h>

#define GL_PI 3.14f

void SetupRC()
{
	//ambientLight, diffuseLight, sepcularLight를 위한 값을 설정한다.
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	//light 설정
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//애니메이션을 위해 일정 시간마다 화면에 디스플레이
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(40, TimerFunc, 1);
}

void RenderScene()
{
	static GLfloat fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//첫번째 원자
	glTranslatef(0.0f, 0.0f, -100.0f);

	glColor3ub(255, 0, 0);
	glutSolidSphere(10.0f, 15, 15);
	glPushMatrix();								

	// 이 둘은 같이 움직인다.

	//두번째 원자
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f); 
	glTranslatef(90.0f, 0.0f, 0.0f);      
	glColor3ub(0, 0, 255);
	glutSolidSphere(6.0f, 15, 15);       

	// 세번째 원자 
	glRotatef(fElect1 * 4, -1.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);

	glColor3ub(255, 255, 255);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();						

	fElect1 += 10.0f;					
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void ChangeWindowSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	//GLfloat lightPos[] = { -0.0f, 0.0f, -10.0f, 1.0f };
	GLfloat lightPos[] = { -0.0f, 0.0f, -10.0f, 1.0f };

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.0f, nRange*2.0f);  
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);  

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("solar_system");

	glutTimerFunc(40, TimerFunc, 1);
	//윈도우의 크기가 변할 때
	glutReshapeFunc(ChangeWindowSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}