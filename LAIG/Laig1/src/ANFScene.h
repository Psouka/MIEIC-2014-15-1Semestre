#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "tinyxml.h"
#include "Cameras.h"
#include "Globals.h"
#include "Lights.h"
#include "Textures.h"
#include "Appearance.h"
#include "Graph.h"
//#include "TPinterface.h"

class ANFScene : public CGFscene
{
public:
	//interface
	int drawMode;
	int Active_Camera;
	ANFScene(){}
	ANFScene(char *filename);
	~ANFScene();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	int parseGlobals();
	int parseCameras();
	int parseLights();
	int parseTextures();
	int parseAppearences();
	int parseGraph();
	Texture *findTexture(string id);
	Appearance* findApp(string id);
	vector<Node*> getNodes(vector<string> n);
	void init();
	void display();
	void process(Node* node);
	void FillChildren(Node* node);
	vector <Light*> getLights();
	vector <Camera*> getCameras();
	
	
protected:
	vector <Camera*> cameras;
	vector <Light*> lights;
	vector <Texture*> textures;
	vector <Appearance*> apps;
	Globals ANFGlobals;
	Graph* ANFGraph;

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement; 
	TiXmlElement* lightElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
    TiXmlElement* graphElement;

};
#endif