all:
	g++ -std=c++11 -o bioloSnake snake.cpp NeuralNetwork/MLP.cpp -I./NeuralNetwork
