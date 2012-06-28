#ifndef __VORONOIDIAGRAM_H__
#define __VORONOIDIAGRAM_H__

#include <vector>
#include <ctime>
#include "VoronoiCell.h"
#include "common.h"

class VoronoiDiagram
{
private:
  std::vector<VoronoiCell*> m_vCells;
public:
  VoronoiDiagram(int numCells)
  {
    srand(time(NULL));
    for(int i = 0; i < numCells; i++) {
      m_vCells.push_back(new VoronoiCell((float) rand() / (RAND_MAX - 1), (float) rand() / (RAND_MAX - 1), -1));
      m_vCells[i]->setColor((float) rand() / (RAND_MAX - 1), (float) rand() / (RAND_MAX - 1), (float) rand() / (RAND_MAX - 1));
    }
  }

  ~VoronoiDiagram()
  {
    for(auto it = m_vCells.begin(); it != m_vCells.end(); it++)
      delete *it;
    m_vCells.clear();
  }

  bool getShowTop()
  {
    return m_vCells[0]->getShowTop();
  }

  void setShowTop(bool show)
  {
    for(auto it = m_vCells.begin(); it != m_vCells.end(); it++)
      (*it)->setShowTop(show);
  }

  int collisionTest(float x, float y)
  {
    for(unsigned int i = 0; i < m_vCells.size(); i++) {
      Point pt = m_vCells[i]->getTop();
      float sz_x = (float) POINT_SIZE / WIDTH;
      float sz_y = (float) POINT_SIZE / HEIGHT;

      if(x >= pt[0] - sz_x && x <= pt[0] + sz_x && y >= pt[1] - sz_y && y <= pt[1] + sz_y)
	return i;

    }
    return -1;
  }

  void addPoint(float x, float y)
  {
    VoronoiCell* tmp = new VoronoiCell(x, y, -1);
    tmp->setColor((float) rand() / (RAND_MAX - 1), (float) rand() / (RAND_MAX - 1), (float) rand() / (RAND_MAX - 1));
    m_vCells.push_back(tmp);
  }

  void removePoint(int i)
  {
    unsigned int idx = (unsigned int) i;
    if(i < 0 || idx >= m_vCells.size())
      return;
    m_vCells.erase(m_vCells.begin() + idx);
  }

  void render()
  {
    for(auto it = m_vCells.begin(); it != m_vCells.end(); it++)
      (*it)->render();
  }
};

#endif /* __VORONOIDIAGRAM_H__ */
