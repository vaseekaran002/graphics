#include<GL/freeglut.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

void windowSetup() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3d(-30, 0, 0);
    glVertex3d(5, 0, 0);
    glVertex3d(0, -30, 0);
    glVertex3d(0, 5, 0);
    glVertex3d(0, 0, -30);
    glVertex3d(0, 0, 5);
    glEnd();
}

void myInit() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}
void myDisplay() {
    GLfloat pos[] = { 1,0.5,1,1 };
    GLfloat col[] = { 1,0.5,1,1 };
    GLfloat M[] = { 0.0,0.5,1,1 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
    gluLookAt(0, 1, 3, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glScalef(1.2, 0.05, 1.2);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, -0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.25, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTeapot(0.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.5);
    glScalef(0.05, 1, 0.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, M);
    glPushMatrix();
    glPopAttrib();

    glutSwapBuffers();

}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D Scene");
    glutDisplayFunc(myDisplay); myInit();
    glutMainLoop();
    return 1;
}

vector<bool> keyState(256, false);
int x_angle = 0, y_angle = 0, z_angle = 0, moves = -5;
double top = -0.0;
int i = 1;

void mydisplay() {
	cout << "\ntop: " << top;
	cout << "\n i: " << i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); // X, Y and Z axis glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0f, top, moves);
	i++;
	glPushMatrix();
	glRotatef(x_angle, 1, 0, 0);
	glRotatef(y_angle, 0, 1, 0);
	glRotatef(z_angle, 0, 0, 1);
	glutWireTeapot(1);
	glPopMatrix();
	glFlush();
 glutSwapBuffers();
}

void init() {
	int WIDTH = 500, HEIGHT = 0;
	int choice = 1;
//cout << "-----PROJECTIONS-----\n1 - Parallel Projection \n 2 - Perspective Projection\nChoose any one projection : ";
//cin >> choice;
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*if (choice == 1) {
		glOrtho(-2.0, 2.0, -2.0, 2.0, 1, 100);
	}
	else {
		gluPerspective(60, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1, 100);
	}*/
	glOrtho(-2.0, 2.0, -2.0, 2.0, 1, 100);
	glMatrixMode(GL_MODELVIEW);

}

void keyOperation() {
	int change_angle = 45;
	if (keyState['w']) {
		x_angle += change_angle;
	}
	else if (keyState['S']) {
		x_angle -= change_angle;
	}
	else if (keyState['a']) {
		y_angle -= change_angle;
	}
	else if(keyState['d'])
	{
		y_angle += change_angle;
	}
	x_angle %= 360;
	y_angle %= 360;
	z_angle %= 360;

	mydisplay();
}

void keyPressed(unsigned char key,int x,int y) {
	keyState[key] = true;
	keyOperation();
}

void KeyUp(unsigned char key,int x,int y) {
	keyState[key] = false;
}

void timer(int) {
	
	if (i == 1) {
		moves = -5;
		top = 1;
	}
	else if (i <= 4) {
		moves = 0;
		top -= 0.8;
	}
	else {
		moves = 0;
		top = 0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(100 , timer, 0);
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D");
	glutDisplayFunc(mydisplay);
	init();
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(KeyUp);
	glutMainLoop();

}




