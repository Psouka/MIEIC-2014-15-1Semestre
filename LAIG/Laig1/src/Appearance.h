#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"

class Appearance
{
	CGFappearance* app;
	string id, textureref;
public:
	Appearance(string id, string textureref, CGFappearance* app);
	CGFappearance* getApp();
	string getAppId();
	void setAppearance(CGFappearance* a);
};

#endif