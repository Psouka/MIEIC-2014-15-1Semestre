#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Graph.h"
#include "Node.h"

class SceneGraph {
	Graph* graph;

public:
	SceneGraph(Graph* graph);
	void display();
	void process(string nodeID);
};

#endif