/*
* CSCI 325 - Computer Graphics
* Aline Lais Gomes Tavares
* Assignment 6: Room
*/

#include <cstdlib>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else          
#include <GL/glut.h>         
#endif


int WIDTH = 800, HEIGHT = 700; 

float tethaFan = 0;

float lx= 0.2f,ly = 0.5f, lz= 0.2f;

float lookx=-2.0,looky=1.5, lookz=10; //2.4, 0, 0

GLUquadric* qobj;

GLfloat color[][3] = {{0.4, 0.2, 0.0}, {0.8, 0.2, 0.2}, {0.2, 0.8, 0.2}, {1.0, 0.8, 0.2}};



/*************************************************/
/******** Functions to help control states *******/

void computePos(int option) {
	if (option == 1) {
		lookz = lookz - lz;
	} else if (option == 2) {
		lookz = lookz + lz;
	} else if (option == 3) {
		lookx = lookx + lx;
	} else if (option == 4) {
		lookx = lookx - lx;
	} else if (option == 5) {
		looky = looky + ly;
	} else if (option == 6) {
		looky = looky - ly;
	}
	printf ("%.2f, %.2f, %.2f\n", lookx,looky, lookz);
}

/*************************************************/
/****************** Render Scene *****************/

void drawWalls () {
	//right
    glPushMatrix();
    	glColor3f(1.0, 1.0, 1.0);
    	glTranslatef(30,-5,0);
    	glRotatef(90, 0,0,1);
	    glScalef(20.0, 0.5, 30.0);
	    glutSolidCube(1.0);
    glPopMatrix();
    //left
    glPushMatrix();
    	glColor3f(1.0, 1.0, 1.0);
    	glTranslatef(-30,-5,0);
    	glRotatef(-90, 0,0,1);
	    glScalef(20.0, 0.5, 30.0);
	    glutSolidCube(1.0);
    glPopMatrix();

    //behind
    glPushMatrix();
    	glColor3f(1.0, 1.0, 1.0);
    	glTranslatef(0,-5,-15);
    	glRotatef(90, 1,0,0);
	    glScalef(60.0, 0.5, 20.0);
	    glutSolidCube(1.0);
    glPopMatrix();

        //front
    glPushMatrix();
    	glColor3f(1.0, 1.0, 1.0);
    	glTranslatef(0,-5,15);
    	glRotatef(90, 1,0,0);
	    glScalef(60.0, 0.5, 20.0);
	    glutSolidCube(1.0);
    glPopMatrix();

}
void drawBottomTop() {
	//floor
    glPushMatrix();
    	glColor3f(0.4, 0.8, 1.0);
    	glTranslatef(0,-15,0);
	    glScalef(60.0, 0.5, 30.0);
	    glutSolidCube(1.0);
    glPopMatrix();
    //ceiling
    glPushMatrix();
    	glColor3f(0.2, 0.2, 0.4);
    	glTranslatef(0, 5,0);
	    glScalef(60.0, 0.5, 30.0);
	    glutSolidCube(1.0);
    glPopMatrix();
}

void drawBlades (int rotate) {
	glPushMatrix();
	glRotatef(rotate, 0,1,0);
    	glColor3f(0.6, 0.8, 1.0);
	    glScalef(6.0, 0.08, 1);
	    glutSolidCube(1.0);
    glPopMatrix();
}
void drawFan () {
	glPushMatrix();
		glTranslatef(0.0, 4, 2);
		glRotatef(tethaFan, 0,1,0);

		glPushMatrix();
			glColor3f(0.6, 0.8, 1.0);
			glScalef(1.0, 3.0, 1.0);
			glRotatef(90, 1,0,0);
			glutSolidTorus(0.3, 0.4, 32, 32);
		glPopMatrix();

		drawBlades(0);
		drawBlades(45);
		drawBlades(-45);

	glPopMatrix();
}




