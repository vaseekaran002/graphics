#include<GL/freeglut.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-320.0, 320.0, -240.0, 240.0, 1, -1);
	//glOrtho(0.0, 640.0, 0.0, 480.0, 1, -1);
}

vector<vector<double>> createTranslationMat(double tx, double ty) {

	vector<vector<double>> res = { {1,0,tx},{0,1,ty},{0,0,1} };

	return res;

}
vector<vector<double>> createRotationMat(double theta) {
	theta *= 3.14 / 180;
	vector<vector<double>> res = { {cos(theta),-sin(theta),0},{sin(theta),cos(theta),0},{0,0,1} };
	return res;
}
vector<vector<double>> createRotationMatPP(double theta,double xr,double yr) {
	theta *= 3.14 / 180;
	vector<vector<double>> res = { {cos(theta),-sin(theta),xr*(1 - cos(theta)) + yr*sin(theta)},{sin(theta),cos(theta),yr * (1 - cos(theta)) - xr * sin(theta)},{0,0,1}};
	return res;
}
vector<vector<double>> createScalingMat(double sx, double sy) {
	vector<vector<double>> res = { {sx,0,0},{0,sy,0},{0,0,1} };
	return res;
}
vector<vector<double>> createScalingMatPP(double sx, double sy,double xf,double yf) {
	vector<vector<double>> res = { {sx,0,xf*(1-sx)},{0,sy,yf*(1-sy)},{0,0,1}};
	return res;
}
vector<vector<double>> createReflectionXMat() {

	vector<vector<double>> res = { {1,0,0},{0,-1,0},{0,0,1} };

	return res;

}
vector<vector<double>> createReflectionYMat() {

	vector<vector<double>> res = { {-1,0,0},{0,1,0},{0,0,1} };

	return res;

}
vector<vector<double>> createReflectionOriginMat() {

	vector<vector<double>> res = { {-1,0,0},{0,-1,0},{0,0,1} };

	return res;

}
vector<vector<double>> createReflectionXYMat() {

	vector<vector<double>> res = { {0,1,0},{1,0,0},{0,0,1} };

	return res;

}
vector<vector<double>> createShearingXMat(double shx, double yref) {

	vector<vector<double>> res = { {1,shx,-(shx * yref)},{0,1,0},{0,0,1} };

	return res;

}
vector<vector<double>> createShearingYMat(double shy, double xref) {

	vector<vector<double>> res = { {1,0,0},{shy,1,-(shy * xref)},{0,0,1} };

	return res;

}

//void DDA(double x0, double x1, double y0, double y1) {
//	double dx = x1 - x0;
//	double dy = y1 - y0;
//	double step;
//	double xinc, yinc;
//	if (abs(dx) > abs(dy)) {
//		step = abs(dx);
//	}
//	else {
//		step = abs(dy);
//	}
//	xinc = dx / step;
//	yinc = dy / step;
//	glBegin(GL_POINTS);
//	for (int i = 0; i < step; i++) {
//		glVertex2d(round(x0), round(y0));
//		x0 += xinc;
//		y0 += yinc;
//	}
//	glEnd();
//}
void DDA(double x0, double x1, double y0, double y1) {
	double dx = x1 - x0;
	double dy = y1 - y0;
	double step, xinc, yinc;
	if (abs(dx) > abs(dy)) {
		step = abs(dx);
	}
	else {
	step = abs(dy);
	}
	xinc = dx / step;
	yinc = dy / step;
	glBegin(GL_LINES);
	for (int i = 0; i < step; i++) {
		glVertex2d(round(x0), round(x1));
		x0 += xinc;
		y0 += yinc;
	}
	glEnd();
	glFlush();
}

void plot(double x, double y) {
	glVertex2d(x, y);
}

