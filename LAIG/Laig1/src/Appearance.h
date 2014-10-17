#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"
#include "Textures.h"

class Appearance : public CGFappearance
{
	string id, textureref;
	Texture *APPTexture;
public:
	Appearance(float*a,float *d,float *s, float shi, string id, string textureref);
	string getAppId();
	void setAppTexture(Texture * t);
};

#endif