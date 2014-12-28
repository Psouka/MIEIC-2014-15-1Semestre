#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "ANFScene.h"

class TPinterface: public CGFinterface {

	ANFScene *Scene;
	std::vector<Light *> lights;
	std::vector<Camera *> cameras;
	int inicial_move_x,inicial_move_y;

public:
	~TPinterface();
	TPinterface();
    TPinterface(ANFScene* S);
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
	virtual void processMouse(int button, int state, int x, int y);	
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]); 
    
    int testVar;
	
};


#endif
