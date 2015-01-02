#include "TPinterface.h"
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

TPinterface::~TPinterface(){
	delete(Scene);

	for(unsigned int i = 0; i < lights.size(); i++)
		delete(lights[i]);

	for(unsigned int i = 0; i < cameras.size(); i++)
		delete(cameras[i]);
}

TPinterface::TPinterface(): CGFinterface() {
	inicial_move_x = inicial_move_y = -1;
}

TPinterface::TPinterface(ANFScene* S): CGFinterface() {
	testVar=0;
	Scene = S;
	inicial_move_x = inicial_move_y = -1;
	Graphs.push_back(Scene->getGraph());

	Scene->parse("room2.anf");
	Graphs.push_back(Scene->getGraph());

	Scene->parse("room3.anf");
	Graphs.push_back(Scene->getGraph());

	graph = 0;
	Scene->setGraph(Graphs[graph]);

}

void TPinterface::initGUI() {
	lights = Scene->getLights();
	cameras = Scene->getCameras();

	int i = 1;
	GLUI_Panel * panelLights = addPanel("Lights: ", 1);
	for(std::vector<Light *>::iterator it = lights.begin(); it != lights.end() ;it++) {
		addCheckboxToPanel (panelLights,(char *)((*it)->getid_s()).c_str(),(int *)&((*it)->active), i);
	}
	addColumn();
	i++;

	GLUI_Panel * cameraPanel = addPanel("Cameras: ", 1);
	GLUI_RadioGroup *modeCamera = addRadioGroupToPanel(cameraPanel,&Scene->Active_Camera,2);

	addRadioButtonToGroup(modeCamera, "OpenGL Default");

	for(unsigned int i = 0; i < cameras.size(); i++)
	{
		addRadioButtonToGroup(modeCamera, (char *)cameras[i]->cameraid.c_str());
	}

	addColumn();


	GLUI_Panel * texturePanel = addPanel( (char*)"Draw Mode");
	GLUI_Listbox * textureList = addListboxToPanel(texturePanel, (char*)"", &(Scene->drawMode), 3);

	textureList->add_item (0, "Fill");
	textureList->add_item (1, "Wireframe");
	textureList->add_item (2, "Point");

	GLUI_Panel * windPanel = addPanel("Wind: ", 1);
	GLUI_Spinner* winrot =addSpinnerToPanel( windPanel,"",  2, &(Scene->globalWind), 4);

	addColumn();

	addButton((char*)"New Game", 7);

	GLUI_Panel * gameMode = addPanel("Game Mode", 1);


	GLUI_RadioGroup *gMode = addRadioGroupToPanel(gameMode,&Scene->GameScene->bot,10);
	addRadioButtonToGroup(gMode, "Player vs Player");
	addRadioButtonToGroup(gMode, "Player vs Pc");


	GLUI_Panel * movPanel = addPanel("Mov: ", 1);

	messageDisplay = addStaticTextToPanel(movPanel, "Player A");

	GLUI_RadioGroup *modeGame = addRadioGroupToPanel(movPanel,&Scene->play_Mode,5);

	addRadioButtonToGroup(modeGame, "New Piece");
	addRadioButtonToGroup(modeGame, "Move Piece");


	GLUI_Panel * movPiece = addPanel("In Case Move", 1);

	GLUI_Listbox * wallList = addListboxToPanel(movPiece, (char*)"", &(Scene->wallPosition), 6);

	wallList->add_item (1, "North");
	wallList->add_item (2, "South");
	wallList->add_item (3, "West");
	wallList->add_item (4, "East");


	addButton((char*)"Undo", 8);
	addColumn();

	GLUI_Panel * graphPanel = addPanel( (char*)"Scene");
	GLUI_Listbox * graphList = addListboxToPanel(graphPanel, (char*)"", &(graph), 9);

	graphList->add_item (0, "Room1.anf");
	graphList->add_item (1, "Room2.anf");
	graphList->add_item (2, "Room3.anf");
}

void TPinterface::processGUI(GLUI_Control *ctrl) {
	printf ("\nGUI control id: %d",ctrl->user_id);
	switch (ctrl->user_id)
	{
	case 1:
		for(unsigned int i = 0; i < lights.size(); i++) {
			if(lights[i]->active)
				lights[i]->turnOn();
			else
				lights[i]->turnOff();
		}
		break;
	case 2:
		printf("\nCamera Changed");
		Scene->changeCamera();
		break;
	case 3:
		printf("\nDraw Mode Changed");
		break;
	case 4:
		printf("\nWind Changed");
		Scene->setGlobalWind();
		break;
	case 5:
		if(Scene->GameScene->isActive() || Scene->GameScene->gameState() )
		{
			Scene->play_Mode = -1;
			printf("\nPlaying / Game over");
		}
		break;
	case 6:
		printf("\nWall position Changed");
		break;
	case 7:
		printf("\nNew Game");
		Scene->play_Mode = -1;
		Scene->GameScene->newGame();
		updateMessage();
		break;
	case 8:
		printf("\n Undo");
		Scene->GameScene->undo();
		updateMessage();
		break;
	case 9:
		printf("\n Room Changed");
		Scene->setGraph(Graphs[graph]);
		break;
	case 10:
		printf("\n Game Mode Changed");
		break;
	default:
		break;
	}
}

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	if(Scene->play_Mode == -1 || Scene->GameScene->gameState()|| !Scene->GameScene->getSocket()->isActive())
		return;

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) 
{

	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("\nPosition: ");
		printf("%d ",selected[0]);
		printf("%d ",selected[1]);
		printf("\n");

		if(Scene->play_Mode == 0){
			if(Scene->GameScene->checkPiece(2*selected[0],2*selected[1]))
			{
				Scene->GameScene->addPiece(selected[0],selected[1]);
				Scene->play_Mode = -1;

				string m;
				if((m = Scene->GameScene->checkGame()) != "")
				{
					Scene->play_Mode = -1;
					messageDisplay->set_text(m.c_str());
				}
				else
					updateMessage();

				if(Scene->GameScene->bot == 1)
				{
						Scene->GameScene->playBot();
						updateMessage();
				}
			}
		}
		else if(Scene->play_Mode == 1){
			if(inicial_move_x == -1)
			{
				inicial_move_x = selected[0];
				inicial_move_y = selected[1];
			}
			else if(Scene->GameScene->checkMove(2*inicial_move_x,2*inicial_move_y,2*selected[0],2*selected[1],Scene->wallPosition))
			{
				Scene->GameScene->movePiece(inicial_move_x,inicial_move_y,selected[0],selected[1],Scene->wallPosition);
				Scene->play_Mode = -1;
				inicial_move_x = -1;
				inicial_move_y = -1;

				string m;
				if((m = Scene->GameScene->checkGame()) != "")
				{
					Scene->play_Mode = -1;
					messageDisplay->set_text(m.c_str());
				}
				else
					updateMessage();

				if(Scene->GameScene->bot == 1)
				{
						Scene->GameScene->playBot();
						updateMessage();
				}

			}
			else
			{
				inicial_move_x = -1;
				inicial_move_y = -1;
			}
		}


	}
}

void TPinterface::updateMessage(){

	if(Scene->GameScene->gameState())
		return;

	if(Scene->GameScene->getPlayer())
		messageDisplay->set_text("Player A");
	else
		messageDisplay->set_text("Player B");
}