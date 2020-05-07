#include <Windows.h>
#include <GL/glut.h>

void setPixel(int, int);
void init();
void display();
void Symmetry(int, int, int, int);
void ellipse(int rx, int ry, int xc, int yc);
void Symmetry8(int, int, int, int);

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OPENGL LAB 4 CIRCLE");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
void Symmetry8(int xc, int yc, int x, int y) {
	setPixel(xc + x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc + y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc + x);
	setPixel(xc - y, yc - x);
	Sleep(100);
}

void setPixel(int x, int y)
{
	
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 60.0, 0.0, 60.0);
}

void display()
{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(5);
		glTranslatef(30, 30, 0);
		glRotated(60, 0, 0, 1);
		ellipse(5, 10, 0, 0);
}

void Symmetry(int xc, int yc, int x, int y) {
	setPixel(xc + x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc + y);
	setPixel(xc - x, yc - y);
	Sleep(10);
}
void ellipse(int rx, int ry, int xc, int yc) {
	int sqr_rx = rx * rx;
	int sqr_ry = ry * ry;
	int x = 0, y = ry;
	Symmetry(xc, yc, x, y);
	int p = sqr_ry - sqr_rx * ry + 0.25 * sqr_rx;
	while (sqr_ry * x <= sqr_rx * y)
	{
		Symmetry(xc, yc, x, y);
		x++;

		if (p <= 0) p += sqr_ry + 2 * sqr_ry * x;
		else {
			y--;
			p += 2 * sqr_ry * x + sqr_ry - 2 * sqr_rx * y;
		}

	}
	while (y>=0)
	{
		Symmetry(xc, yc, x, y);
		y--;

		if (p > 0) p += sqr_rx - 2 * sqr_rx * y;
		else {
			x++;
			p += sqr_rx + sqr_ry * 2 * x - 2 * sqr_rx * y;
		}

	}
}