//void bresenhamLine(double x0, double x1, double y0, double y1) {
//	bool isLeftToRight;
//	if (x0 < x1) isLeftToRight = true;
//	else isLeftToRight = false;
//	double dx = x1 - x0;
//	double dy = y1 - y0;
//	double m = dx / dy;
//	double x = x0;
//	double y = y0;
//	if (dx < 0) dx *= -1;
//	if (dy < 0) dy *= -1;
//	glBegin(GL_POINTS);
//	if (m > 0 && m <= 1) {
//		double p = 2 * dy - dx;
//		for (int i = 0; i < dx; i++) {
//			if (p < 0) {
//				glVertex2d(round(x), round(y));
//				p = p + 2 * dy;
//			}
//			else {
//				if (isLeftToRight) y += 1;
//				else y -= 1;
//				glVertex2d(round(x), round(y));
//				p = p + 2*(dy - dx);
//			}
//			if (isLeftToRight) x += 1;
//			else x -= 1;
//		}
//	}
//	else if (m > 1) {
//		double p = 2 * dx - dy;
//		for (int i = 0; i < dy; i++) {
//			if (p < 0) {
//				glVertex2d(round(x), round(y));
//				p = p + 2 * dx;
//			}
//			else {
//				if (isLeftToRight) x += 1;
//				else x -= 1;
//				glVertex2d(round(x), round(y));
//				p = p + 2 * (dx - dy);
//			}
//			if (isLeftToRight) y += 1;
//			else y -= 1;
//		}
//	}
//	else if (m < 0 && m >= -1) {
//		double p = 2 * dy - dx;
//		for (int i = 0; i < dx; i++) {
//			if (p < 0) {
//				glVertex2d(round(x), round(y));
//				p = p + 2 * dy;
//			}
//			else {
//				if (isLeftToRight) y -= 1;
//				else y += 1;
//				glVertex2d(round(x), round(y));
//				p = p + 2 * (dy - dx);
//			}
//			if (isLeftToRight) x += 1;
//			else x -= 1;
//		}
//	}
//	else {
//		double p = 2 * dx - dy;
//		for (int i = 0; i < dy; i++) {
//			if (p < 0) {
//				glVertex2d(round(x), round(y));
//				p = p + 2 * dx;
//			}
//			else {
//				if (isLeftToRight) x += 1;
//				else x -= 1;
//				glVertex2d(round(x), round(y));
//				p = p + 2 * (dx - dy);
//			}
//			if (isLeftToRight) y -= 1;
//			else y += 1;
//		}
//	}
//	glEnd();
//	glFlush();
//}
void bresenhamLine(double x0, double x1, double y0, double y1){
	double xinc = 1, yinc=1,x,y,dx,dy;
	x = x0;
	y = y0;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x1 < x0) {
		xinc = -1;
	}
	if (y1 < y0) {
		yinc = -1;
	}
	glBegin(GL_POINTS);
	plot(x, y);
	if (dx > dy) {
		double p = 2 * dy - dx;
		for (int i = 0; i < dx; i++) {
			if (p < 0) {
				p += 2 * dy;
			}
			else {
				p += 2 * (dy - dx);
				y += yinc;
			}
			x += xinc;
			plot(x, y);
		}
	}
	else {
		double p = 2 * dx - dy;
		for (int i = 0; i < dy; i++) {
			if (p < 0) {
				p += 2 * dx;
			}
			else {
				p += 2 * (dx - dy);
				x += xinc;
			}
			y += yinc;
			plot(x, y);
		}
	}
	
	glEnd();
	glFlush();
}

//void midPointCircle(double xp,double yp,double radius) {
//	double x = radius, y = 0;
//	glBegin(GL_POINTS);
//	glVertex2d(x + xp, y + yp);
//	if (radius > 0) {
//		glVertex2d(x+xp, -y + yp);
//		glVertex2d(y + xp, x + yp);
//		glVertex2d(-y + xp, x + yp);
//	}
//	double p = 1 - radius;
//	while (x > y) {
//		y++;
//		if (p <= 0) {
//			p += 2 * y + 1;
//		}
//		else {
//			x--;
//			p += 2 * y - 2 * x + 1;
//		}
//
//		if (x < y) break;
//		glVertex2d(x + xp,y + yp);
//		glVertex2d(-x + xp,y + yp);
//		glVertex2d(x + xp,-y + yp);
//		glVertex2d(-x + xp,-y + yp);
//
//		if (x != y) {
//			glVertex2d(y + xp,x + yp);
//			glVertex2d(-y + xp,x + yp);
//			glVertex2d(y + xp,-x + yp);
//			glVertex2d(-y + xp,-x + yp);
//		}
//	}
//	glEnd();
//	glFlush();
//}
void midPointCircle(double xp, double yp, double radius) {
	double x = radius, y = 0;
	glBegin(GL_POINTS);
	double p = 1 - radius;
	while (x > y) {
		y++;
		if (p <= 0) {
			p += 2 * y + 1;
		}
		else {
			x--;
			p += 2 * (y - x) + 1;
		}
		if (x < y) break;
		glVertex2d(x + xp, y + yp);
		glVertex2d(-x + xp, y + yp);
		glVertex2d(x + xp, -y + yp);
		glVertex2d(-x + xp, -y + yp);
		if (x != y) {
			glVertex2d(y + xp, x + yp);
			glVertex2d(-y + xp,x + yp);
			glVertex2d(y + xp, -x + yp);
			glVertex2d(-y + xp,- x + yp);
		}
	}

	glEnd();
}

