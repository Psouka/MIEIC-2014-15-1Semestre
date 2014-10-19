#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"
#include "ANFScene.h"

class TPinterface: public CGFinterface {

	ANFScene *Scene;
	std::vector<Light *> lights;
	std::vector<Camera *> cameras;

public:
	TPinterface();
    TPinterface(ANFScene* S);
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
    
    int testVar;
	
};


#endif
