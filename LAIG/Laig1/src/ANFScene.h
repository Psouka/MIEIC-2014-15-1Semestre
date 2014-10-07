#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "tinyxml.h"
#include "Cameras.h"
#include "Globals.h"
#include "Lights.h"
#include "Textures.h"
#include "Appearance.h"

class ANFScene
{
public:
	ANFScene(char *filename);
	~ANFScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	int parseGlobals();
	int parseCameras();
	int parseLights();
	int parseTextures();
	int parseAppearences();
	void parseNodes();
	void parseGraph();
	string findTexture(string id);
	
protected:
	vector <Camera*> cameras;
	vector <Light*> lights;
	vector <Texture*> textures;
	vector <Appearance*> Apps;
	Globals ANFGlobals;

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement; 
	TiXmlElement* lightElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* nodesElement;
    TiXmlElement* graphElement;

};
#endif