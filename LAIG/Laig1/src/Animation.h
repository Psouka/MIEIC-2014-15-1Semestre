#ifndef _ANIMATION_
#define _ANIMATION_

#include "CGFscene.h"

class Animation {
	string id;
	float span;

public:
	Animation(string id);
};

class LinearAnimation : public Animation {
	float* controlPoint;

public:
	LinearAnimation(string id, float span, string type, float* controlPoint);
};

class CircularAnimation : public Animation {

	float* center[3], radius, startAng, rotAng;

public:

	CircularAnimation(string id, float span, string type, float* center, float radius, float startAng, float rotAng);
};

#endif