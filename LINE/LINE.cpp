#include <GL/glut.h>
#include <iostream>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")

using namespace std;

void init();
void display();
void drawLine(int, int, int, int);
void SetPixel(int, int);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RUSSIAN");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ATTRIB1");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(30);
	SetPixel(5, 15);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(40);
	SetPixel(20, 40);
	glDisable(GL_POINT_SMOOTH);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	SetPixel(15, 15);
	glDisable(GL_POINT_SMOOTH);

	glEnable(GL_LINE_STIPPLE);

	glLineWidth(8);
	glLineStipple(5, 0x0101);
	drawLine(25, 10, 50, 10);

	glLineWidth(2);
	glLineStipple(5, 0x1C47);
	drawLine(25, 20, 50, 20);

	glLineWidth(1);
	glLineStipple(5, 0xE557);
	drawLine(25, 30, 50, 30);

	glDisable(GL_LINE_STIPPLE);

	glLineWidth(20);
	drawLine(25, 40, 50, 40);

}

void SetPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawLine(int x, int y, int xend, int yend)
{
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(x, y);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(xend, yend);
	glEnd();
	glFlush();
}