void drawLamp () {
	glPushMatrix();
		glTranslatef(1,0,-3);
		glColor3f(1.0, 0.8, 0.6);
		glTranslatef (0,5,0);
		//lamp cover
		glPushMatrix();
			//glScalef(0.1, 5, 0.1);
			glRotatef(-90, 1,0,0);
			glRotatef(45, 0,1,0);
			glutSolidCone(1, 3, 50, 50);
		glPopMatrix();

		//lamp
		glPushMatrix();
			glTranslatef (0,0,0);
			glScalef(1,1,1);
			glutSolidSphere(0.5, 30,30);
		glPopMatrix();

		//detail
		glPushMatrix();
			glTranslatef (1.8,1.8, -0.1);
			glScalef(0.5, 0.5, 0.5);
			glRotatef(-90, 1,0,0);
			glRotatef(45, 0,1,0);
			glutSolidTorus(0.3, 0.4, 32, 32);
		glPopMatrix();

		//leg
		glPushMatrix();
			glTranslatef (2,-2,0);
			glScalef(0.2, 7.5, 0.2);
			glutSolidCube(1);
		glPopMatrix();

		//base
		glPushMatrix();
			glTranslatef (2,-4.5,0);
			glScalef(1,0.5,1);
			glRotatef(-90, 1,0,0);
			glutSolidTorus(0.3, 0.4, 32, 32);
		glPopMatrix();


    glPopMatrix();
}

void monitor () {
	glPushMatrix();
	glTranslatef(-2,2.5,2);
	glRotatef(-90, 0,1,0);
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glScalef(4.4,3,0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,0.05);
		glColor3f(0.3, 0.3, 0.3);
		glScalef(4.0,2.6,0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,-1.5,-0.1);
		glColor3f(0.1, 0.1, 0.1);
		glScalef(0.2, 1.2, 0.2);
		glRotatef(90, 1,0,0);
		glutSolidTorus(0.5, 0.3, 32, 32);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,-2,-0.1);
		glColor3f(0.1, 0.1, 0.1);
		glScalef(0.5, 0.3, 0.5);
		glRotatef(90, 1,0,0);
		glutSolidTorus(0.5, 0.3, 32, 32);
	glPopMatrix();
	glPopMatrix();
}

void legs(float x, float z, float size){
	glPushMatrix();
		glTranslatef (x, -2.5, z);
		glColor3f(0.6, 0.4, 0.4);
		glScalef(0.2, size, 0.2);
		glutSolidCube(1.0);
    glPopMatrix();
}

void drawTable () {
	glPushMatrix();
		glTranslatef(15, -10, 0);
		//something on the table
		drawLamp();
		monitor();

		//table
		glPushMatrix();
			glColor3f(0.6, 0.4, 0.4);
			glScalef(10.0, 0.5, 10);
	    	glutSolidCube(1.0);
    	glPopMatrix();

    	legs(5, 5, 5);
    	legs(-5, 5, 5);
    	legs(5, -5, 5);
    	legs(-5, -5, 5);

	glPopMatrix();
}

void drawChair (float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, 0,1,0);
	//seat
	glPushMatrix();
		glTranslatef(0,-4,2.5);
		glColor3f(0.4, 0.2, 0.2);
		glScalef(5, 0.8, 5);
		glutSolidCube(1.0);
	glPopMatrix();
	// back
	glPushMatrix();
		glTranslatef(0,-1,0);
		glColor3f(0.4, 0.2, 0.2);
		glScalef(5, 3.5, 0.8);
		glutSolidCube(1.0);
	glPopMatrix();
	//connections
	glPushMatrix();
		glTranslatef(-1,-3.5,0);
		glColor3f(0.6, 0.4, 0.4);
		glScalef(0.5, 2, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1,-3.5,0);
		glColor3f(0.6, 0.4, 0.4);
		glScalef(0.5, 2, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	//legs
	glPushMatrix();
		glTranslatef(0, -3, 2.5);
	    legs(2.5, 2.5, 3.5);
	    legs(-2.5, 2.5, 3.5);
	    legs(2.5, -2.5, 3.5);
	    legs(-2.5, -2.5, 3.5);
	glPopMatrix();

    glPopMatrix();
}

