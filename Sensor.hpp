#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include <vector>

namespace BioloSnake {

  class Sensor {

  public:
    virtual const std::vector<double>& sense() = 0;
    static int size() {return 0;}
  protected:
    std::vector<double> m_sensed;
  };

  class SimpleEye : Sensor {
    
  public:
    static int size() {return 15;}
    SimpleEye() {
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
      m_sensed.push_back(0.0);
    }
    
    const std::vector<double>& sense(const int (&map)[mapSizeY][mapSizeX], int direction, int x, int y) {
      switch (direction) {
      case 0:
	m_sensed[0] = getDanger(map, x+1, y+2);
	m_sensed[1] = getDanger(map, x+1, y+1);
	m_sensed[2] = getDanger(map, x+1, y);
	m_sensed[3] = getDanger(map, x+1, y-1);
	m_sensed[4] = getDanger(map, x+1, y-2);
	m_sensed[5] = getDanger(map, x+2, y+2);
	m_sensed[6] = getDanger(map, x+2, y+1);
	m_sensed[7] = getDanger(map, x+2, y);
	m_sensed[8] = getDanger(map, x+2, y-1);
	m_sensed[9] = getDanger(map, x+2, y-2);
	m_sensed[10] = getDanger(map, x+3, y+2);
	m_sensed[11] = getDanger(map, x+3, y+1);
	m_sensed[12] = getDanger(map, x+3, y);
	m_sensed[13] = getDanger(map, x+3, y-1);
	m_sensed[14] = getDanger(map, x+3, y-2);
	break;
      case 1:
	m_sensed[0] = getDanger(map, x+2, y+1);
	m_sensed[1] = getDanger(map, x+1, y+1);
	m_sensed[2] = getDanger(map, x, y+1);
	m_sensed[3] = getDanger(map, x-1, y+1);
	m_sensed[4] = getDanger(map, x-2, y+1);
	m_sensed[5] = getDanger(map, x+2, y+2);
	m_sensed[6] = getDanger(map, x+1, y+2);
	m_sensed[7] = getDanger(map, x, y+2);
	m_sensed[8] = getDanger(map, x-1, y+2);
	m_sensed[9] = getDanger(map, x-2, y+2);
	m_sensed[10] = getDanger(map, x+2, y+3);
	m_sensed[11] = getDanger(map, x+1, y+3);
	m_sensed[12] = getDanger(map, x, y+3);
	m_sensed[13] = getDanger(map, x-1, y+3);
	m_sensed[14] = getDanger(map, x-2, y+3);
	break;
      case 2:
	m_sensed[0] = getDanger(map, x-1, y+2);
	m_sensed[1] = getDanger(map, x-1, y+1);
	m_sensed[2] = getDanger(map, x-1, y);
	m_sensed[3] = getDanger(map, x-1, y-1);
	m_sensed[4] = getDanger(map, x-1, y-2);
	m_sensed[5] = getDanger(map, x-2, y+2);
	m_sensed[6] = getDanger(map, x-2, y+1);
	m_sensed[7] = getDanger(map, x-2, y);
	m_sensed[8] = getDanger(map, x-2, y-1);
	m_sensed[9] = getDanger(map, x-2, y-2);
	m_sensed[10] = getDanger(map, x-3, y+2);
	m_sensed[11] = getDanger(map, x-3, y+1);
	m_sensed[12] = getDanger(map, x-3, y);
	m_sensed[13] = getDanger(map, x-3, y-1);
	m_sensed[14] = getDanger(map, x-3, y-2);
	break;
      case 3:
	m_sensed[0] = getDanger(map, x+2, y-1);
	m_sensed[1] = getDanger(map, x+1, y-1);
	m_sensed[2] = getDanger(map, x, y-1);
	m_sensed[3] = getDanger(map, x-1, y-1);
	m_sensed[4] = getDanger(map, x-2, y-1);
	m_sensed[5] = getDanger(map, x+2, y-2);
	m_sensed[6] = getDanger(map, x+1, y-2);
	m_sensed[7] = getDanger(map, x, y-2);
	m_sensed[8] = getDanger(map, x-1, y-2);
	m_sensed[9] = getDanger(map, x-2, y-2);
	m_sensed[10] = getDanger(map, x+2, y-3);
	m_sensed[11] = getDanger(map, x+1, y-3);
	m_sensed[12] = getDanger(map, x, y-3);
	m_sensed[13] = getDanger(map, x-1, y-3);
	m_sensed[14] = getDanger(map, x-2, y-3);
	break;
      }
      return m_sensed;
    }
  private:
    const std::vector<double>& sense() {}

    double getDanger(const int (&map)[mapSizeY][mapSizeX], int x, int y) {
      //x = x >= mapSizeX ? 0 : x < 0 ? mapSizeX-1 : x;
      //y = y >= mapSizeY ? 0 : y < 0 ? mapSizeY-1 : y;
      if (x >= mapSizeX || x < 0 || y >= mapSizeY || y < 0) return -1.0;
      else if (map[y][x]=='#') return -1.0;
      else if (map[y][x]=='.') return 1.0;
      else return 0.0;
    }
  };
};

#endif /* !SENSOR_HPP_ */
