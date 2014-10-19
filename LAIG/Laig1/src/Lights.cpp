#include "Lights.h"


Light :: Light()
	: CGFlight(NULL,NULL){
}

Light :: Light(string id_s,unsigned int iID,float *p,string t, bool m)
	:CGFlight(iID,p){
		this->id_s = id_s;
		this->marker = m;
		this-> type = t;
		this->position[3] = 1;
		this->angle = 180;
}

bool Light::getMarker(){
	return marker;
}

string Light::getid_s(){
	return id_s;
}

bool Light::getEnable(){
return enabled;
}

void Light::turnOn(){
	active = 1;
	this->enable();
}
void Light::turnOff(){
	active = 0;
	this->disable();
}
void Light :: updateL(){
	this->update();
}

SpotLight :: SpotLight(string id_s,unsigned int iID, float* p, string t,bool m, float*targ, float exp, float angle)
	: Light(id_s,iID,p,t,m)
{

	target[0] = targ[0];
	target[1] = targ[1];
	target[2] = targ[2];

	direction[0] =	target[0] - position[0];
	direction[1] = target[1] - position[1];
	direction[2] = target[2] - position[2];
	
	float normal = sqrt( pow(direction[0],2) + pow(direction[1],2) + pow(direction[2],2));

	direction[0] =	direction[0] / normal;
	direction[1] = direction[1] / normal;
	direction[2] = direction[2] / normal;
	exponent = exp;
	this->angle = angle;

}

void SpotLight :: updateL(){
	glLightf(this->id,GL_SPOT_EXPONENT,exponent);
	glLightf(this->id,GL_SPOT_CUTOFF,angle);
	glLightfv(this->id,GL_SPOT_DIRECTION,target);
	this->update();
}