void shelfs(int height) {
	glPushMatrix();
		glTranslatef(0,height,0.8);
		glColor3f(0.8, 0.2, 0.4);
		glScalef(8, 0.1, 2);
		glutSolidCube(1.0);
	glPopMatrix();
}

void holdings (float x, float y, int angle) {
	glPushMatrix();
		glTranslatef(x, y, 0.8);
		glRotatef(-angle, 1, 0, 0);
		glColor3f(0.8, 0.2, 0.4);
		glScalef(0.05, 2.5, 0.05);
		glutSolidCube(1.0);
	glPopMatrix();
}

void drawBook (float x, float y, float z, GLfloat color[]) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, 0,1,0);
		glPushMatrix();
	
			glColor3fv(color);
			glScalef(0.1, 1.5, 0.17);
			glRotatef(90, 1,0,0);
			glutSolidTorus(0.5, 0.3, 32, 32);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.5, 0,0);
			glColor3fv(color);
			glScalef(1, 1.5, 0.2);
			//glRotatef(90, 1,0,0);
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.5, 0.73,0);
			glColor3f(1.0, 1.0, 1.0);
			glScalef(0.9, 0.05, 0.1);
			//glRotatef(90, 1,0,0);
			glutSolidCube(1.0);
		glPopMatrix();

	glPopMatrix();
}
void books () {
	drawBook (0, 0.8, 2, color[0]);
	drawBook (-2, 0.8, 2, color[1]);
	drawBook (-1.5, 0.8, 2, color[2]);
	drawBook (-2.3, 0.8, 2, color[3]);
}
void drawShelf() {
	//wall hoding
	glPushMatrix();
		glTranslatef(-3,-6, -10);
		books();
		glPushMatrix();
			glTranslatef(-4,1,0);
			glColor3f(0.8, 0.2, 0.4);
			glScalef(0.3,6 , 0.15);
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(4,1,0);
			glColor3f(0.8, 0.2, 0.4);
			glScalef(0.3, 6, 0.15);
			glutSolidCube(1.0);
		glPopMatrix();
		holdings (4, 3, 40);
		holdings (4, 0.8, 40);
		holdings (4, -1, 40);
		holdings (-4, 3, 40);
		holdings (-4, 0.8, 40);
		holdings (-4, -1, 40);
		//shelfs
		shelfs(2);
		shelfs(0);
		shelfs(-2);

	glPopMatrix();
}

void drawSwitch() {
	glPushMatrix();
	glTranslatef(9,-5,-10);
	glPushMatrix();
		glColor3f(0.6, 0.8, 1.0);
		glScalef(0.8, 1.3, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,0.1);
		glColor3f(0.4, 0.6, 1.0);
		glScalef(0.2, 0.2, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0.2,0.1);
		glColor3f(0.8, 1.0, 1.0);
		glScalef(0.2, 0.2, 0.1);
		glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
}

void drawDoor () {
	glPushMatrix();
		glTranslatef(0,-10,15);
		glPushMatrix();
			glColor3f(0.4, 0.2, 0.2);
			glScalef(6, 12, 1);
			glutSolidCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2, 0, 0.2);
			glColor3f(0.4, 0.0, 0.0);
			glScalef(0.5, 0.5, 0.5);
			glutSolidSphere(1.0, 30,30);
		glPopMatrix();
	glPopMatrix();
}


void background () {
	glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(90, -15, 90);
    glVertex3f(90, -15, -90);
    glVertex3f(-90, -15, -90);
    glVertex3f(-90, -15, 90);
    glEnd();

    //sun
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(25, 25, -10);
    glutSolidSphere(6, 30,30);
    glPopMatrix();
}

