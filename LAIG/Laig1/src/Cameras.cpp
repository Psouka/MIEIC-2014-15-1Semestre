#include "Cameras.h"

Camera::Camera(string id)
	:CGFcamera()
{
	cameraid=id;
}

PerspectiveCamera::PerspectiveCamera(string id, float nearP, float farP, float angle) : Camera(id)
{
	this->nearP=nearP;
	this->farP=farP;
	this->angle=angle;
}

void PerspectiveCamera:: applyView(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, 1.0, nearP, farP);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position[0], position[1], position[2], target[0], target[1], target[2], 0, 1, 0);
}


void OrthoCamera:: applyView(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, nearP, farP);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	switch(direction)
	{
	case 'x':
		gluLookAt(1, 0.0, 0.0, farP, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 'y':
		gluLookAt(0.0, 1, 0.0, 0, -farP, 0.0, 0.0, 0.0, -1.0);
		break;
	case 'z':
		gluLookAt(0.0, 0.0, 1, 0.0, 0.0, -farP, 0.0, 1.0, 0.0);
		break;
	default:
		break;
	}
}


OrthoCamera::OrthoCamera(string id, float nearP, float farP, float left, float right, float top, float bottom,char direction) : Camera(id)
{
	this->nearP=nearP;
	this->farP=farP;
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
	this->direction = direction;
}

void Camera :: setPosition(float *p){
	position[0] = p[0];
	position[1] = p[1];
	position[2] = p[2];
}


void Camera :: setTarget(float *t){
	target[0] = t[0];
	target[1] = t[1];
	target[2] = t[2];
}
