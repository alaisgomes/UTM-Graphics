#ifdef __APPLE__       // For use with OS X
#include <GLUT/glut.h>
#else       // Other (Linux)
#include <GL/glut.h>         
#endif

#ifndef WALKER_H
#define WALKER_H

class Walker
{
private:
  float theta, legTheta;
  float legDir;
  void update();

  void drawBody();
  void drawHead();
  void drawLegs();
  void drawArms();

public:
 Walker();
 void draw();
};
#endif
