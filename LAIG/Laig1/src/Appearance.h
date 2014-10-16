#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "CGFscene.h"

class Appearance : public CGFappearance
{
	string id, textureref;
public:
	Appearance(float*a,float *d,float *s, float shi, string id, string textureref);
	string getAppId();
};

#endif