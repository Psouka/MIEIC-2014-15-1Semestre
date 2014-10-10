#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "tinyxml.h"
#include "Cameras.h"
#include "Globals.h"
#include "Lights.h"
#include "Textures.h"
#include "Appearance.h"
#include "Graph.h"

class ANFScene : public CGFscene
{
public:
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
	string findTexture(string id);
	CGFappearance* findApp(string id);
	void init();
	void display();
	
	
protected:
	vector <Camera*> cameras;
	vector <Light*> lights;
	vector <Texture*> textures;
	vector <Appearance*> apps;
	Globals ANFGlobals;
	Graph ANFGraph;

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement; 
	TiXmlElement* lightElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
    TiXmlElement* graphElement;

};
#endif