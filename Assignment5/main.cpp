/*
* CSCI 325 - Computer Graphics
* Aline Lais Gomes Tavares
* Jeremy Greenburg
* Assignment 5: Robot

 -----------------------------------------------------------------------
* Functions

  Mouse:
    - Left: Change scene
    - Right: quit

*/


#ifdef __APPLE__       // For use with OS X
#include <GLUT/glut.h>
#else       // Other (Linux)
#include <GL/glut.h>         
#endif

#include <cstdlib>
#include <ctime>

#include <bits/stdc++.h>

#include "Walker.h"

using namespace std;

bool showLego = true;

void drawNutcracker();
void drawlego();

void display();

void idle();

void mouse(int btn, int state, int x, int y);

void reshape(int w, int h);

int width = 700;
int height = 600;
static float theta = 0;

/*************************************************/

GLfloat membersTetha =  0.5, legoBodyTetha = 0.0;

float movCount = 0.0;
int leftMemberX = 1, rightMemberX= -1;
GLfloat colors[] = {1.0, 1.0, 1.0};

//Disco
#define X 0.53
#define Z 0.86

GLfloat disco_vertices[][3] = {    
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


float light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
float light_position[] = {0, 3, 0, 1.0};
float mat_specular[] = {0.5, 0.5, 0.5, 1.0};     
float mat_shininess[]= {5.0};

void init();

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  srand (static_cast <unsigned> (time(0)));
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Walker");


  init();
 
  glutMainLoop();

  return 0;
}

void init()
{
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHT2);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light_position);

  // Sky Blue
  glClearColor(135/255.0, 206/255.0, 250/255.0, 1);
}

void reshape(int w, int h)
{
  width = w;
  height = h;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLdouble aspect = (GLdouble)w / (GLdouble)h;

  gluPerspective(60, aspect, 1, 30);
  gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);

}

void drawNutcracker()
{
  glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(25, -1.5, 25);
    glVertex3f(25, -1.5, -25);
    glVertex3f(-25, -1.5, -25);
    glVertex3f(-25, -1.5, 15);
    glEnd();
    
    glRotatef(theta, 0, 1, 0);

    static Walker bob;
    bob.draw();
  glPopMatrix();
}

/*************************************************/
/*************************************************/

void randomizeColors (){
    float r, a = 1.0;
    for (int i = 0; i< 3; i++) {
      r = (float)rand()/(float)(RAND_MAX) * a;
      colors[i] = r;
    }
}

//disco
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

void Disco () {
  for (i = 0; i < 20; i++) { 
      divideTriangles(&disco_vertices[indx[i][0]][0],       
            &disco_vertices[indx[i][1]][0],       
          &disco_vertices[indx[i][2]][0]); 
  }
}

void drawDisco () {
  glPushMatrix();
    glTranslatef(-5.0, 5.0, 6.0);
    glScalef(1.0, 1.0, 1.0);
    Disco();
  glPopMatrix();
}

/****/

void legoMembersMovement() {

  if (movCount < 10){
    membersTetha = membersTetha + 0.5;
    movCount = movCount + 0.5;

  } else if (movCount >= 10 && movCount < 20) {
    movCount = movCount + 0.5;
    membersTetha = membersTetha - 0.5;

  } else if (movCount >= 20) {
    movCount = 0;

    //invert directions
    if (leftMemberX == 1) {
      leftMemberX = -1;
      rightMemberX = 1;
    } else {
      leftMemberX = 1;
      rightMemberX = -1;
    }
  }
}

void legoEyes (int position) {
  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.4*position, 3.0, 1.3);
  glScalef(1.0, 1.0, 1.0);
  glutSolidSphere(0.25, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(0.4*position, 3.0, 1.5);
  glScalef(1.0, 1.0, 1.0);
  glutSolidSphere(0.1, 20, 20);
  glPopMatrix();
}

void legoFace () {
  legoEyes(1);
  legoEyes(-1);

  //mouth
  glPushMatrix();
  glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.0, 2.4, 1.2);
  glScalef(2.0, 0.2, 1.0);
  glutSolidCube(0.3);
  glPopMatrix();
}

void legoHead () {
  //hair
  glPushMatrix();
  glColor3f(1.0, 0.8, 0.2);
  glTranslatef(0.0, 4.0, 0.0);
  glScalef(1.0, 0.4, 1.0);
  glutSolidCube(1.3);
  glPopMatrix();

  //legoHead
  glPushMatrix();
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef(0.0, 3.0, 0.0);
  glScalef(1.0, 1.5, 1.0);
  glRotatef(90, 1,0,0);
  glutSolidTorus(0.5, 0.9, 32, 32);
  glPopMatrix();

  //neck
  glPushMatrix();
  glColor3f(1.0, 0.8, 0.2);
  glTranslatef(0.0, 2.0, 0.0);
  glScalef(1.0, 0.3, 1.0);
  glutSolidCube(1.3);
  glPopMatrix();

  legoFace();
}

