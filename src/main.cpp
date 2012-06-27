#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <ctime>

#include "common.h"
#include "VoronoiDiagram.h"

static const int NUM_POINTS = 5;

void cleanup();
//OpenGL functions.
void initGL(int w, int h);
void cbRender();
void cbReshape(int w, int h);
void cbKeyDown(unsigned char key, int x, int y);
void cbKeyUp(unsigned char key, int x, int y);
void cbSpecialKeyDown(int key, int x, int y);
void cbSpecialKeyUp(int key, int x, int y);
void cbMouseAction(int button, int state, int x, int y);
void cbMouseMove(int x, int y);

VoronoiDiagram* vorDiag;

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  initGL(WIDTH, HEIGHT);

  vorDiag = new VoronoiDiagram(NUM_POINTS);

  glutMainLoop();
  return 0;
}

void initGL(int w, int h)
{
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Voronoi");

  glutKeyboardFunc(cbKeyDown);
  glutKeyboardUpFunc(cbKeyUp);
  glutSpecialFunc(cbSpecialKeyDown);
  glutSpecialUpFunc(cbSpecialKeyUp);
  glutMouseFunc(cbMouseAction);
  glutMotionFunc(cbMouseMove);
  glutPassiveMotionFunc(cbMouseMove);
  glutReshapeFunc(cbReshape);
  glutDisplayFunc(cbRender);
  glutIdleFunc(cbRender);

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPointSize(POINT_SIZE);

  glEnable(GL_DEPTH_TEST);
}

void cbRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  vorDiag->render();

  glutSwapBuffers();
  glutPostRedisplay();
}

void cbReshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, 0, 5);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
}

void cbKeyDown(unsigned char key, int x, int y)
{
  switch(key) {
  case 27:
    cleanup();
    exit(0);
    break;
  default:
    std::cout << "Key: " << key << std::endl;
    break;
  }
}

void cbKeyUp(unsigned char key, int x, int y)
{
}

void cbSpecialKeyDown(int key, int x, int y)
{
}

void cbSpecialKeyUp(int key, int x, int y)
{
}

void cbMouseAction(int button, int state, int x, int y)
{
  std::cout << button << " " << state << " (" << x << ", " << y << ")" << std::endl;
  y = HEIGHT - y;
  switch(button) {
  case 0:
    if(state == 1) {
      if(vorDiag->collisionTest((float) x / WIDTH, (float) y / HEIGHT) == -1)
	vorDiag->addPoint((float) x / WIDTH, (float) y / HEIGHT);
    }
    break;
  case 2:
    if(state == 1)
      vorDiag->removePoint(vorDiag->collisionTest((float) x / WIDTH, (float) y / HEIGHT));
    break;
  }
}

void cbMouseMove(int x, int y)
{
}

void cleanup()
{
  delete vorDiag;
}
