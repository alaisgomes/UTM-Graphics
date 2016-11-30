/*
* CSCI 325 - Computer Graphics
* Aline Lais Gomes Tavares
* Assignment 4: Dancing Cubes

* Understanding perspective (for future reference): 
http://webglfundamentals.org/webgl/lessons/webgl-3d-perspective.html

 -----------------------------------------------------------------------
* Functions

	Keybord:
		- A: Start/stop rotation
		- S: make sphere/Icosahedron smaller
		- D: make sphere/icosahedron bigger
		- Q: Quit
		- Left/Right/Up/Down special keys(arrows) move the sphere around

	Mouse:
		- Left: Change rotations
		- Right: Start/Stop disco mode (random colors)

*/


#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else          
#include <GL/glut.h>         
#endif


/*************************************************/
/************* Global Variables *****************/

int WIDTH = 700, HEIGHT = 700,  cont = 0;

int ROTATING_FLAG = 0, RANDOM_FLAG = 0, SPIN_FLAG = 0, STOP = 0;

GLfloat vertices[][3] = {{-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5},
              {0.5,0.5,-0.5}, {-0.5,0.5,-0.5},
              {0.5,-0.5,0.5}, {0.5,0.5,0.5},
              {-0.5,0.5,0.5}, {-0.5,-0.5,0.5}
            };

 
GLfloat colors[3] = {0.4, 0.4, 0.8};



GLfloat tetha = 0.0, factor = 0.5;

//Sphere Rotation
GLfloat movSpherex = 0.0;
GLfloat movSpherey = 0.0;

GLfloat sphere_scale = 0.0;

//SPhere
#define X 0.53
#define Z 0.86