void matMul(vector<vector<double>>& a, vector<vector<double>>& b, vector<vector<double>>& res) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b[0].size(); j++) {
			res[i][j] = 0;
			for (int k = 0; k < a[0].size(); k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}


vector<vector<double>> ballCenter = {{-120},{60},{1}};

void writepoint(int x, int y) {
	string pt = "(" + to_string(x) + "," + to_string(y) + ")";
	glRasterPos2i(x - 25, y - 15);
	for (int k = 0; pt[k] != '\0'; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, pt[k]);
	}
}
void writepoints(vector<int> area) {
	for (int i = 0; i < area.size(); i = i + 2) {
		writepoint(area[i], area[i + 1]);
	}
}

void plot(vector<int> area) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < area.size(); i = i + 2) {
		glVertex2d(area[i], area[i + 1]);
	}
	glEnd();
	writepoints(area);
}

//void bowler() {
//	midPointCircle(-100, 0, 30);
//	bresenhamLine(-100,-100,-150,-30);
//	bresenhamLine(-170, -100, 0, -70);
//	bresenhamLine(-170, -120, 0, 50);
//	bresenhamLine(-100, -150, -150, -200);
//	bresenhamLine(-100, -50, -150, -200);
//	bresenhamLine(-100, -50, -70, -20);
//	midPointCircle(ballCenter[0][0], ballCenter[1][0], 10);
//}

void timer(int) {

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	vector<vector<double>> h1 = createTranslationMat(1, -0.15);
	vector<vector<double>> res(3, vector<double>(1, 0));
	matMul(h1, ballCenter, res);
	ballCenter = res;

}

typedef struct point {
	double x, y;
	vector<double> regionCode = { 0,0,0,0 };
} point;

void point_writer(double x, double y) {
	string str = "(" + to_string((int)x) + "," + to_string((int)y) + ")";
	glRasterPos2i(x - 25, y - 15);
	for (int i = 0; i < str.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
	}
}

void draw_clipwindow(vector<double> clipwindow) {
	
	double xmin = clipwindow[0];
	double xmax = clipwindow[1];
	double ymin = clipwindow[2];
	double ymax = clipwindow[3];
	point_writer(xmin, ymin);
	point_writer(xmin, ymax);
	point_writer(xmax, ymin);
	point_writer(xmax, ymax);
	glBegin(GL_LINES);
	glVertex2d(xmin, ymin);
	
	glVertex2d(xmin, ymax);
	
	glVertex2d(xmin, ymin);
	glVertex2d(xmax, ymin);
	glVertex2d(xmax, ymax);
	
	glVertex2d(xmax, ymin);
	glVertex2d(xmax, ymax);
	
	glVertex2d(xmin, ymax);
	glEnd();

}

point findRC(vector<double> clipwindow,point p) {
	double xmin = clipwindow[0];
	double xmax = clipwindow[1];
	double ymin = clipwindow[2];
	double ymax = clipwindow[3];

	if (p.y > ymax) {
		p.regionCode[0] = 1;
	}
	if (p.y < ymin) {
		p.regionCode[1] = 1;
	}
	if (p.x > xmax) {
		p.regionCode[2] = 1;
	}
	if (p.x < xmin) {
		p.regionCode[3] = 1;
	}
	return p;
}

bool checkOR(vector<double> a, vector<double> b){
	int n = a.size();
	for (int i = 0; i < n; i++) {
		int x = (int)a[i] | (int)b[i];
		if (x == 1) {
			return false;
		}
		
	}
	return true;
}

bool checkAND(vector<double> a, vector<double> b) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		int x = (int)a[i] & (int)b[i];
		if (x == 1) {
			return true;
		}
		
	}
	return false;
}

