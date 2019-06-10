all: maxflow

maxflow: graph.o
	g++ main.cpp graph.o -std=c++11 -g -o maxflow -O3 -Wall

graph.o: graph.cpp
	g++ graph.cpp -std=c++11 -g -c -o graph.o -O3 -Wall
	
clean:
	rm maxflow
	rm graph.o
