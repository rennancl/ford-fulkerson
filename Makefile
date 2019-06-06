all: maxflow

maxflow: directed_graph.o
	g++ main.cpp directed_graph.o -std=c++11 -g -o maxflow -O3 -Wall

directed_graph.o: directed_graph.cpp
	g++ directed_graph.cpp -std=c++11 -g -c -o directed_graph.o -O3 -Wall
	
clean:
	rm maxflow
	rm directed_graph.o
