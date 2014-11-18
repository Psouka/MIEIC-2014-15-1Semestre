#ifndef _ANIMATION_
#define _ANIMATION_

#include "CGFscene.h"
#include <string>
#include <vector>
using namespace std;

class Animation {

public:
	Animation(string id,float span);
	string getId();
	virtual void update(unsigned long t) = 0;
	virtual void apply() = 0;

protected:
	float transX, transY, transZ, time, span;
	string id;
};

class LinearAnimation:public Animation {
	vector<vector<float>> controlPoint;
	float distance, rotation;
	int idPC;

public:
	LinearAnimation(string id, float span, vector<vector<float>> controlPoint);
	void init(unsigned long t);
	void update(unsigned long t);
	void apply();
};

class CircularAnimation:public Animation {
	float center[3], radius, startAng, rotAng;
public:
	CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng);
	void init(unsigned long t);
	void update(unsigned long t);
	void apply();
};

class NoAnimation:public Animation{

public:
	NoAnimation();
	virtual void update(unsigned long t);
	virtual void apply();
};

#endif