#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Graph.h"
#include "Node.h"

Graph::Graph(){
}

Graph::Graph(string root) {
	this->root = root;
}

Graph::graphMap Graph::getGraph() {
	return this->graph;
}

void Graph:: addNode(Node* n){
	graph[n->getID()] = n;
}

void draw(){

}

string Graph :: getRoot(){
	return root;
}