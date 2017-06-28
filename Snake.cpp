#include <iostream>

#include "Snake.hpp"

BioloSnake::Snake::~Snake() {
  delete(m_eye);
  delete(m_fsLeft);
  delete(m_fsRight);
  delete(m_brain);
}

BioloSnake::Snake::Snake(int x, int y) {
  std::vector<int> posXY = {x, y};
  m_body.push_back(posXY);
  m_direction = std::rand() % 4;
  m_grow = false;
  m_alive = true;
  m_eye = new SimpleEye(m_inputs);
  m_fsLeft = new FoodSensor(m_inputs);
  m_fsRight = new FoodSensor(m_inputs);
  m_outputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_brain = new Brain(m_inputs.size(), m_outputs.size());
  m_brain->mutate();
  m_food = 20;
  m_age = 0;
  m_fork = false;
}

BioloSnake::Snake::Snake(int x, int y, const BioloSnake::Brain& brain) {
  std::vector<int> posXY = {x, y};
  m_body.push_back(posXY);
  m_direction = std::rand() % 4;
  m_grow = false;
  m_alive = true;
  m_eye = new SimpleEye(m_inputs);
  m_fsLeft = new FoodSensor(m_inputs);
  m_fsRight = new FoodSensor(m_inputs);
  m_outputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_brain = new Brain(m_inputs.size(), m_outputs.size());
  *m_brain = brain;
  m_brain->mutate();
  m_food = 20;
  m_age = 0;
  m_fork = false;
}

void BioloSnake::Snake::turnLeft() {
  m_direction = m_direction == 0 ? 3 : m_direction - 1;
}//std::cout << "turnLeft" << std::endl;}

void BioloSnake::Snake::turnRight() {
  m_direction = m_direction == 3 ? 0 : m_direction + 1;
}//std::cout << "turnRight" << std::endl;}
  
void BioloSnake::Snake::sense(const int (&map)[mapSizeY][mapSizeX]) {
  m_eye->sense(map, m_direction, m_body.front()[0], m_body.front()[1]);
}

void BioloSnake::Snake::sense(const std::list<Food>& foods) {
  switch (m_direction) {
  case 0:
    m_fsLeft->sense(m_body.front()[0], m_body.front()[1]-1, m_direction, foods);
    m_fsRight->sense(m_body.front()[0], m_body.front()[1]+1, m_direction, foods);
    break;
  case 1:
    m_fsLeft->sense(m_body.front()[0]-1, m_body.front()[1], m_direction, foods);
    m_fsRight->sense(m_body.front()[0]+1, m_body.front()[1], m_direction, foods);
    break;
  case 2:
    m_fsLeft->sense(m_body.front()[0], m_body.front()[1]+1, m_direction, foods);
    m_fsRight->sense(m_body.front()[0], m_body.front()[1]-1, m_direction, foods);
    break;
  case 3:
    m_fsLeft->sense(m_body.front()[0]+1, m_body.front()[1], m_direction, foods);
    m_fsRight->sense(m_body.front()[0]-1, m_body.front()[1], m_direction, foods);
    break;
  }
}

void BioloSnake::Snake::step() {
  if (--m_food == 0) {
    kill();
    return;
  }
  if (++m_age % 100 == 0) m_fork = true;
  m_brain->process(m_inputs, m_outputs);
  if (m_outputs[0] > 0.9) turnLeft();
  if (m_outputs[1] > 0.9) turnRight();
  std::vector<int> pos = {0, 0};

  switch(m_direction) {
  case 1:
    pos[0] = m_body.front()[0];
    pos[1] = m_body.front()[1] + 1;
    //pos[1] = pos[1] >= mapSizeY ? 0 : pos[1];
    break;
  case 3:
    pos[0] = m_body.front()[0];
    pos[1] = m_body.front()[1] - 1;
    //pos[1] = pos[1] < 0 ? mapSizeY-1 : pos[1];
    break;
  case 2:
    pos[0] = m_body.front()[0] - 1;
    //pos[0] = pos[0] < 0 ? mapSizeX-1 : pos[0];
    pos[1] = m_body.front()[1];
    break;
  case 0:
    pos[0] = m_body.front()[0] + 1;
    //pos[0] = pos[0] >= mapSizeX ? 0 : pos[0];
    pos[1] = m_body.front()[1];
    break;
  }

  if (m_grow == true) m_body.push_front(pos);
  else {
    int tmp[2];
    for (auto& bodyPart : m_body) {
      tmp[0] = bodyPart[0];
      tmp[1] = bodyPart[1];
      bodyPart[0] = pos[0];
      bodyPart[1] = pos[1];
      pos[0] = tmp[0];
      pos[1] = tmp[1];
    }
  }
  m_grow = false;
}
  
void BioloSnake::Snake::feed() {
  m_grow = true; m_food = 50;
}

void BioloSnake::Snake::kill() {
  m_alive = false;
}

bool BioloSnake::Snake::isAlive() {
  return m_alive;
}

bool BioloSnake::Snake::fork() {
  return m_fork;
}

int BioloSnake::Snake::getAge() {
  return m_age;
}
  
const std::list< std::vector<int> >& BioloSnake::Snake::getBody() {
  return m_body;
}

const BioloSnake::Brain& BioloSnake::Snake::getBrain() {
  return *m_brain;
}

void BioloSnake::Snake::dump() {
  for (auto& bp : m_body) std::cout << "(" << bp[0] << "," << bp[1] << ")";
}
