all: hard

easy:

	g++ -O3 -std=c++11 -o bioloSnake *.cpp NeuralNetwork/MLP.cpp -I./NeuralNetwork

hard:
	g++ -D DEADLY_COLLISIONS -O3 -std=c++11 -o bioloSnake *.cpp NeuralNetwork/MLP.cpp -I./NeuralNetwork

debug:
	g++ -D DEBUG -g3 -O3 -std=c++11 -o bioloSnake *.cpp NeuralNetwork/MLP.cpp -I./NeuralNetwork
