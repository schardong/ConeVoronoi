#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "common.h"
#include "VoronoiDiagram.h"

static const int NUM_POINTS = 5;

//OpenGL callbacks.
void initGL(int w, int h);
void cbRender();
void cbReshape(int w, int h);
void cbKeyDown(unsigned char key, int x, int y);
void cbMouseAction(int button, int state, int x, int y);

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
  glutCreateWindow("Cone Voronoi Diagram");

  glutKeyboardFunc(cbKeyDown);
  glutMouseFunc(cbMouseAction);
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
  WIDTH = w;
  HEIGHT = h;

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
    delete vorDiag;
    exit(0);
    break;
  case 32:
    vorDiag->setShowTop(!vorDiag->getShowTop());
    break;
  default:
    std::cout << "Key: " << key << std::endl;
    break;
  }
}

void cbMouseAction(int button, int state, int x, int y)
{
  y = HEIGHT - y;
  
  switch(button) {
  case GLUT_LEFT_BUTTON:
    if(state == GLUT_DOWN)
      if(vorDiag->collisionTest((float) x / WIDTH, (float) y / HEIGHT) == -1) {
	vorDiag->addPoint((float) x / WIDTH, (float) y / HEIGHT);
	vorDiag->setShowTop(vorDiag->getShowTop());
      }
    break;
  case GLUT_RIGHT_BUTTON:
    if(state == GLUT_DOWN)
      vorDiag->removePoint(vorDiag->collisionTest((float) x / WIDTH, (float) y / HEIGHT));
    break;
  }
}
