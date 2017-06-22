#include <vector>
#include <thread>
#include <chrono>
#include <list>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "MLP.h"

#define mapSizeX 100
#define mapSizeY 50

const static double mutationRate = 0.1;
const static double mutationCoef = 0.4;

class Brain : public NeuralNetwork::MLP {
 public:
  Brain() : NeuralNetwork::MLP(4) {
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);
    addNeuron(0);

    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);
    addNeuron(1);

    addNeuron(2);
    addNeuron(2);
    addNeuron(2);
    addNeuron(2);
    addNeuron(2);

    addNeuron(3);
    addNeuron(3);
  }

  void mutate() {
    for (unsigned int layer = 0, layerMax = m_activation.size()-1;
	 layer < layerMax; ++layer) {
      for (unsigned int neuronIn = 0, neuronInMax = m_activation[layer].size();
	   neuronIn < neuronInMax; ++neuronIn)
	{
	  for (unsigned int neuronOut = 0, neuronOutMax = m_activation[layer+1].size();
	       neuronOut < neuronOutMax; ++neuronOut)
	    {
	      if (std::rand()%(int)(mutationRate*100) == 0)
		m_weights[layer][neuronIn][neuronOut] += (double)(std::rand()%(int)(mutationCoef*100))/100;
	      else if (std::rand()%(int)(mutationRate*100) == 1)
		m_weights[layer][neuronIn][neuronOut] -= (double)(std::rand()%(int)(mutationCoef*100))/100;
	    }
	}
    }
  }
 private:
};

class Snake {
  
public:
  Snake(int x, int y) {
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
    m_outputs.push_back(0.0);
    m_outputs.push_back(0.0);
    m_brain.mutate();
    m_food = 50;
    m_age = 0;
    m_fork = false;
  }

  Snake(int x, int y, const Brain& brain) {
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
    m_outputs.push_back(0.0);
    m_outputs.push_back(0.0);
    m_brain = brain;
    m_brain.mutate();
    m_food = 50;
    m_age = 0;
    m_fork = false;
  }

  void turnLeft() { m_direction = m_direction == 0 ? 3 : m_direction - 1; }//std::cout << "turnLeft" << std::endl;}
  void turnRight() { m_direction = m_direction == 3 ? 0 : m_direction + 1; }//std::cout << "turnRight" << std::endl;}

  double getDanger(const int (&map)[mapSizeY][mapSizeX], int x, int y) {
    //x = x >= mapSizeX ? 0 : x < 0 ? mapSizeX-1 : x;
    //y = y >= mapSizeY ? 0 : y < 0 ? mapSizeY-1 : y;
    if (x >= mapSizeX || x < 0 || y >= mapSizeY || y < 0) return -1.0;
    else if (map[y][x]=='#') return -1.0;
    else if (map[y][x]=='.') return 1.0;
    else return 0.0;
  }
  
  void sense(const int (&map)[mapSizeY][mapSizeX]) {
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
      break;
    }
  }
  
  void step() {
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
  
  void feed() { m_grow = true; m_food += 40;}
  void kill() { m_alive = false; }
  bool isAlive() { return m_alive; }
  bool fork() { return m_fork; }

  int getAge() { return m_age; }
  
  const std::list< std::vector<int> >& getBody() { return m_body; }
  const Brain& getBrain() { return m_brain; }

  void dump() { for (auto& bp : m_body) std::cout << "(" << bp[0] << "," << bp[1] << ")";}

private:
  std::list< std::vector<int> > m_body;
  int m_direction;
  bool m_grow;
  bool m_alive;
  Brain m_brain;
  int m_food;
  int m_age;
  bool m_fork;

  std::vector<double> m_inputs;
  std::vector<double> m_outputs;
};

struct Food {
  Food(int x, int y) {this->x = x; this->y = y; eaten = false;};
  int x;
  int y;
  bool eaten;
};

