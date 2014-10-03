#ifndef _NODE_H_
#define _NODE_H_

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
	Node(string ID);
	Node(string ID, vector<string> children);
	void setParentApp(Appearance* fatherAppearance);
	string getID();
	float* getMatrix();
	vector<string> getChildren();
	void readANF(); //caso não seja para fazer o read no construtor
};

#endif