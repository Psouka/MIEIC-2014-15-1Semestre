#include <vector>
#include <string>
#include <iostream>
#include "SceneGraph.h"
#include "Graph.h"
#include "Node.h"

SceneGraph::SceneGraph(Graph* graph) {
	this->graph = graph;
}

void SceneGraph::display() {

	//inicializações
	glMatrixMode(GL_MODELVIEW);
	this->process("root");
}

void SceneGraph::process(string nodeID) {
	Node *no = this->graph->getGraph()[nodeID];
	glMultMatrixf(no->getMatrix());
	//processar texturas e aparencia
	vector<string>::iterator it = no->getChildren().begin();
	for(it; it != no->getChildren().end(); it++) {
		glPushMatrix();
		process(*it);
		glPopMatrix();
	}
	//repor text e aparencia (?)
}