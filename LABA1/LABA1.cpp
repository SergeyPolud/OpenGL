#include <Windows.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")



void Coord_Input(int& a, int& b, const char* a_name, const char* b_name)
{
	do {
		cout << "Enter " << a_name << " and " << b_name << " from 0 to 600" << endl;
		cin >> a >> b;
	} while (a < 0 || a > 600 || b < 0 || b> 600);
}


void display()
{
	int x1, y1;
	Coord_Input(x1, y1, "x1", "y1");
	int l, cnt = 0;
	cout << "Enter length" << endl;
	cin >> l;
	glColor3f(0.0, 0.0, 1.0);
	while (y1-l > 0)
	{
		if (!(cnt%2)) 
		{
			glBegin(GL_QUADS);
			glVertex2i(x1, y1 - l);
			glVertex2i(x1, y1);
			glVertex2i(x1 + l, y1);
			glVertex2i(x1 + l, y1 - l);
			glEnd();
			glFlush();
			y1 -= l;
		}
		else 
		{
			glBegin(GL_QUADS);
			glVertex2i(x1, y1 - l/2);
			glVertex2i(x1, y1);
			glVertex2i(x1 + l/2, y1);
			glVertex2i(x1 + l/2, y1 - l/2);
			glEnd();
			glFlush();
			y1 -= l / 2;
		}
		cnt++;
		y1 -= l;
	}
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

int main(int argc, char** argv)
{
	int width, height;
	cout << "Enter width and height of window" << endl;
	cin >> width >> height;
	setlocale(LC_ALL, "RUSSIAN");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("LAB1_LINE");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


