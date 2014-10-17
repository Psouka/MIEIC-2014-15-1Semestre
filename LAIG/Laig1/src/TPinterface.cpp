#include "TPinterface.h"


TPinterface:: TPinterface()
:CGFinterface(){
}

TPinterface:: TPinterface(ANFScene* S)
	:CGFinterface()
{
	testVar=0;
	Scene = S;
}


void TPinterface::initGUI()
{
	lights = Scene->getLights();
	cameras = Scene->getCameras();

	int i = 1;
	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++){
		addCheckboxToPanel (panelLights,(char *)((*it)->getid_s()).c_str(),(int *)&((*it)->active), i);
	}
	addColumn();
	i++;

	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 2);
	GLUI_RadioGroup *modeCamera = addRadioGroupToPanel(cameraPanel,&Scene->Active_Camera,2);

	addRadioButtonToGroup(modeCamera, "OpenGL Default");

	for(unsigned int i = 0; i < cameras.size(); i++)
	{
		addRadioButtonToGroup(modeCamera, (char *)cameras[i]->cameraid.c_str());
	}

		
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n",ctrl->user_id);
	switch (ctrl->user_id)
	{
		case 1:
			for(unsigned int i = 0; i < lights.size(); i++){
			if(lights[i]->active)
				lights[i]->turnOn();
			else
				lights[i]->turnOff();
			}
			break;
		case 2:
			printf("  Camera Changed\n");
			break;
	}
}


