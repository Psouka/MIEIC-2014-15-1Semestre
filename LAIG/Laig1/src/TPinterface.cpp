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


	int i = 1;
	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++){
		addCheckboxToPanel (panelLights,(char *)((*it)->getid_s()).c_str(),(int *)&((*it)->active), i);
	}

	
	addColumn();
	/*
	int & activeCameraPosition = ((Scene *)this->scene)->activeCameraPosition;
	std::cout << "active xx camera:"<< ((Scene *)this->scene)->activeCameraPosition;


	// Jump the first camera..
	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 1);
	GLUI_RadioGroup * rgCameras = addRadioGroupToPanel(cameraPanel,&((Scene *)this->scene)->activeCameraPosition, 123);
	i = 20;
	
	std::vector<Camera *> cameras = ((Scene *)this->scene)->getCameras();

	unsigned size = i + cameras.size();
	std::vector<Camera *>::iterator it = cameras.begin();	
	for(; it != cameras.end() ;it++, i++){
		addRadioButtonToGroup (rgCameras, (char *)(*it)->getTitle().c_str());
		//if(size == i && size != 19){
//			addSeparatorToPanel(cameraPanel);
		//}
	} */
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


