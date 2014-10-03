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
	string ID;
	vector<string> children;
	vector<Primitives*> primitives;
	float matrix[16];
	Appearance* appearance;
	static Appearance* fatherAppearance;
public:
	Node();
};

#endif