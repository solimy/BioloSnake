all:
	g++ -std=c++11 -o bioloSnake *.cpp NeuralNetwork/MLP.cpp -I./NeuralNetwork
