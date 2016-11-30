/*
* Assignment 1: Old GLory 
* Student Name: Aline Lais Gomes Tavares
*compile: make
*execute: ./oldglory
*/

#include <iostream>
 #include <cmath>
#ifdef __APPLE__      
#include <GLUT/glut.h>
#else		       
#include <GL/glut.h>         
#endif

#ifndef FACTOR
 #define FACTOR 1
 #endif

GLfloat L;

/*drawing a star based on an outer and inner circle by finding points in them through sin/cossin 
* and using a fan of triangles 
* X and Y are given as reference the center points of circles*/
void star(float  X, float  Y) {
  const float pi = 3.141592653589793238462;
  const float radius = (L * 4.0/5.0)/2.0; //Diameter of star: K = (L × 4/5)
  const float  innerRadius =  radius*(1.0/(sin((2.0* pi)/5.0)*2.0*cos( pi/10.0) + sin((3.0* pi)/10.0)));


  glColor3f(1.0, 1.0, 1.0);

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f( X, Y);
    for (int vIndex = 0; vIndex < 10; ++vIndex) {
      float aStart =  pi/2.0 + (vIndex*2.0* pi)/10.0;
      float aEnd   = aStart +  pi/5.0;

      if (vIndex % 2 == 0) {
        glVertex2f( X +  radius*cos(aStart)/0.95,  Y +  radius*sin(aStart));
        glVertex2f( X +  innerRadius*cos(aEnd)/0.95,  Y +  innerRadius*sin(aEnd));
      } else {
        glVertex2f( X +  innerRadius*cos(aStart)/0.95,  Y +  innerRadius*sin(aStart));
        glVertex2f( X +  radius*cos(aEnd)/0.95,  Y +  radius*sin(aEnd));
      }
    }
  glEnd();
}



void display(void) {
  /* Reference value proportions */
  const GLfloat X = FACTOR * 0.95;
  const GLfloat Y = FACTOR * 0.5;

  int i, j;
  GLfloat Y1, Y2, X1;

  /* clear buffer */
  glClear(GL_COLOR_BUFFER_BIT); 
  

  /***********
  **Big External White Area
  ***********/

  glColor3f(1.0, 1.0, 1.0);

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
    glVertex2f(-X, -Y);
    glVertex2f(-X, Y);
    glVertex2f(X, Y);
    glVertex2f(X, -Y);
  glEnd();

  /***********
  **Red Stripes
  ***********/

  L = (float) Y*2/13;

    Y2 = Y;
    for (i = 1; i<14 ; i++) {
    Y1 = Y2 - L;
    /* it will skip the ones that are supposed to be white */
    if ((i % 2) != 0){

      glColor3f(0.698, 0.132, 0.203);
      glBegin(GL_POLYGON);
        //All Xs are the same because the width remain the same, only height changing, adjusted by Y
        glVertex2f(-X, -Y2);
        glVertex2f(-X, -Y1);
        glVertex2f(X, -Y1);
        glVertex2f(X, -Y2);
      glEnd();
    }
    Y2 = Y1; /*Update reference values*/

  }

  /***********
  **Blue Area 
  ***********/
  Y1 = Y * 2 * (float)(7/13); //C
  X1 = X * 2 * (float)(2/5); //D

  glColor3f(0.234, 0.233, 0.430);
      glBegin(GL_POLYGON);
        glVertex2f(-X, Y1); //bottom left, adjust height with new Y
        glVertex2f(-X, Y);  // same vertex as original on top left
        glVertex2f(-X1, Y); // top right, ajust width with new X
        glVertex2f(-X1, Y1); // bottom right, both new values
      glEnd();


  /***********
  **Stars
  ***********/

  glColor3f(1.0,1.0,1.0);
  X1= 0;
  Y1 = 0;

  GLfloat G = X/12.0;
  GLfloat E = Y/10.0;

  for (i = 0; i < 9; ++i) {
    Y1 = ((i + 1)*(E)); //Y base position for the stars, just changed when changing column

    // 2 Different loops for each kind of row (alternating between 5 and 6 stars)
    if (i % 2 == 0) {
      for (j = 1; j < 7; ++j) {
        star(-((j - 0.5) * (X/6.0)) , Y1); 
      }
    } else {
      for (j = 1; j < 6; ++j) {
        star(-(j + 0.5)*(X/6.0) + G, Y1);
      }
    }
  }

  
  glFlush(); 

}


void init() {

  /* set clear color to black */
  glClearColor (0.0, 0.0, 0.0, 0.0);
  
}



int main(int argc, char** argv) {
  int window_x, window_y;

  window_x = 800 * FACTOR;
  window_y = 800 * FACTOR;

  /* Window title is name of program (arg[0]) */
  glutInit(&argc,argv); 
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  //Window Size
  glutInitWindowSize(window_x, window_y);

  //Window Position (upper left corner of the screen).
  glutInitWindowPosition(0,0); 

  //Create a window with title parameter
  glutCreateWindow("Old Glory");

  //Pass our display function to GLUT void display(void);
  glutDisplayFunc(display);

  //Our initialization function
  init();

  //Entger the GLUT event processing loop.
  glutMainLoop();

}
