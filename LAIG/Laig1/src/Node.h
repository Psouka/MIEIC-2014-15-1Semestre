#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Primitives.h"
#include <string>
#include <iostream>
#include "CGFscene.h"
#include "Appearance.h"
using namespace std;

class Node
{
	string nodeID;
	vector<Node*> childrenNodes;
	vector<Primitives*> primitivas;
	float transforms[16];
	Appearance* appearance;
	string appearanceref;
	float length_s,length_t;
	static Appearance* parentApp;
public:
	Node();
};

#endif