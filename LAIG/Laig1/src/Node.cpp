#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "Graph.h"

Node:: ~Node(){
	for(unsigned int i = 0; i <nodeChilds.size(); i++)
		delete(nodeChilds[i]);

	for(unsigned int i = 0; i <primitives.size(); i++)
		delete(primitives[i]);

	delete(app);
	
	for(unsigned int i = 0; i <animsV.size(); i++)
		delete(animsV[i]);
}

Node::Node() {

}

Node::Node(string ID,bool displaylist) {
	this->displaylist = displaylist;
	this->nodeID = ID;
	this->displaylistGen = false;
	this->dlID = NULL;
	this->activeAnim = 0;
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,transforms);
	glPopMatrix();
}

int Node::getActiveAnim() {
	return activeAnim;
}

void Node::setActiveAnim(int animN) {
	this->activeAnim = animN;
}

GLuint Node::getdlID() {
	return dlID;
}

vector<Animation*> Node::getAnimsVector() {
	return animsV;
}

void Node::setAnimsVector(vector<Animation*> animsV) {
	this->animsV = animsV;
}


void Node::setdlID(GLuint id) {
	this->dlID = id;
}


bool Node::getDisplayList() {
	return displaylist;
}

bool Node::getDisplayListGen() {
	return displaylistGen;
}

void Node::setDisplayListGen(bool dlGen) {
	this->displaylistGen = dlGen;
}


void Node::setApp(Appearance *p) {
	this->app = p;
}

float* Node::getMatrix() {
	return transforms;
}

void Node::addPrimitive(Primitives* p) {
	primitives.push_back(p);
}

void Node::addDescend(string n) {
	children.push_back(n);
}

string Node::getID() {
	return nodeID;
}

vector<string> Node::getChildren() {
	return children;
}

vector<Primitives*> Node::getPrimitives() {
	return primitives;
}

void Node::ApplyApp() {
	if(app!= NULL)
		app->apply();
}

vector<Node*> Node::getNChilds() {
	return nodeChilds;
}

void Node::setChilds(vector<Node*> n) {
	nodeChilds = n;
}

Appearance * Node::getApp() {
	return app;
}



void Node::translate(float x, float y, float z)
{
	glPushMatrix();
	glLoadMatrixf(transforms);
	glTranslatef(x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX,transforms);
	glPopMatrix();
}

void Node::rotate(string axis, float angle)
{
	glPushMatrix();
	glLoadMatrixf(transforms);
	if(axis=="x")
		glRotatef(angle,1,0,0);
	if(axis=="y")
		glRotatef(angle,0,1,0);
	if(axis=="z")
		glRotatef(angle,0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX,transforms);
	glPopMatrix();
}

void Node::scale(float x, float y, float z)
{
	glPushMatrix();
	glLoadMatrixf(transforms);
	glScalef(x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX,transforms);
	glPopMatrix();
}
