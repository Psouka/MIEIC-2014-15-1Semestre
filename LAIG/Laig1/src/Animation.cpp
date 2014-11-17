#include "Animation.h"

Animation:: Animation(string id,float span)
	:id(id),span(span){

}

string Animation:: getId(){
	return id;
}

LinearAnimation::LinearAnimation(string id, float span, vector<vector<float>> controlPoint)
	:Animation(id,span),controlPoint(controlPoint){

}

void LinearAnimation::update(unsigned long t) {

}

void LinearAnimation::init(unsigned long t) {

}

CircularAnimation :: CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng)
	:Animation(id,span),radius(radius),startAng(startAng),rotAng(rotAng) {

		this->center[0] = center[0];
		this->center[1] = center[1];
		this->center[2] = center[2];
}

void CircularAnimation::update(unsigned long t) {

}

void CircularAnimation::init(unsigned long t) {

}

