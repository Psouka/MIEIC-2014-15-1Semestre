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
	string nodeID;
	vector<string> children;
	vector<Node*> nodeChilds;
	vector<Primitives *> primitives;
	float transforms[16];
	Appearance * app;
public:
	Node();
	Node(string ID);
	void setApp(Appearance *p);
	void addPrimitive(Primitives* p);
	void addDescend(string n);
	string getID();
	float* getMatrix();
	void translate(float x, float y, float z);
	void rotate(string axis, float angle);
	void scale(float x, float y, float z);
	vector<string> getChildren();
	vector<Primitives*> getPrimitives();
	void ApplyApp();
	vector<Node*> getNChilds();
	void setChilds(vector<Node*> n);
	Appearance * getApp();
};

#endif