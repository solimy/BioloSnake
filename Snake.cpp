#include <iostream>

#include "Snake.hpp"

BioloSnake::Snake::Snake(int x, int y) {
  std::vector<int> posXY = {x, y};
  m_body.push_back(posXY);
  m_direction = std::rand() % 4;
  m_grow = false;
  m_alive = true;
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_brain.mutate();
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
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_inputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_outputs.push_back(0.0);
  m_brain = brain;
  m_brain.mutate();
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

double BioloSnake::Snake::getDanger(const int (&map)[mapSizeY][mapSizeX], int x, int y) {
  //x = x >= mapSizeX ? 0 : x < 0 ? mapSizeX-1 : x;
  //y = y >= mapSizeY ? 0 : y < 0 ? mapSizeY-1 : y;
  if (x >= mapSizeX || x < 0 || y >= mapSizeY || y < 0) return -1.0;
  else if (map[y][x]=='#') return -1.0;
  else if (map[y][x]=='.') return 1.0;
  else return 0.0;
}
  
void BioloSnake::Snake::sense(const int (&map)[mapSizeY][mapSizeX]) {
  int x = m_body.front()[0];
  int y = m_body.front()[1];
  switch (m_direction) {
  case 0:
    m_inputs[0] = getDanger(map, x+1, y+2);
    m_inputs[1] = getDanger(map, x+1, y+1);
    m_inputs[2] = getDanger(map, x+1, y);
    m_inputs[3] = getDanger(map, x+1, y-1);
    m_inputs[4] = getDanger(map, x+1, y-2);
    m_inputs[5] = getDanger(map, x+2, y+2);
    m_inputs[6] = getDanger(map, x+2, y+1);
    m_inputs[7] = getDanger(map, x+2, y);
    m_inputs[8] = getDanger(map, x+2, y-1);
    m_inputs[9] = getDanger(map, x+2, y-2);
    m_inputs[10] = getDanger(map, x+3, y+2);
    m_inputs[11] = getDanger(map, x+3, y+1);
    m_inputs[12] = getDanger(map, x+3, y);
    m_inputs[13] = getDanger(map, x+3, y-1);
    m_inputs[14] = getDanger(map, x+3, y-2);
    break;
  case 1:
    m_inputs[0] = getDanger(map, x+2, y+1);
    m_inputs[1] = getDanger(map, x+1, y+1);
    m_inputs[2] = getDanger(map, x, y+1);
    m_inputs[3] = getDanger(map, x-1, y+1);
    m_inputs[4] = getDanger(map, x-2, y+1);
    m_inputs[5] = getDanger(map, x+2, y+2);
    m_inputs[6] = getDanger(map, x+1, y+2);
    m_inputs[7] = getDanger(map, x, y+2);
    m_inputs[8] = getDanger(map, x-1, y+2);
    m_inputs[9] = getDanger(map, x-2, y+2);
    m_inputs[10] = getDanger(map, x+2, y+3);
    m_inputs[11] = getDanger(map, x+1, y+3);
    m_inputs[12] = getDanger(map, x, y+3);
    m_inputs[13] = getDanger(map, x-1, y+3);
    m_inputs[14] = getDanger(map, x-2, y+3);
    break;
  case 2:
    m_inputs[0] = getDanger(map, x-1, y+2);
    m_inputs[1] = getDanger(map, x-1, y+1);
    m_inputs[2] = getDanger(map, x-1, y);
    m_inputs[3] = getDanger(map, x-1, y-1);
    m_inputs[4] = getDanger(map, x-1, y-2);
    m_inputs[5] = getDanger(map, x-2, y+2);
    m_inputs[6] = getDanger(map, x-2, y+1);
    m_inputs[7] = getDanger(map, x-2, y);
    m_inputs[8] = getDanger(map, x-2, y-1);
    m_inputs[9] = getDanger(map, x-2, y-2);
    m_inputs[10] = getDanger(map, x-3, y+2);
    m_inputs[11] = getDanger(map, x-3, y+1);
    m_inputs[12] = getDanger(map, x-3, y);
    m_inputs[13] = getDanger(map, x-3, y-1);
    m_inputs[14] = getDanger(map, x-3, y-2);
    break;
  case 3:
    m_inputs[0] = getDanger(map, x+2, y-1);
    m_inputs[1] = getDanger(map, x+1, y-1);
    m_inputs[2] = getDanger(map, x, y-1);
    m_inputs[3] = getDanger(map, x-1, y-1);
    m_inputs[4] = getDanger(map, x-2, y-1);
    m_inputs[5] = getDanger(map, x+2, y-2);
    m_inputs[6] = getDanger(map, x+1, y-2);
    m_inputs[7] = getDanger(map, x, y-2);
    m_inputs[8] = getDanger(map, x-1, y-2);
    m_inputs[9] = getDanger(map, x-2, y-2);
    m_inputs[10] = getDanger(map, x+2, y-3);
    m_inputs[11] = getDanger(map, x+1, y-3);
    m_inputs[12] = getDanger(map, x, y-3);
    m_inputs[13] = getDanger(map, x-1, y-3);
    m_inputs[14] = getDanger(map, x-2, y-3);
    break;
  }
}
  
void BioloSnake::Snake::step() {
  if (--m_food == 0) {
    kill();
    return;
  }
  if (++m_age % 100 == 0) m_fork = true;
  m_brain.process(m_inputs, m_outputs);
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
  return m_brain;
}

void BioloSnake::Snake::dump() {
  for (auto& bp : m_body) std::cout << "(" << bp[0] << "," << bp[1] << ")";
}
