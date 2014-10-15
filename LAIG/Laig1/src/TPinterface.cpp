#include "TPinterface.h"


TPinterface::TPinterface()
	:CGFinterface()
{
	testVar=0;
}


void TPinterface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
    //CGFinterface::processKeyboard(key, x, y);
    
	switch(key)
	{
	default: break;
	}
}

void TPinterface::initGUI()
{
	/*
    GLUI_Panel * lightsPanel = addPanel( (char*)"Luzes", 1);
    
    addCheckboxToPanel(lightsPanel, (char*)"Luz 1", &(((LightingScene*) scene)->light0On), 0);
    addCheckboxToPanel(lightsPanel, (char*)"Luz 2", &(((LightingScene*) scene)->light1On), 1);
    addCheckboxToPanel(lightsPanel, (char*)"Luz 3", &(((LightingScene*) scene)->light2On), 2);
    addCheckboxToPanel(lightsPanel, (char*)"Luz 4", &(((LightingScene*) scene)->light3On), 3);
    addCheckboxToPanel(lightsPanel, (char*)"Luz 5", &(((LightingScene*) scene)->light4On), 4);
    
    addColumn();
    
    addButton((char*)"Parar/continuar relogio", 5);
        
    GLUI_Panel * texturePanel = addPanel( (char*)"Robot");
    
    GLUI_Listbox * textureList = addListboxToPanel(texturePanel, (char*)"Textura ", &(((LightingScene*) scene)->myBot->texture), 6);
    
    textureList->add_item (0, "Nenhuma");
    textureList->add_item (1, "Android");
    textureList->add_item (2, "Wall-e");
    textureList->add_item (3, "Teste");
    textureList->add_item (4, "Laser");
    textureList->add_item (5, "Matrix");
    
    textureList->set_int_val (1);
    
    GLUI_RadioGroup * radioGroup = addRadioGroupToPanel (texturePanel, &(((LightingScene*) scene)->myBot->isWireframe) , 7);
    
    addRadioButtonToGroup(radioGroup, (char*) "Com textura");
    addRadioButtonToGroup(radioGroup, (char*) "Wireframe");
    */
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %ld\n  ",ctrl->user_id);
	switch (ctrl->user_id)
	{
	default :break;
	}
}


