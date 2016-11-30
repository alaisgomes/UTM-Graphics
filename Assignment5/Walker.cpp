#include "Walker.h"

using namespace std;

Walker::Walker()
{
  theta = 0;
  legTheta = 0;
  legDir = 1;
}

void Walker::draw()
{
  glPushMatrix();
  glTranslatef(3, 0, 0.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
  drawBody();
  drawHead();
  drawArms();
  drawLegs();
  glPopMatrix();

  update();
}

void Walker::drawBody()
{
  glPushMatrix();
  glTranslatef(0, .20, 0);
  glColor3f(1, 0, 0);
  glScalef(1, 1.5, 1);
  glutSolidCube(1);
  glPopMatrix();
}

void Walker::drawHead()
{
  static GLUquadric* quad = gluNewQuadric();
  
  glPushMatrix();
  // Peach Puff
  glColor3f(255/255.0, 218/255.0, 185/255.0);
  glTranslatef(0, 1.5, 0);
  glutSolidSphere(.5, 50, 50);

  glPushMatrix();
  // Eyes  
  glRotatef(90, 0, 1, 0);
  glTranslatef(.5, 0, .1);
  glColor3f(0, 0, 1);
  glutSolidSphere(.1, 50, 50);
  glTranslatef(0, 0, -.2);
  glutSolidSphere(.1, 50, 50);
  glPopMatrix();

  // Beard
  glColor3f(1, 1, 1);
  glPushMatrix();
  glTranslatef(0, -.3, -.2);
  glPushMatrix();
  glRotatef(120, 1, 0, 0);
  gluCylinder(quad, .3, 0, 1, 50, 50);
  glPopMatrix();

  // Inner beard
  glColor3f(.2, .2, .2);
  glTranslatef(0, -.5, -.3);
  glRotatef(120, 1, 0, 0);
  gluCylinder(quad, .1, 0, .5, 50, 50);

  glPopMatrix();

  // Hat
  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(0, 1, .6);
  glRotatef(120, 1, 0, 0);
  gluCylinder(quad, .5, .5, 1, 50, 50);
  glPopMatrix();

  // Hat thingy
  glPushMatrix();
  // Goldenrod
  glColor3f(218/255.0, 165/255.0, 32/255.0);
  glTranslatef(0, .2, .1);
  glRotatef(120, 1, 0, 0);
  gluCylinder(quad, .53, .53, .2, 50, 50);
  glPopMatrix();

  glPopMatrix();
}

void Walker::drawArms()
{
  glColor3f(.7, 0, 0);

  glPushMatrix();

  glTranslatef(.5, 0, 0);
  glScalef(.5, 1, .1);

  // RIGHT STUFF
  glPushMatrix();
  glRotatef(-legTheta, 1, 0, 0);
  glutSolidCube(1);
  glPopMatrix();

  glTranslatef(-2, 0, 0);

  // LEFT STUFF
  glPushMatrix();
  glRotatef(legTheta, 1, 0, 0);
  glutSolidCube(1);
  glPopMatrix();

  glPopMatrix();

}

void Walker::drawLegs()
{
  glColor3f(1, 1, 1);
  glPushMatrix();

  glTranslatef(0, 0, 0);

  // LEFT STUFF
  glPushMatrix();

  glScalef(.3, 1.5, .3);

  glTranslatef(.5, -.5, 0);

  glPushMatrix();
  glRotatef(legTheta, 1, 0, 0);
  glutSolidCube(1);
  glPopMatrix();

  glTranslatef(-1, 0 , 0);

  glPushMatrix();
  glRotatef(-legTheta, 1, 0, 0);
  glutSolidCube(1);
  glPopMatrix();

  glPopMatrix();


  glPopMatrix();  
}

void Walker::update()
{
  theta += .01;
  legTheta += legDir;

  if (legTheta > 40 || legTheta < -40)
    legDir *= -1;
  if (theta > 360)
    theta -= 360.0;
}
