#include <vector>
#include <thread>
#include <chrono>
#include <list>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Global.h"
#include "Brain.hpp"
#include "Snake.hpp"

void display(int (&map)[mapSizeY][mapSizeX], std::list<BioloSnake::Snake*>& snakes, std::list<Food>& foods, bool disp) {
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

void collisions(std::list<BioloSnake::Snake*>& snakes, std::list<BioloSnake::Snake*>& deadSnakes, std::list<Food>& foods) {
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
	  if (snakeHead[0] == bodyPart[0] &&
	      snakeHead[1] == bodyPart[1]) {
	    snake->kill();
	    break;
	  }
	}
    }
  }

  for (std::list<BioloSnake::Snake*>::iterator it = snakes.begin(); it != snakes.end();) {
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

void move(std::list<BioloSnake::Snake*>& snakes) {
  for (auto& snake : snakes) {
    snake->step();
  }
}

void sense(std::list<BioloSnake::Snake*>& snakes, std::list<Food>& foods, const int (&map)[mapSizeY][mapSizeX]) {
  for (auto& snake : snakes) {
    snake->sense(map);
    snake->sense(foods);
  }
}

void foodGeneration(std::list<Food>& foods, int min, int max) {
  if (foods.size() > 300) return;
  for (int rand = min + (min == max ? 0 : std::rand() % (max-min)); rand > 0; --rand)
    foods.push_back(Food(std::rand()%mapSizeX, std::rand()%mapSizeY));
}

void snakeGeneration(std::list<BioloSnake::Snake*>& snakes, int min, int max) {
  for (int rand = min + (min == max ? 0 : std::rand() % (max-min)); rand > 0; --rand)
    snakes.push_back(new BioloSnake::Snake(std::rand()%mapSizeX, std::rand()%mapSizeY));
}

void birth(std::list<BioloSnake::Snake*>& snakes) {
  if (snakes.size() > 20) return;
  for (auto& snake : snakes) {
    if (snake->fork() == true)
      snakes.push_back(new BioloSnake::Snake(std::rand()%mapSizeX, std::rand()%mapSizeY, snake->getBrain()));
  }
}

void cloneBestDeadSnake(std::list<BioloSnake::Snake*>& snakes, std::list<BioloSnake::Snake*>& deadSnakes) {
  deadSnakes.sort([](BioloSnake::Snake* const& a, BioloSnake::Snake* const& b) -> bool
		  {
		    return a->getAge() > b->getAge();
		  });
  for (int i = 0; i < 30; ++i) {
    snakes.push_back(new BioloSnake::Snake(std::rand()%mapSizeX, std::rand()%mapSizeY, deadSnakes.front()->getBrain()));
  }
  snakes.push_back(deadSnakes.front());
  deadSnakes.pop_front();
  for (std::list<BioloSnake::Snake*>::iterator it = deadSnakes.begin(); it != deadSnakes.end();) {
    delete *it;
    it = deadSnakes.erase(it);
  }
}

int main(int ac, char**av) {
  int map[mapSizeY][mapSizeX]; std::memset(map, ' ', sizeof(map));
  std::list<BioloSnake::Snake*> snakes;
  std::list<BioloSnake::Snake*> deadSnakes;
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
      sense(snakes, foods, map);
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
      sense(snakes, foods, map);
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
