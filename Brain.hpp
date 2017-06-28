#ifndef BRAIN_HPP_
# define BRAIN_HPP_

#include "MLP.h"

namespace BioloSnake {

  const static double mutationRate = 0.1;//0.1
  const static double mutationCoef = 0.4;//0.4

  class Brain : public NeuralNetwork::MLP {
  public:
    Brain();
    void mutate();
  private:
  };

}

#endif /* BRAIN_HPP_ */
