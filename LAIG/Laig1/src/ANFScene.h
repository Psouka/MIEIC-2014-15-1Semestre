#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "tinyxml.h"

class ANFScene
{
public:
	ANFScene(char *filename);
	~ANFScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	void parseGlobals();
	void parseCameras();
	void parseLights();
	void parseTextures();
	void parseAppearences();
	void parseNodes();
	void parseGraph();
	
protected:

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement; 
	TiXmlElement* lightsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* nodesElement;
    TiXmlElement* graphElement;

};
#endif