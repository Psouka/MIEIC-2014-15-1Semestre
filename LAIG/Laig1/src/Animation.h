#ifndef _ANIMATION_
#define _ANIMATION_

#include "CGFscene.h"
#include <string>
#include <vector>
using namespace std;

class Animation {
	string id;
	float span, transX, transY, transZ;

public:
	Animation(string id,float span);
	string getId();
};

class LinearAnimation : public Animation {
	vector<vector<float>> controlPoint;
public:
	LinearAnimation(string id, float span, vector<vector<float>> controlPoint);
	void init(unsigned long t);
	void update(unsigned long t);
	void apply();
};

class CircularAnimation : public Animation {
	float center[3], radius, startAng, rotAng;
public:
	CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng);
	void init(unsigned long t);
	void update(unsigned long t);
	void apply();
};

#endif