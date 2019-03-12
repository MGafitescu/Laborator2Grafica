#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1);
	double ratia = 0.05;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2d(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2d(x2, y2);
	}
	glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2d(x1, y1);
	}
	glEnd();
}

double DistanceToInt(double x) {
	double upper_distance = ceil(x) - x;
	double lower_distance = x - floor(x);
	if (upper_distance < lower_distance)
		return upper_distance;
	else
		return lower_distance;
}
void Display3() {
	double xmax = 30*1.1;
	double ymax = 1.1;
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < 30; x += ratia) {
		double x1, y1;
		x1 = x;
		if (x1 == 0)
			y1 = 1;
		else
			y1 = DistanceToInt(x1) / x1;
		x1 = x1 / xmax;
		y1 = y1 / ymax;
		glVertex2d(x1, y1);
	}
	glEnd();
}

void Display4() {
	double xmax, ymax, xmin, ymin;
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1);
	double ratia = 0.05;
	xmax = 0;
	xmin = 0;
	ymax = ymin = 0;
	for (double t = -pi+ratia ; t < pi; t += ratia) {
		double x, y;
		x = 2*(a*cos(t) + b) * cos(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = 2*(a * cos(t) + b) * sin(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	ymax = ymax * 1.6;
	xmax = xmax * 1.1;
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a*cos(t) + b) * cos(t);
		y = 2 * (a*cos(t) + b) * sin(t);
		x = x / xmax;
		y = y / ymax;
		glVertex2d(x, y);
	}
	glEnd();
}

void Display5() {
	double t;
	double a = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double x1;
	double y1;
	double x2;
	double y2;
	double x_sig1;
	double x_sig2;
	double y_sig1;
	double y_sig2;
	

	glColor3f(0, 0, 0); // negru
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		x1 = (a / (4 * pow(cos(t), 2) - 3));
		y1 = ((a * tan(t)) / (4 * pow(cos(t), 2) - 3));
		x1 = x1 / 1.3;
		y1 = y1 / 1.4;
		if (t == -pi / 2 + ratia)
		{
			x_sig1 = x1;
			y_sig1 = y1;
		}
		glVertex2d(x1, y1);
	}
	x_sig2 = x1 ;
	y_sig2 = y1 ;
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(x_sig1, y_sig1);
	glVertex2d(x_sig2, y_sig1);
	glVertex2d(x_sig2, y_sig2);
	glEnd();


	ratia /= 10;
	for (t = -pi / 2 + ratia * 10.5; t < -pi / 2.25 ; t += ratia * 2) {
		glColor3f(1, 0.1, 0.1); // rosu
		glBegin(GL_TRIANGLES);
		x1 = (a / (4 * pow(cos(t), 2) - 3));
		y1 = ((a * tan(t)) / (4 * pow(cos(t), 2) - 3));
		x2 = (a / (4 * pow(cos(t + ratia), 2) - 3));
		y2 = ((a * tan(t + ratia)) / (4 * pow(cos(t + ratia), 2) - 3));
		
		x1 = x1 / 1.3;
		x2 = x2 / 1.3;
		y1 = y1 / 1.4;
		y2 = y2 / 1.4;

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x_sig2, y_sig1);

		glEnd();
	}

	for (t = -pi / 4 + ratia ; t < -pi / 6 - ratia*10; t += ratia * 2) {
		glColor3f(1, 0.1, 0.1); // rosu
		glBegin(GL_TRIANGLES);

		x1 = (a / (4 * pow(cos(t), 2) - 3));
		y1 = ((a * tan(t)) / (4 * pow(cos(t), 2) - 3));
		x2 = (a / (4 * pow(cos(t + ratia), 2) - 3));
		y2 = ((a * tan(t + ratia)) / (4 * pow(cos(t + ratia), 2) - 3));

		x1 = x1 / 1.3;
		x2 = x2 / 1.3;
		y1 = y1 / 1.4;
		y2 = y2 / 1.4;

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x_sig2, y_sig1);

		glEnd();
	}
	
	
}

void Display6() {
	double xmax, ymax, xmin, ymin;
	double a = 0.1, b = 0.2;
	double ratia = 0.05;
	xmax = 0;
	xmin = 0;
	ymax = ymin = 0;
	for (double t = -9; t < 9; t += ratia) {
		double x, y;
		x = a*t - b*sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = a - b*cos(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	ymax = ymax * 2.8;
	xmax = xmax * 1.1;
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -9; t < 9; t += ratia) {
		double x, y;
		x = a*t - b*sin(t);
		y = a - b*cos(t);
		x = x / xmax;
		y = y / ymax;
		glVertex2d(x, y);
	}
	glEnd();
}


void Display7() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1);
	double ratia = 0.05;
	xmax = 0;
	xmin = 0;
	ymax = ymin = 0;
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R + r)*cos(r/R*t)-r*cos(t+r/R*t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = (R + r)*sin(r / R*t) - r*sin(t + r / R*t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	ymax = ymax * 1.5;
	xmax = xmax * 1.5;
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R + r)*cos(r / R*t) - r*cos(t + r / R*t);
		y = (R + r)*sin(r / R*t) - r*sin(t + r / R*t);
		x = x / xmax;
		y = y / ymax;
		glVertex2d(x, y);
	}
	glEnd();
}

void Display8() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1);
	double ratia = 0.05;
	xmax = 0;
	xmin = 0;
	ymax = ymin = 0;
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R - r)*cos(r / R*t) - r*cos(t - r / R*t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = (R - r)*sin(r / R*t) - r*sin(t - r / R*t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	ymax = ymax * 1.5;
	xmax = xmax * 1.5;
	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		x = (R - r)*cos(r / R*t) - r*cos(t - r / R*t);
		y = (R - r)*sin(r / R*t) - r*sin(t - r / R*t);
		x = x / xmax;
		y = y / ymax;
		glVertex2d(x, y);
	}
	glEnd();
}

void Display9() {
	double a = 0.4;
	double pi = 4 * atan(1);
	double ratia = 0.005;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4 - ratia ; t < pi / 4 ; t += ratia) {
		double x1, y1;
		double r1 = a*sqrt(2 * cos(2 * t));
		x1 = r1*cos(t);
		y1 = r1*sin(t);

		glVertex2d(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 4 - ratia  ; t < pi / 4 ; t += ratia) {
		double  x2, y2;
		double r2 = -a*sqrt(2 * cos(2 * t));
		x2 = r2*cos(t);
		y2 = r2*sin(t);

		glVertex2d(x2, y2);
	}
	glEnd();
}

void Display10() {
	double a = 0.02;
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = 0; t < 3; t += ratia) {
		double x, y;
		double r = a*exp(1 + t);
		x = r*cos(t);
		x = x / 1.15;
		y = r*sin(t);
		y = y / 1.1;
		glVertex2d(x, y);
	}
	glEnd();

}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display10();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

