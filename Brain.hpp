#ifndef BRAIN_HPP_
# define BRAIN_HPP_

#include "MLP.h"

namespace BioloSnake {

  const static double mutationRate = 0.1;//0.1
  const static double mutationCoef = 0.4;//0.4

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
		if (std::rand()%(int)(mutationRate*100) < mutationRate*100)
		  m_weights[layer][neuronIn][neuronOut] += (rand()%2 == 0 ? -1 : 1)*((double)(std::rand()%(int)(mutationCoef*100))/100);
	      }
	  }
      }
    }
  private:
  };

}

#endif /* BRAIN_HPP_ */
