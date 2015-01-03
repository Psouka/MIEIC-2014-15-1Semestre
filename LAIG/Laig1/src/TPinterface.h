#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "ANFScene.h"

class TPinterface: public CGFinterface {

	ANFScene *Scene;
	vector<Light *> lights;
	vector<Camera *> cameras;
	int inicial_move_x,inicial_move_y;
	GLUI_StaticText* messageDisplay;
	int graph;
	vector<Graph*> Graphs;
public:
	~TPinterface();
	TPinterface();
    TPinterface(ANFScene* S);
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
	virtual void processMouse(int button, int state, int x, int y);	
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]); 
	void updateMessage();
	void setMessage(string m);
    
    int testVar;
	
};


#endif