void legoTorso () {
  //legoTorso
  glPushMatrix();
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef(0.0, -0.24, 0.0);
  glScalef(1.0, 1.3, 1.0);
  glutSolidCube(3);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(0.0, -2.5, 0.0);
  glScalef(1.0, 0.2, 1.0);
  glutSolidCube(3);
  glPopMatrix();


}

void legoArms(int memberX, int position) {
  //upper arm
  glPushMatrix();
  glRotatef(membersTetha, memberX , 0.0, 0.0);
  glPushMatrix();
  glColor3f(0.8, 0.0, 0.0);
  glTranslatef(position*2.1, 1.0, 0.0);
  glScalef(1.0, 1.0, 1.0);
  glutSolidSphere(0.65, 20, 20);
  glPopMatrix();

  //lower arm
  glPushMatrix();
  glColor3f(0.8, 0.0, 0.0);
  glTranslatef(position*2.2, -0.6, 0.0);
  glScalef(1.0, 3.5, 1.0);
  glutSolidCube(0.7);
  glPopMatrix();

  //hands
  glPushMatrix();
  glColor3f(1.0, 1.0, 0.0);
  glTranslatef(position*2.2, -2.0, 0.0);
  glScalef(1.0, 1.0, 1.0);
  glRotatef(90, 1,0,0);
  glutSolidTorus(0.3, 0.5, 32, 32);
  glPopMatrix();
  glPopMatrix();

}

void legoLegs (int memberX, int position) {

  glPushMatrix();
  glRotatef(membersTetha, memberX , 0.0, 0.0);

  //left upper Leg
  glPushMatrix();
  glColor3f(0.2, 0.2, 0.8);
  glTranslatef(position*0.76, -3.1, 0.0);
  glScalef(1.0, 3.0, 1.0);
  glRotatef(90, 1,0,0);
  glutSolidTorus(0.3, 0.5, 32, 32);
  glPopMatrix();

  //left leg
  glPushMatrix();
  glColor3f(0.2, 0.2, 0.8);
  glTranslatef(position*0.9, -5.0, 0.0);
  glScalef(1.0, 3.0, 1.0);
  glutSolidCube(0.8);
  glPopMatrix();

  //left foot
  glPushMatrix();
  glColor3f(0.2, 0.2, 0.8);
  glTranslatef(position*0.9, -6.0, 0.8);
  glScalef(1.0, 0.5, 1.2);
  glutSolidCube(0.8);
  glPopMatrix();

  glPopMatrix();
}

void drawFloor () {
    glPushMatrix();
  glColor3fv(colors);
  randomizeColors();
  glTranslatef(-8.0, -6.9, -9.0);
  glScalef(100.0, 0.5, 100.0);
  glutSolidCube(0.8);
  glPopMatrix();
}

void drawLegoMan () {
  legoHead();
  legoTorso();
  legoArms(leftMemberX, 1);
  legoArms(rightMemberX, -1);
  legoLegs(rightMemberX, 1);
  legoLegs(leftMemberX, -1);

}


void drawLego()
{
  glPushMatrix();
    drawFloor();
    drawDisco();   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(legoBodyTetha, 0, -1, 0);
    glTranslatef(3.0, 0.0, 0.0);

   glScalef(0.4, 0.4, 0.4);
    drawLegoMan();
  glPopMatrix();

}
/*************************************************/


void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (showLego)
    drawLego();
  else
    drawNutcracker();

  glFlush();
  glutSwapBuffers();
}

void idle()
{
  if (showLego) {
      legoBodyTetha = legoBodyTetha + 0.5;
      legoMembersMovement();
      
      if (legoBodyTetha> 360) 
	 legoBodyTetha = 0.0;
  }

  else
    theta += 0.5;

  glutPostRedisplay();
}

void drawScene()
{
  glColor3f(.7, .7, .7);
  glBegin(GL_QUADS);
  glVertex3f(25, 0, 25);
  glVertex3f(25, 0, -25);
  glVertex3f(-25, 0, -25);
  glVertex3f(-25, 0, 25);
  glEnd();
}

void mouse(int btn, int state, int x, int y)
{
  if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
      showLego = !showLego;

      if (showLego)
	glDisable(GL_LIGHTING);

      else
	glEnable(GL_LIGHTING);
  }
  if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    exit(0);
  }
}
