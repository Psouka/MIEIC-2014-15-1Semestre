#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"

class Appearance
{
	CGFappearance* app;
	string appearanceid;
	float emissive[4];
public:
	Appearance(string ID);	
	CGFappearance* getApp();
	string getAppId();
	float* getEmissive();
	void setEmissive(float e[4]);
	void apply();
	void setAppearance(CGFappearance* a);
	float texlength_s, texlength_t;
};

#endif