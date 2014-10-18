#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"
#include "Textures.h"

class Appearance : public CGFappearance
{
	string id, textureref;
public:
	Texture *APPTexture;
	Appearance(float*a,float *d,float *s, float shi, string id, string textureref);
	Appearance(string text_ref);
	string getAppId();
	string get_text_ref();
	void setAppTexture(Texture * t);
};

#endif