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
	virtual void init(unsigned long t) = 0;
	bool getStop();
	vector<float> getFinalPos();
	vector<float> getInitialPos();


protected:
	float time, span, distance, rotation;
	string id;
	bool stop, start;
	vector<float> finalPos, initialPos;

};

class LinearAnimation:public Animation {
	vector<vector<float>> controlPoint;
	int idPC;
	float transX, transY, transZ;

public:
	LinearAnimation(string id, float span, vector<vector<float>> controlPoint);
	void update(unsigned long t);
	void apply();
	void init(unsigned long t);
	vector<float> getTrans() {
		vector<float> temp;
		temp.push_back(transX);
		temp.push_back(transY);
		temp.push_back(transZ);
	}
};

class CircularAnimation:public Animation {
	float center[3], radius, startAng, rotAng, velAng;
public:
	CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng);
	void update(unsigned long t);
	void apply();
	void init(unsigned long t);
	float getRotation() {
		return rotation;
	}
	float* getCenter() {
		return center;
	}
	float getRadius() {
		return radius;
	}
};

class NoAnimation:public Animation{

public:
	NoAnimation();
	virtual void update(unsigned long t);
	virtual void apply();
	void init(unsigned long t);
};

#endif