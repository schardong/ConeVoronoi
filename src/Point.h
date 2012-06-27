#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <GL/gl.h>
#include <cstring>

class Point
{
private:
  float x, y, z;
  float color[3];
public:
  Point(float _x = 0.f, float _y = 0.f, float _z = 0.f)
  {
    x = _x;
    y = _y;
    z = _z;
    memset(color, 0, sizeof(float) * 3);
  }

  ~Point()
  {
    x = y = z = 0.f;
  }

  void setColor(float r, float g, float b)
  {
    color[0] = r;
    color[1] = g;
    color[2] = b;
  }

  void render()
  {
    glBegin(GL_POINTS);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f((float) x, (float) y, (float) z);
    glEnd();
  }

  inline float operator[](int i)
  {
    switch(i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    }
    return 0.f;
  }

  inline friend std::ostream& operator <<(std::ostream& _stream, const Point& rhs)
  {
    _stream << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
    return _stream;
  }
};

#endif /* __POINT_HPP__ */
