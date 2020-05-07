#include <Windows.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")



void display()

{
	int x0, y0, xEnd, yEnd;
	cout << "введите координаты начала линии, от 0 до 200" << endl;
	cin >> x0 >> y0;
	while (x0 > 200 || y0 > 200 || x0 < 0 || y0 < 0)
	{
		cout << "Повторите ввод, от 0 до 200" << endl;
		cin >> x0 >> y0;
	}
	cout << "введите координаты конца линии, от 0 до 200" << endl;
	cin >> xEnd >> yEnd;
	while (xEnd > 200 || yEnd > 200 || xEnd < 0 || yEnd < 0)
	{
		cout << "Повторите ввод, от 0 до 200" << endl;
		cin >> xEnd >> yEnd;
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(xEnd, yEnd);
	glEnd();
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "RUSSIAN");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("LAB1_LINE");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


