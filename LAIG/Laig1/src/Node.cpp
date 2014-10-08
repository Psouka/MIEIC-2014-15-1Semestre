#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Graph.h"

Node::Node(){
}

Node::Node(string nodeID) {
	this->nodeID = nodeID;
	for(int i=0;i<16;i++)
	{
		if(i==0||i==5||i==10||i==15)
			transforms[i]=1;
		else
			transforms[i]=0;
	}

}

void Node::setApp(CGFappearance *p){
	this->app = p;

}

void Node:: addPrimitive(Primitives* p){
	primitives.push_back(p);
}



void Node:: addDescend(Node * n){
	descendants.push_back(n);

}

string Node:: getID(){
	return nodeID;
}


void Node::translate(float x, float y, float z){}
void Node::rotate(string axis, float angle){}
void Node::scale(float x, float y, float z){}