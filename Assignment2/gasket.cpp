/*
* CSCI 325 - Computer Graphics
* Aline Lais Gomes Tavares
* Assignment 2: Triangles and User Input
*/

#include <iostream>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else		       
#include <GL/glut.h>         
#endif

int WIDTH = 600, HEIGHT = 600; // default window size
int MAX_N = 7; //default max number of divisions of the triangles


typedef GLfloat points[2]; //structure for coordinates (x,y) of points

GLfloat RTiangle = 0.25, GTriangle = 0.25, BTriangle = 0.7; //for internal triangles color
GLfloat RBg = 0.1, GBg = 0.1, BBg = 0.1; 					// for bckground color

bool CHANGEFLAG = false; // flag to control color change
int ANIMATIONFLAG = 0; 
int n = -1; 



/* Function to draw triangles */
void triangle(points a, points b, points c) {
	glBegin(GL_TRIANGLES); 
	glVertex2fv(a); 
	glVertex2fv(b);  
	glVertex2fv(c);
	glEnd();
}

/*Function for the recursion of the gasket algorithm as seen in class*/
void divide_triangle(points a, points b, points c, int m){
	/* triangle subdivision using vertex coordinates */
	points v0, v1, v2;
	int j;

	if(m>0){
		for(j=0; j<2; j++){
			v0[j]=(a[j]+b[j])/2;
		}

		for(j=0; j<2; j++) {
			v1[j]=(a[j]+c[j])/2;
		}

		for(j=0; j<2; j++){
			v2[j]=(b[j]+c[j])/2;
		}

		divide_triangle(a, v0, v1, m-1);
		divide_triangle(c, v1, v2, m-1);
		divide_triangle(b, v2, v0, m-1);
	}
	else {
		glColor3f(RTiangle, GTriangle, BTriangle);
		triangle(a,b,c);
	}
}

/**/

void display(void){
	points v[] = {{-2.0, -1}, {2.0, -1.0}, {0.0, 2.0}}; //Initial big triangle
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable( GL_CULL_FACE );

	glColor3f(RBg, GBg, BBg);
	triangle(v[0],v[1],v[2]);
	divide_triangle(v[0], v[1], v[2], n);
	glFlush();
}

/**/
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.5);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (1.0, 1.0, 1.0, 0.0);
}

/**/
void timer(int i) {
	
	if (n <= MAX_N)
		n = n + 1;
	else 
		n = 0;
    glutPostRedisplay();
    //GLut function to do the animation based on time parameter (300ms)
    glutTimerFunc(300, timer, 0); //(ms, callback, ?)
}

/*
*if ANIMATIONFLAG was set 1, then this mouse callback will be used and the animation 
* will occur spontaneously. If you left click on the screen, the triangle colors will be inverted.
*/
void mouse_animation(int button, int state, int x, int y) {

	// changes colors with left click
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		n = -1;
		if (CHANGEFLAG == false) {
			RTiangle = 0.1;
			GTriangle = 0.1;
			BTriangle = 0.1;
			RBg = 0.25;
			GBg = 0.25;
			BBg = 0.7;
			CHANGEFLAG = true;
		} else {
			RTiangle = 0.25;
			GTriangle = 0.25;
			BTriangle = 0.7;
			RBg = 0.1;
			GBg = 0.1;
			BBg = 0.1;
			CHANGEFLAG = false;

		}
		glutPostRedisplay();
	}

	//exists with right click
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		exit(0);
	}

}

/*
*if ANIMATIONFLAG was set 0 (default), then this mouse callback will be used and the animation 
* will occur every time you left click on the screen only.
*/
void mouse_click(int button, int state, int x, int y) {

	// changes colors with left click
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (n <= MAX_N)
			n = n + 1;
		else 
			n = 0;
    glutPostRedisplay();
		//n = -1;
	}

	//exists with right click
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		exit(0);
	}

}

/*Reshape callback to adjust the window size*/
void reshape (int w, int h) {
GLdouble aspect = (GLdouble)w / (GLdouble)h;
glMatrixMode   (GL_PROJECTION);
glLoadIdentity ();
gluOrtho2D     (-2.0 * aspect, 2.0 * aspect, -2.0, 2.5);
glMatrixMode   (GL_MODELVIEW);
glViewport     (0, 0, w, h);
}

/**/
int main (int argc, char** argv){

	if (argc > 2){
		WIDTH = atoi(argv[1]);
		HEIGHT = atoi(argv[2]);
	}

	if (argc >= 4) {
		MAX_N = atoi(argv[3]);
	}

	if (argc >= 5) {
		ANIMATIONFLAG = atoi(argv[4]);
	}

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0,0);

	glutCreateWindow("Gasket");

	if (ANIMATIONFLAG == 0) {
		glutMouseFunc(mouse_click);

	} else  if (ANIMATIONFLAG == 1){
		glutMouseFunc(mouse_animation);
		timer(0);
	}

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}