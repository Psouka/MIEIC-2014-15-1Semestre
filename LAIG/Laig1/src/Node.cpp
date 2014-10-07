#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Graph.h"

Node::Node(string nodeID) {
	this->nodeID = nodeID;
}

Node::Node(string nodeID, vector<string> children) {
	this->nodeID = nodeID;
	this->childStrids = children;
}

string Node::getID() {
	return this->nodeID;
}

float* Node::getMatrix() {
	return transforms;
}

void Node::setParentApp(Appearance* fatherAppearance) {
	this->fatherAppearance = fatherAppearance;
}

vector<string> Node::getChildren() {
	return this->childStrids;
}