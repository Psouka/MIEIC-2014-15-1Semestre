#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Primitives.h"
#include <string>
#include <iostream>
#include "CGFscene.h"
#include "Appearance.h"
#include "Animation.h"

using namespace std;

class Node {
	bool displaylist;
	bool displaylistGen;
	string nodeID;
	vector<string> children;
	vector<Node*> nodeChilds;
	vector<Primitives *> primitives;
	float transforms[16];
	Appearance * app;
	Animation * anim;
	GLuint dlID;
	

public:
	Node();
	Node(string ID,bool displaylist);
	GLuint getdlID();
	void setdlID(GLuint id);
	bool getDisplayList();
	bool getDisplayListGen();
	void setDisplayListGen(bool dlGen);
	void setApp(Appearance *p);
	void setAnim(Animation *a);
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