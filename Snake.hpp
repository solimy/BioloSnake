#ifndef SNAKE_HPP_
# define SNAKE_HPP_

#include <list>
#include <vector>

#include "Global.h"
#include "Brain.hpp"
#include "Sensor.hpp"

namespace BioloSnake {

  class Snake {
  
  public:
    Snake(int x, int y);
    Snake(int x, int y, const Brain& brain);
    ~Snake();
    void turnLeft();
    void turnRight();
    void sense(const int (&map)[mapSizeY][mapSizeX]);
    void sense(const std::list<Food>& foods);
    void step();
    void feed();
    void kill();
    void resurrection();
    bool isAlive();
    bool fork();
    int getAge();
    const std::list< std::vector<int> >& getBody();
    const Brain& getBrain();
    void dump();

  private:
    std::list< std::vector<int> > m_body;
    int m_direction;
    bool m_grow;
    bool m_alive;
    Brain* m_brain;
    SimpleEye* m_eye;
    FoodSensor* m_fsLeft;
    FoodSensor* m_fsRight;
    int m_food;
    int m_age;
    bool m_fork;

    std::vector<double> m_inputs;
    std::vector<double> m_outputs;
  };

}

#endif /* !SNAKE_HPP_ */
