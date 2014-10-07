#include "Cameras.h"

Camera::Camera(string id)
{
	cameraid=id;
	initial = false;
}

PerspectiveCamera::PerspectiveCamera(string id, float nearP, float farP, float angle) : Camera(id)
{
	this->nearP=nearP;
	this->farP=farP;
	this->angle=angle;
}

OrthoCamera::OrthoCamera(string id, float nearP, float farP, float left, float right, float top, float bottom) : Camera(id)
{
	this->nearP=nearP;
	this->farP=farP;
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
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


void Camera :: setInitial(bool i){
	initial = i;
}