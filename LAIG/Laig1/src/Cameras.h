#ifndef _CAMERAS_H_
#define _CAMERAS_H_


#include "CGFapplication.h"
#include "CGFcamera.h"

using namespace std;

class Camera : public CGFcamera
{
protected:
	float nearP;
	float farP;
public:
	string cameraid;
	void setPosition(float *p);
	void setTarget(float *t);
	Camera(string id);
	float getnearP();
	float getfarP();

};

class PerspectiveCamera : public Camera {
	float angle;
public:
	PerspectiveCamera(string id, float nearP, float farP, float angle);
	float getAngle();
	void applyView();
	void updateProjectionMatrix (int width, int height);
};

class OrthoCamera : public Camera {
	float left;
	float right;
	float top;
	float bottom;
	char direction;
public:
	OrthoCamera(string id, float nearP, float farP, float left, float right, float top, float bottom,char direction);
	void applyView();
	void updateProjectionMatrix (int width, int height);
};
#endif
