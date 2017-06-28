#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include <list>
#include <vector>

#include "Snake.hpp"

struct Food {
  Food(int x, int y) {this->x = x; this->y = y; eaten = false;};
  int x;
  int y;
  bool eaten;
};

namespace BioloSnake {

  class SensorHub;
  
  class Sensor {

  public:
    Sensor(int size, std::vector<double>& inputsHub)
      :
      m_sensed(inputsHub),
      m_start_index(inputsHub.size()),
      m_end_index(inputsHub.size() + size)
    {
      for (int i = m_start_index; i < m_end_index; ++i) inputsHub.push_back(0.0);
    }
    void sense() {};
  protected:
    std::vector<double>& m_sensed;
    const int m_start_index;
    const int m_end_index;
  };
  
  class SimpleEye : public Sensor {
    
  public:
    SimpleEye(std::vector<double>& inputsHub) : Sensor(15, inputsHub) {
    }
    
    void sense(const int (&map)[mapSizeY][mapSizeX], int direction, int x, int y) {
      switch (direction) {
      case 0:
	m_sensed[m_start_index+0] = getDanger(map, x+1, y+2);
	m_sensed[m_start_index+1] = getDanger(map, x+1, y+1);
	m_sensed[m_start_index+2] = getDanger(map, x+1, y);
	m_sensed[m_start_index+3] = getDanger(map, x+1, y-1);
	m_sensed[m_start_index+4] = getDanger(map, x+1, y-2);
	m_sensed[m_start_index+5] = getDanger(map, x+2, y+2);
	m_sensed[m_start_index+6] = getDanger(map, x+2, y+1);
	m_sensed[m_start_index+7] = getDanger(map, x+2, y);
	m_sensed[m_start_index+8] = getDanger(map, x+2, y-1);
	m_sensed[m_start_index+9] = getDanger(map, x+2, y-2);
	m_sensed[m_start_index+10] = getDanger(map, x+3, y+2);
	m_sensed[m_start_index+11] = getDanger(map, x+3, y+1);
	m_sensed[m_start_index+12] = getDanger(map, x+3, y);
	m_sensed[m_start_index+13] = getDanger(map, x+3, y-1);
	m_sensed[m_start_index+14] = getDanger(map, x+3, y-2);
	break;
      case 1:
	m_sensed[m_start_index+0] = getDanger(map, x+2, y+1);
	m_sensed[m_start_index+1] = getDanger(map, x+1, y+1);
	m_sensed[m_start_index+2] = getDanger(map, x, y+1);
	m_sensed[m_start_index+3] = getDanger(map, x-1, y+1);
	m_sensed[m_start_index+4] = getDanger(map, x-2, y+1);
	m_sensed[m_start_index+5] = getDanger(map, x+2, y+2);
	m_sensed[m_start_index+6] = getDanger(map, x+1, y+2);
	m_sensed[m_start_index+7] = getDanger(map, x, y+2);
	m_sensed[m_start_index+8] = getDanger(map, x-1, y+2);
	m_sensed[m_start_index+9] = getDanger(map, x-2, y+2);
	m_sensed[m_start_index+10] = getDanger(map, x+2, y+3);
	m_sensed[m_start_index+11] = getDanger(map, x+1, y+3);
	m_sensed[m_start_index+12] = getDanger(map, x, y+3);
	m_sensed[m_start_index+13] = getDanger(map, x-1, y+3);
	m_sensed[m_start_index+14] = getDanger(map, x-2, y+3);
	break;
      case 2:
	m_sensed[m_start_index+0] = getDanger(map, x-1, y+2);
	m_sensed[m_start_index+1] = getDanger(map, x-1, y+1);
	m_sensed[m_start_index+2] = getDanger(map, x-1, y);
	m_sensed[m_start_index+3] = getDanger(map, x-1, y-1);
	m_sensed[m_start_index+4] = getDanger(map, x-1, y-2);
	m_sensed[m_start_index+5] = getDanger(map, x-2, y+2);
	m_sensed[m_start_index+6] = getDanger(map, x-2, y+1);
	m_sensed[m_start_index+7] = getDanger(map, x-2, y);
	m_sensed[m_start_index+8] = getDanger(map, x-2, y-1);
	m_sensed[m_start_index+9] = getDanger(map, x-2, y-2);
	m_sensed[m_start_index+10] = getDanger(map, x-3, y+2);
	m_sensed[m_start_index+11] = getDanger(map, x-3, y+1);
	m_sensed[m_start_index+12] = getDanger(map, x-3, y);
	m_sensed[m_start_index+13] = getDanger(map, x-3, y-1);
	m_sensed[m_start_index+14] = getDanger(map, x-3, y-2);
	break;
      case 3:
	m_sensed[m_start_index+0] = getDanger(map, x+2, y-1);
	m_sensed[m_start_index+1] = getDanger(map, x+1, y-1);
	m_sensed[m_start_index+2] = getDanger(map, x, y-1);
	m_sensed[m_start_index+3] = getDanger(map, x-1, y-1);
	m_sensed[m_start_index+4] = getDanger(map, x-2, y-1);
	m_sensed[m_start_index+5] = getDanger(map, x+2, y-2);
	m_sensed[m_start_index+6] = getDanger(map, x+1, y-2);
	m_sensed[m_start_index+7] = getDanger(map, x, y-2);
	m_sensed[m_start_index+8] = getDanger(map, x-1, y-2);
	m_sensed[m_start_index+9] = getDanger(map, x-2, y-2);
	m_sensed[m_start_index+10] = getDanger(map, x+2, y-3);
	m_sensed[m_start_index+11] = getDanger(map, x+1, y-3);
	m_sensed[m_start_index+12] = getDanger(map, x, y-3);
	m_sensed[m_start_index+13] = getDanger(map, x-1, y-3);
	m_sensed[m_start_index+14] = getDanger(map, x-2, y-3);
	break;
      }
    }
  private:
    double getDanger(const int (&map)[mapSizeY][mapSizeX], int x, int y) {
      //x = x >= mapSizeX ? 0 : x < 0 ? mapSizeX-1 : x;
      //y = y >= mapSizeY ? 0 : y < 0 ? mapSizeY-1 : y;
      if (x >= mapSizeX || x < 0 || y >= mapSizeY || y < 0) return -1.0;
      else if (map[y][x]=='#') return -1.0;
      else if (map[y][x]=='.') return 1.0;
      else return 0.0;
    }
  };

  class FoodSensor : public Sensor {
    
  public:
    FoodSensor(std::vector<double>& inputsHub) : Sensor(1, inputsHub) {
    }
    void sense(int x, int y, int direction, const std::list<Food>& foods) {
      double i = ((foods.front().x - x)*(foods.front().x - x)) + ((foods.front().y - y)*(foods.front().y - y));
      m_sensed[m_start_index] = i;
      for (auto& food : foods)
	if ((i = ((food.x - x)*(food.x - x)) + ((food.y - y)*(food.y - y))) < m_sensed[m_start_index])
	  m_sensed[m_start_index] = i;
    }
  };
};

#endif /* !SENSOR_HPP_ */
