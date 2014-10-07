#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"

class Appearance
{
	CGFappearance* app;
	string id, textureref;
public:
	Appearance(string id, string textureref, CGFappearance* app);
	Appearance(string ID);	
	CGFappearance* getApp();
	string getAppId();
	float* getEmissive();
	void setEmissive(float e[4]);
	void apply();
	void setAppearance(CGFappearance* a);
};

#endif