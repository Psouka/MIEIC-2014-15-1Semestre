#ifndef _ANFSCENE_H_
#define _ANFSCENE_H_

#include "tinyxml.h"
#include "Cameras.h"
#include "Globals.h"
#include "Lights.h"
#include "Textures.h"
#include "Appearance.h"
#include "Graph.h"
#include "Animation.h"

class ANFScene:public CGFscene {
public:
	//interface
	int globalWind;
	int drawMode;
	int Active_Camera;
	ANFScene() {}
	ANFScene(char *filename);
	~ANFScene();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	int parseGlobals();
	int parseCameras();
	int parseLights();
	int parseTextures();
	int parseAppearences();
	int parseGraph();
	int parseAnimations();
	Texture *findTexture(string id);
	Appearance* findApp(string id);
	Animation* findAnimation(string id);
	vector<Node*> getNodes(vector<string> n);
	void init();
	void display();
	void update(unsigned long t);
	void process(Node* node,Appearance * app);
	void FillChildren(Node* node);
	vector <Light*> getLights();
	vector <Camera*> getCameras();
	void changeCamera();
	void setGlobalWind();

protected:
	vector <Camera*> cameras;
	vector <Light*> lights;
	vector <Texture*> textures;
	vector <Appearance*> apps;
	vector <Animation*> anim;
	vector <Flag *> Flags;

	Globals ANFGlobals;

	Graph* ANFGraph;

	TiXmlDocument* doc;

	TiXmlElement* globalsElement; 
	TiXmlElement* camerasElement; 
	TiXmlElement* lightElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* graphElement;
	TiXmlElement* animationElement;

};
#endif