#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Graph.h"

Node::Node(string nodeID) {
	this->ID = nodeID;
}

Node::Node(string nodeID, vector<string> children) {
	this->ID = nodeID;
	this->children = children;
}

string Node::getID() {
	return this->ID;
}

float* Node::getMatrix() {
	return matrix;
}

void Node::setParentApp(Appearance* fatherAppearance) {
	this->fatherAppearance = fatherAppearance;
}

vector<string> Node::getChildren() {
	return this->children;
}