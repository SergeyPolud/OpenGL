#include <Windows.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <time.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")

using namespace std;

struct Vector2
{
	GLdouble x;
	GLdouble y;
};

struct Point
{
	GLdouble x;
	GLdouble y;
};

bool DetectConvex(Point*, Vector2*, int);
void setPixel(Point);
void setPixel(GLdouble, GLdouble);
void init();
void display();
bool TestInside(Point*, Vector2*, Point, Point, Point, int);
void DrawLine(Point, Point);

int main(int argc, char** argv) 
{
	srand(uint8_t(time(NULL)));
	setlocale(LC_ALL, "RUSSIAN");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("RAYCASTING");
	init();
	glutDisplayFunc(display);	
	glutMainLoop();
	return 0;
}

void setPixel(Point p)
{
	
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
}
void setPixel(GLdouble x, GLdouble y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
void DrawLine(Point a, Point b)
{
	glBegin(GL_LINES);
	glVertex2f(a.x, a.y);
	glVertex2f(b.x, b.y);
	glEnd();
	glFlush();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	cout << "Enter point cnt:";
	int cnt;
	cin >> cnt;
	Point* ptArr = new Point[cnt];
	for (int i = 0; i < cnt; i++)
	{
		cout << "Point[" << i << "] X = ";
		cin >> ptArr[i].x;
		cout << "Point[" << i << "] Y = ";
		cin >> ptArr[i].y;
	}
	Vector2* vecArr = new Vector2[cnt];
	for (int i = 0; i < cnt - 1; i++)
	{
		vecArr[i].x = ptArr[i + 1].x - ptArr[i].x;
		vecArr[i].y = ptArr[i + 1].y - ptArr[i].y;
	}
	vecArr[cnt - 1].x = ptArr[0].x - ptArr[cnt - 1].x;
	vecArr[cnt - 1].y = ptArr[0].y - ptArr[cnt - 1].y;
	glPointSize(5);
	if (!DetectConvex(ptArr, vecArr, cnt)) cout << "Вогнутый" << endl;
	else cout << "Выпуклый" << endl;
	GLdouble xMin = 999, xMax =-999;
	GLdouble yMin = 999, yMax =-999;
	double g = 0, b = 1.0;
	glColor3i(0, g, b);
	glEnable(GL_POINT_SMOOTH);
	for (int i = 0; i < cnt; i++)
		if (ptArr[i].x < xMin) xMin = ptArr[i].x;
		else if (ptArr[i].x > xMax) xMax = ptArr[i].x;
	for (int i = 0; i < cnt; i++)
		if (ptArr[i].y < yMin) yMin = ptArr[i].y;
		else if (ptArr[i].y > yMax) yMax = ptArr[i].y;
	Point max = { xMax, yMax };
	Point min = { xMin, yMin };
	double delta =  1.0 / double(yMax - yMin);
	for (GLdouble y = yMin; y < yMax; y++)
	{
		for (GLdouble x = xMin; x < xMax; x++)
		{
			Point current = { x+1.00000001, y };
			if (TestInside(ptArr, vecArr, current, max, min, cnt)) setPixel(current);
		}
		g += delta;
		b -= delta;
		glColor3f(0.0, g, b);
	}
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(3);
	for (int i = 0; i < cnt - 1; i++)
		DrawLine(ptArr[i], ptArr[i + 1]);
	DrawLine(ptArr[cnt - 1], ptArr[0]);
}

bool TestInside(Point* ptArr, Vector2* vecArr, Point cur, Point max, Point min, int cnt)
{
	Point cur2 = { max.x + 1, cur.y + 0.5 };
	Vector2 vec = { cur2.x - cur.x, cur2.y - cur.y };
	int intersections = 0;
	int test = 0;
	for (int i = 0; i < cnt; i++)
	{
		GLdouble a = vecArr[i].y;
		GLdouble b = -vecArr[i].x;
		GLdouble c = -(ptArr[i].x * a) - (ptArr[i].y * b);
		GLdouble test1 = cur.x * a + cur.y * b + c;
		GLdouble test2 = cur2.x * a + cur2.y * b + c;
		if (!(test1 < 0) ^ (test2 < 0)) continue;
		else
		{
			a = (cur2.y - cur.y);
			b = -(cur2.x - cur.x);
			c = -(cur.x * a) - (cur.y * b);
			test1 = ptArr[i].x * a + ptArr[i].y * b + c;
			test2 = ptArr[i + 1].x * a + ptArr[i + 1].y * b + c;
			if (!(test1 < 0) ^ (test2 < 0)) continue;
			else
			{
				
				int zComponent = vecArr[i].x * vec.y - vecArr[i].y * vec.x;
				if (zComponent > 0) intersections++;
				else if(zComponent <0)intersections--;
			}
		}
	}
	if (intersections) return true;
	else return false;
}

bool DetectConvex(Point* arr, Vector2* vecArr, int cnt)
{
	int zComponent, zPrev;
	zPrev = vecArr[0].x * vecArr[1].y - vecArr[0].y * vecArr[1].x;
	for (int i = 1; i < cnt - 1; i++)
	{
		zComponent = vecArr[i].x * vecArr[i + 1].y - vecArr[i].y * vecArr[i + 1].x;
		if ((zComponent > 0 && zPrev > 0) || (zComponent < 0 && zPrev < 0)) zPrev = zComponent;
		else return false;
	}
	int zLast = vecArr[cnt - 1].x * vecArr[0].y - vecArr[cnt - 1].y * vecArr[0].x;
	if ((zLast > 0 && zPrev > 0) || (zLast < 0 && zPrev < 0)) return true;
	else return false;
}

//void BrezLineAlg(GLdouble x0, GLdouble y0, GLdouble xEnd, GLdouble yEnd)
//{
//	int dx = abs(xEnd - x0);
//	int dy = abs(yEnd - y0);
//	int yInc = (y0 < yEnd) ? 1 : -1;
//	int xInc = (x0 < xEnd) ? 1 : -1;
//	int x, y;
//	int lead = dx > dy ? dx : dy;
//	int p = dy > dx ? -2 * dx + dy : -2 * dy + dx;
//	x = x0;
//	y = y0;
//	setPixel(x, y);
//	if (dy > dx)
//	{
//		for (int i = 0; i < lead - 1; i++)
//		{
//			y += yInc;
//			if (p < 0)
//			{
//				x += xInc;
//				p += 2 * (dy - dx);
//			}
//			else
//			{
//				p += -2 * dx;
//			}
//			setPixel(x, y);
//		}
//	}
//	else
//	{
//		for (int i = 0; i < lead - 1; i++)
//		{
//			x += xInc;
//			if (p < 0)
//			{
//				y += yInc;
//				p += 2 * (dx - dy);
//			}
//			else
//			{
//				p += -2 * dy;
//			}
//			setPixel(x, y);
//		}
//	}
//}