GLfloat sphere_vertices[][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};
GLuint indx[][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int i;


/*************************************************/
/************** Randomize colors ****************/

void randomizeColors (){
	if (RANDOM_FLAG == 1) {
		float r, a = 1.0;
		for (int i = 0; i< 3; i++) {
			r = (float)rand()/(float)(RAND_MAX) * a;
			colors[i] = r;
		}
	}
}

/*************************************************/
/******** Functions to help control states *******/

void chooseRotation(){
    switch(ROTATING_FLAG) {
      case 0: 
        glRotatef(tetha, 1.0, 0.0, 0.0);
        break;
      case 1:
        glRotatef(tetha, 0.0, 1.0, 0.0);
        break;
      case 2:
        glRotatef(tetha, 0.0, 0.0, 1.0);
        break;
    }
}


void spinCube () {
	if (SPIN_FLAG == 0) {
		tetha = tetha + 0.5;

	} else if (SPIN_FLAG = 1) {
		if (factor == 30.0 && STOP == 0) {
			tetha = tetha + factor;
			cont++;
			if (cont == 40) {
				STOP = 1;
				cont--;
			}
		} else {
			tetha = tetha + factor;
			if (cont == 0)
				factor = factor + 0.5;
		}
	}  

	if (tetha> 360) 
		tetha = 0.0;

	glutPostRedisplay();
}


/*************************************************/
/************* Shapes drawing functions **********/

/************* SPHERE **********/
// each points in the same direction as the vector from the origin to the corresponding vertex
void normalize(float vertex[3]) {    
   GLfloat d = sqrt(vertex[0]*vertex[0]+vertex[1]*vertex[1]+vertex[2]*vertex[2]); 
   if (d == 0.0) {   
      return;
   }
   vertex[0] /= d; 
   vertex[1] /= d; 
   vertex[2] /= d; 
}

void drawTriangle(float *v1, float *v2, float *v3) { 
	glBegin(GL_TRIANGLES);
		randomizeColors();
		glColor3fv(colors);

		glNormal3fv(v1); 
		glVertex3fv(v1);

		glNormal3fv(v2); 
		glVertex3fv(v2); 

		glNormal3fv(v3); 
		glVertex3fv(v3);    
	glEnd(); 
}

void divideTriangles(float *v1, float *v2, float *v3) 
{ 
   GLfloat v12[3], v23[3], v31[3];    
   GLint i;

   for (i = 0; i < 3; i++) { 
      v12[i] = v1[i]+v2[i]; 
      v23[i] = v2[i]+v3[i];     
      v31[i] = v3[i]+v1[i];    
   } 
   normalize(v12);    
   normalize(v23); 
   normalize(v31);

   drawTriangle(v1, v12, v31);    
   drawTriangle(v2, v23, v12);    
   drawTriangle(v3, v31, v23);    
   drawTriangle(v12, v23, v31); 
}

void drawSphere () {
	for (i = 0; i < 20; i++) { 
   		divideTriangles(&sphere_vertices[indx[i][0]][0],       
            &sphere_vertices[indx[i][1]][0],       
	        &sphere_vertices[indx[i][2]][0]); 
	}
}

/************* CUBES **********/

void drawFace (int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		randomizeColors();
		glColor3fv(colors);
		glVertex3fv(vertices[a]);

		randomizeColors();
		glColor3fv(colors);
		glVertex3fv(vertices[b]);

		randomizeColors();
		glColor3fv(colors);
		glVertex3fv(vertices[c]);

		randomizeColors();
		glColor3fv(colors);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorCube () {
	drawFace(1,2,3,0); //front
	drawFace(4,5,6,7); //back
	drawFace(1,2,5,4); //right
	drawFace(7,6,3,0); //left
	drawFace(5,2,3,6);  //top
	drawFace(1,4,7,0); //bottom
}

/************* Shapes Rendered **********/

void renderShapes(){

	//Right Top
	glPushMatrix();
		glTranslatef(1.5, 1.5, -4.0);
		chooseRotation();
		colorCube();
	glPopMatrix();

	//Left Top
	glPushMatrix();
		glTranslatef(-1.5, 1.5, -4.0);
		chooseRotation();
		colorCube();
	glPopMatrix();

	//Left Botton
	glPushMatrix();
		glTranslatef(-1.5, -1.5, -4.0);
		chooseRotation();
		colorCube();
	glPopMatrix();

	//Left Right
	glPushMatrix();
		glTranslatef(1.5, -1.5, -4.0);
		chooseRotation();
		colorCube();
	glPopMatrix();

	//Sphere
	glPushMatrix();
		glTranslatef(0.0+movSpherex, 0.0+movSpherey, -4.0);
		chooseRotation();
		glScalef(1.0+sphere_scale, 1.0+sphere_scale, 1.0+sphere_scale);
		drawSphere();
	glPopMatrix();
}


void display(){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
	renderShapes();
 
	glFlush();
	glutSwapBuffers();
 
}


/*************************************************/
/*********** User Interaction callbacks **********/

void mouse (int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		ROTATING_FLAG = ROTATING_FLAG + 1;
		if (ROTATING_FLAG > 2) {
			ROTATING_FLAG = 0;
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if (RANDOM_FLAG == 0)
			RANDOM_FLAG = 1;
		else 
			RANDOM_FLAG = 0;
	}

	glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y){
	if (key == 'Q' || key == 'q') {
		exit(0);		
	}
	if (key == 'A' || key == 'a') {
		if (SPIN_FLAG == 0)
			SPIN_FLAG = 1;
		else if (SPIN_FLAG == 1)
			SPIN_FLAG = 0;
	}
	if (key == 'S' || key == 's') {
		if (sphere_scale > -1.1)
			sphere_scale = sphere_scale	- 0.2;	
	}
	if (key == 'd'|| key == 'D') {
		sphere_scale = sphere_scale	+ 0.2;	
	}
}

void specialKey(int key, int x, int y) {

	float fraction = 1.0f;

	switch (key) {
		case GLUT_KEY_LEFT :
			movSpherex = movSpherex - 0.1;
			break;

		case GLUT_KEY_RIGHT :
			movSpherex = movSpherex + 0.1;
			break;

		case GLUT_KEY_UP :
			movSpherey = movSpherey + 0.1;;
			break;

		case GLUT_KEY_DOWN :
			movSpherey = movSpherey - 0.1;;

			break;
	}
}


/*************************************************/
/********* Initial State + Reshape func **********/

void init() {

	glClearColor (1.0, 1.0, 1.0, 1.0);
	//glClearColor (0.0, 0.0, 0.0, 1.0);
}

void reshape (int w, int h) {
	gluLookAt(0,0,8, 0,0,0, 0,1,0);
	GLdouble aspect = (GLdouble)w / (GLdouble)h;
	glMatrixMode   (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective(90.0, aspect, 0.1, 80.0);
	
	glMatrixMode   (GL_MODELVIEW);
	glViewport     (0, 0, w, h);
}


/*************************************************/
/***************** Main Function *****************/


int main(int argc, char** argv){

	srand (static_cast <unsigned> (time(0)));

	glutInit(&argc,argv);
 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cubes and Stuff");
 
	glEnable(GL_DEPTH_TEST);


  	// Callback functions
	glutReshapeFunc(reshape);

	glutDisplayFunc(display);

	glutIdleFunc(spinCube);

	glutMouseFunc(mouse);

	glutKeyboardFunc(keyboard);

	glutSpecialFunc(specialKey);
  	//

	init();

	glutMainLoop();
 
	return 0;
}