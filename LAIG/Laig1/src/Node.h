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
	GLuint dlID;
	vector<Animation*> animsV;
	int activeAnim;

public:
	~Node();
	Node();
	Node(string ID,bool displaylist);
	GLuint getdlID();
	void setdlID(GLuint id);
	bool getDisplayList();
	bool getDisplayListGen();
	void setDisplayListGen(bool dlGen);
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
	vector<Animation*> getAnimsVector();
	void setAnimsVector(vector<Animation*> animsv);
	int getActiveAnim();
	void setActiveAnim(int animN);
};

#endif