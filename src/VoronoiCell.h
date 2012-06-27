#ifndef __VORONOICELL_H__
#define __VORONOICELL_H__

#include <iostream>
#include "Point.h"

class VoronoiCell
{
private:
  Point* top;
  float color[3];
public:
  VoronoiCell(float x, float y, float z)
  {
    top = new Point(x, y, z);
    memset(color, 0, sizeof(float) * 3);
  }

  VoronoiCell()
  {
    delete top;
    memset(color, 0, sizeof(float) * 3);
  }

  Point getTop()
  {
    return *top;
  }

  void setColor(float r, float g, float b)
  {
    color[0] = r;
    color[1] = g;
    color[2] = b;
  }

  void render()
  {
    glPushMatrix();
    glTranslatef((*top)[0], (*top)[1], (*top)[2] - 1);
    glColor3f(color[0], color[1], color[2]);
    glutSolidCone(1, 0.2, 48, 12);
    glPopMatrix();
    top->render();
  }

  inline friend std::ostream& operator <<(std::ostream& _stream, const VoronoiCell& rhs)
  {
    _stream << *rhs.top;
    _stream << " Color: " << rhs.color[0] << " " << rhs.color[1] << " " << rhs.color[2];
    return _stream;
  }
};

#endif /* __VORONOICELL_H__ */