void cohen_suther(vector<double> clipwindow, vector<double> line) {
	double xmin = clipwindow[0];
	double xmax = clipwindow[1];
	double ymin = clipwindow[2];
	double ymax = clipwindow[3];

	point p1, p2;
	p1.x = line[0];
	p2.x = line[1];
	p1.y = line[2];
	p2.y = line[3];

	
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	p1 = findRC(clipwindow, p1);
	p2 = findRC(clipwindow, p2);
	double m = (p2.y - p1.y) / (p2.x - p1.x);

	if (checkOR(p1.regionCode, p2.regionCode)) {
		cout << "\n trivially accepted";
	}
	else {
		cout << "\n trivially not accepted";
		if (checkAND(p1.regionCode, p2.regionCode)) {
			cout << "\ntrivially Rejected";
		}
		else {
			double x, y;
			vector<double> left = { 0,0,0,1 };
			vector<double> right = { 0,0,1,0 };
			vector<double> top = { 1,0,0,0 };
			vector<double> bottom = { 0,1,0,0 };
			if (checkAND(p1.regionCode, left))
			{
				x = xmin;
				y = p1.y + m * (x - p1.x);
				p1.x = x;
				p1.y = y;
				
			}
			if (checkAND(p1.regionCode, right) )
			{
				x = xmax;
				y = p1.y + m * (x - p1.x);
				p1.x = x;
				p1.y = y;
				
			}
			if (checkAND(p1.regionCode, bottom) )
			{
			
				y = ymin;
				x = p1.x + (y - p1.y) / m;
				p1.x = x;
				p1.y = y;
				
			}
			if (checkAND(p1.regionCode, top) )
			{
				y = ymax;
				x = p1.x + (y - p1.y) / m;
				p1.x = x;
				p1.y = y;
				
			}
			if (checkAND(p2.regionCode, left))
			{
				x = xmin;
				y = p2.y + m * (x - p2.x);
				p2.x = x;
				p2.y = y;
				
			}
			if (checkAND(p2.regionCode, right) )
			{
				x = xmax;
				y = p2.y + m * (x - p2.x);
				p2.x = x;
				p2.y = y;
				
			}
			if (checkAND(p2.regionCode, bottom) )
			{
				y = ymin;
				x = p2.x + (y - p2.y) / m;
				p2.x = x;
				p2.y = y;
				
			}
			if (checkAND(p2.regionCode, top) )
			{
			
				y = ymax;
				x = p2.x + (y - p2.y) / m;
				p2.x = x;
				p2.y = y;
				
			}


		}
	}
	

	
	glBegin(GL_LINES);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();

}

void window_viewport_mapping(vector<int> window, vector<int> viewport, vector<int> window_object) {

}



void fan() {
	midPointCircle(0, 0, 10);
	bresenhamLine(0, 7, 15, 45);
	bresenhamLine(0, -7, 15, 45);
	bresenhamLine(-7, 7, 45, 45);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	fan();
	/*glBegin(GL_LINES);
	glVertex2d(-320, 0);
	glVertex2d(320, 0);
	glVertex2d(0,-240);
	glVertex2d(0, 240);
	glEnd()*/;
	/*vector<int> window = { -300,-100,-100,-100,-100,100,-300,100 };
	vector<int> viewport = { 0,-70,200,-70,200,70,0,70 };
	vector<int> window_object = { -250,-75,-150,-75,-150,75,-250,75 };
	vector<int> viewport_object;
	glColor3f(120.0f, 0.0f, 0.0f);
	plot(window);
	plot(viewport);
	glColor3f(0.0f, 120.0f, 0.0f);
	plot(window_object);
	viewport_object = window_viewport_mapping(window, viewport, window_object);
	plot(viewport_object);*/
	//bowler();
	/*vector<double> clipwindow = { 10,210,10,110 };
	vector<double> line = { 15,50,5,120 };
	draw_clipwindow(clipwindow);
	cohen_suther(clipwindow, line);*/
	//DDA(0, 100, 0, 100);
	//bresenhamLine(100, 0, 100, 0);
	//midPointCircle(10, 10, 100);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("lab text practice");
	glutDisplayFunc(myDisplay);
	glutTimerFunc(0, timer, 0);
	myInit();
	glutMainLoop();
	return 1;
}