void display(int (&map)[mapSizeY][mapSizeX], std::list<Snake*>& snakes, std::list<Food>& foods, bool disp) {
  std::memset(map, ' ', sizeof(map));
  for (auto& food : foods) {
    map[food.y][food.x] = '.';
  }
  for (auto& snake : snakes) {
    for (auto& bodyPart : snake->getBody()) {
      map[bodyPart[1]][bodyPart[0]] = '#';
    }
  }
  if (!disp) return;
  for (int y = 0; y < mapSizeY; ++y) {
    for (int x = 0; x < mapSizeX; ++x) {
      std::cout << (char)map[y][x];
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
  std::cout << "\033[u" << std::flush;
}

void collisions(std::list<Snake*>& snakes, std::list<Snake*>& deadSnakes, std::list<Food>& foods) {
  for (auto& snake : snakes) {
    auto& snakeHead = snake->getBody().front();
    if (snakeHead[0] < 0 || snakeHead[0] >= mapSizeX ||
	snakeHead[1] < 0 || snakeHead[1] >= mapSizeY) {
      snake->kill();
      continue;
    }

    for (auto& food : foods) {
      if (food.eaten == false &&
	  snakeHead[0] == food.x &&
	  snakeHead[1] == food.y) {
	snake->feed();
	food.eaten = true;
	break;
      }
    }
    
    for (auto& snake2 : snakes) {
      if (snake->isAlive() == false) break;
      if (snake == snake2)
	for (auto bodyPartIt = snake2->getBody().begin(); bodyPartIt != snake2->getBody().end(); ++bodyPartIt) {
	  if (bodyPartIt != snake2->getBody().begin() &&
	      snakeHead[0] == (*bodyPartIt)[0] &&
	      snakeHead[1] == (*bodyPartIt)[1]) {
	    snake->kill();
	    break;
	  }
	}
      else
	for (auto& bodyPart : snake2->getBody()) {
	  //if (snakeHead == bodyPart) continue;
	  if (snakeHead[0] == bodyPart[0] &&
	      snakeHead[1] == bodyPart[1]) {
	    snake->kill();
	    //	  exit(56);
	    break;
	  }
	}
    }
  }

  for (std::list<Snake*>::iterator it = snakes.begin(); it != snakes.end();) {
    if ((*it)->isAlive() == false) {
      deadSnakes.push_back(*it);
      it = snakes.erase(it);
    } else ++it;
  }
  for (std::list<Food>::iterator it = foods.begin(); it != foods.end();) {
    if ((*it).eaten == true) {
      it = foods.erase(it);
    } else ++it;
  }
}

void move(std::list<Snake*>& snakes) {
  for (auto& snake : snakes) {
    snake->step();
  }
}

void sense(std::list<Snake*>& snakes, const int (&map)[mapSizeY][mapSizeX]) {
  for (auto& snake : snakes) {
    snake->sense(map);
  }
}

void foodGeneration(std::list<Food>& foods, int min, int max) {
  if (foods.size() > 200) return;
  for (int rand = min + (min == max ? 0 : std::rand() % (max-min)); rand > 0; --rand)
    foods.push_back(Food(std::rand()%mapSizeX, std::rand()%mapSizeY));
}

void snakeGeneration(std::list<Snake*>& snakes, int min, int max) {
  for (int rand = min + (min == max ? 0 : std::rand() % (max-min)); rand > 0; --rand)
    snakes.push_back(new Snake(std::rand()%mapSizeX, std::rand()%mapSizeY));
}

void birth(std::list<Snake*>& snakes) {
  if (snakes.size() > 20) return;
  for (auto& snake : snakes) {
    if (snake->fork() == true)
      snakes.push_back(new Snake(std::rand()%mapSizeX, std::rand()%mapSizeY, snake->getBrain()));
  }
}

void cloneBestDeadSnake(std::list<Snake*>& snakes, std::list<Snake*>& deadSnakes) {
  deadSnakes.sort([](Snake* const& a, Snake* const& b) -> bool
		  {
		    return a->getAge() > b->getAge();
		  });
  for (int i = 0; i < 30; ++i) {
    snakes.push_back(new Snake(std::rand()%mapSizeX, std::rand()%mapSizeY, deadSnakes.front()->getBrain()));
  }
  snakes.push_back(deadSnakes.front());
  deadSnakes.pop_front();
  for (std::list<Snake*>::iterator it = deadSnakes.begin(); it != deadSnakes.end();) {
    delete *it;
    it = deadSnakes.erase(it);
  }
}

int main(int ac, char**av) {
  int map[mapSizeY][mapSizeX]; std::memset(map, ' ', sizeof(map));
  std::list<Snake*> snakes;
  std::list<Snake*> deadSnakes;
  std::list<Food> foods;

  std::srand(std::time(0));

  snakeGeneration(snakes, 30, 30);
  //no display train
  std::cout << "\033[2J" << std::flush;
  for (int i = 0, imax = (ac == 2 ? std::atoi(av[1]) : 1000); i < imax; ++i) {    
    std::cout << "\033[2J\033[0;0f\033[s" << std::flush;
    std::cout << "epoch: " << i << "/" << imax << std::endl;
    foodGeneration(foods, 10, 100);
    collisions(snakes, deadSnakes, foods);
    while (snakes.size() > 0) {
      foodGeneration(foods, 1, 2);
      display(map, snakes, foods, false);
      sense(snakes, map);
      move(snakes);
      collisions(snakes, deadSnakes, foods);
      //    snakeGeneration(snakes, 1, 1);
      //birth(snakes);
    }
    cloneBestDeadSnake(snakes, deadSnakes);
  }
  //display train
  std::cout << "\033[2J" << std::flush;
  while (42) {
    std::cout << "\033[0;0f\033[s" << std::flush;
    foodGeneration(foods, 10, 100);
    collisions(snakes, deadSnakes, foods);
    while (snakes.size() > 0) {
      foodGeneration(foods, 1, 2);
      display(map, snakes, foods, true);
      sense(snakes, map);
      move(snakes);
      collisions(snakes, deadSnakes, foods);
      //    snakeGeneration(snakes, 1, 1);
      //birth(snakes);
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    cloneBestDeadSnake(snakes, deadSnakes);
  }
  return 0;
}
