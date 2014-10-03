#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "Graph.h"
#include "Node.h"

class SceneGraph {
	Graph* graph;

public:
	display();
	process(string nodeID);
};