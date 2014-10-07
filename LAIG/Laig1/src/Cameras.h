#ifndef _CAMERAS_H_
#define _CAMERAS_H_


#include "CGFapplication.h"
#include "CGFcamera.h"

using namespace std;

class Camera
{
protected:
	bool initial;
	string cameraid;
	float position[3];
	float target[3];
	float nearP;
	float farP;
public:
	void setPosition(float *p);
	void setTarget(float *t);
	void setInitial(bool i);
	Camera(string id);
	float getnearP();
	float getfarP();

};

class PerspectiveCamera : public Camera {
	float angle;
public:
	PerspectiveCamera(string id, float nearP, float farP, float angle);
	float getAngle();
};

class OrthoCamera : public Camera {
	float left;
	float right;
	float top;
	float bottom;
public:
	OrthoCamera(string id, float nearP, float farP, float left, float right, float top, float bottom);
};
#endif
