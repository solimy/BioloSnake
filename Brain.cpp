#include "Brain.hpp"

BioloSnake::Brain::Brain(int inputs, int outputs) : NeuralNetwork::MLP(4) {
  for (int i = 0; i < inputs; ++i)
    addNeuron(0);

  for (int i = 0; i < inputs; ++i)
    addNeuron(1);

  for (int i = 0; i < inputs / 2; ++i)
    addNeuron(2);

  for (int i = 0; i < outputs; ++i)
    addNeuron(3);
}

void BioloSnake::Brain::mutate() {
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

