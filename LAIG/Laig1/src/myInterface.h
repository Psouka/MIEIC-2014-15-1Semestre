#ifndef MYINTERFACE_H
#define MYINTERFACE_H

#include "CGFinterface.h"
#include "myScene.h"

class myInterface: public CGFinterface {
public:
	myInterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);
private:
};


#endif