void drawBed() {
	glPushMatrix();
		glTranslatef(-20, -13, -3);
		glRotatef(-90, 0,1,0);
		//head
		glPushMatrix();
			glTranslatef(-6.5,2,0);
			glColor3f(0.6, 0.6, 1.0);
			glScalef(1, 7.5, 9.5);
			glutSolidCube(1.0);
		glPopMatrix();

		 //mattress
		glPushMatrix();
			glTranslatef(0,2,0);
			glColor3f(1.0, 1.0, 1.0);
			glScalef(13, 1, 9);
			glutSolidCube(1.0);
		glPopMatrix();

		//bed
		glPushMatrix();
			glColor3f(0.6, 0.6, 1.0);
			glScalef(13, 4, 9);
			glutSolidCube(1.0);
		glPopMatrix();


	glPopMatrix();
}

/*************************************************/
/*************** DISPLAY FUNCTION ****************/


void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat light_Intensity[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat light_Position[]={-1.0, 1.0, -1.0,1.0f};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_ambient[]={0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,light_Position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Intensity);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);

    GLfloat mat_ambient[]={0.5, 0.5, 0.5,1.0f};
    GLfloat mat_diffuse[]={0.1f,0.1f,0.1f,1.0f};
    GLfloat mat_specular[]={0.1, 0.1, 0.1 ,1.0f};
    GLfloat mat_shininess[]={5.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    gluLookAt(lookx, looky, lookz,  0.0f, 0.0f, 0.0f,   0.0f, 1.0f,  0.0f);


    glPushMatrix();
    	drawSwitch();
    	drawShelf();
    	drawBed();
    	drawChair(4, -8, 0);
   		drawTable();
    	drawFan();
    	drawDoor();
    	drawBottomTop();
    	drawWalls();
    	background();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}

/*************************************************/
/***************** Callbacks *****************/

void specialKey(int key, int xx, int yy) {

       switch (key) {
             case GLUT_KEY_UP :  
             	computePos(1);
             	break;
             case GLUT_KEY_DOWN : 
             	computePos(2); 
             	break;
             case GLUT_KEY_RIGHT: 
             	computePos(3);
             	break;
             case GLUT_KEY_LEFT: 
            	 computePos(4);
             	break;

       }
       glutPostRedisplay();
} 

void mouse (int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		exit(0);
	}
}

void keyboard (unsigned char key, int x, int y) {
	if (key == 's' || key == 'S') {  
        computePos(5);
    } else if (key == 'a' || key == 'A') {
		computePos(6);
    }

	if (key == 'e' || key == 'E') {  
        glDisable(GL_LIGHTING);
    	glDisable(GL_LIGHT0);
    }
    if (key == 'r' || key == 'R') {  
        glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
    }
    if (key == 'q' || key == 'Q') {  
    	exit(0);
    }
    if (key == 'o' || key == 'O') {  
     lookx = 0.0;
     looky = 0.0;
     lookz = 44.0;
    }

    if (key == 'i' || key == 'I') {  
    	lookx = -2.4;
     	looky = 1.0;
     	lookz = 10.0;
    }
    glutPostRedisplay();
}

void idle (){
	tethaFan = tethaFan + 2.0;

	if (tethaFan> 360) 
		tethaFan = 0.0;

	glutPostRedisplay();
}


/*************************************************/
/********* Initial State + Reshape func **********/

void reshape (int w, int h) {
	GLdouble aspect = (GLdouble)w / (GLdouble)h;
	glMatrixMode   (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90.0, aspect, 1.0, 50.0);
	
	glMatrixMode   (GL_MODELVIEW);
	glViewport     (0, 0, w, h);
}

void init() {
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glClearColor (0.4, 0.8, 1.0, 1.0);

}

/*************************************************/
/***************** Main Function *****************/

int main(int argc, char** argv){


	glutInit(&argc,argv);
 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Room");


  	// Callback functions
	glutReshapeFunc(reshape);

	glutDisplayFunc(display);


	glutMouseFunc(mouse);
	glutSpecialFunc(specialKey);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
  	//

	init();

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
 
	return 0;
}