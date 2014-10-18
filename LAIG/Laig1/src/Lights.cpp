#include "Lights.h"


Light :: Light()
	: CGFlight(NULL,NULL){
}

Light :: Light(string id_s,unsigned int iID,float *p,string t, bool m)
	:CGFlight(iID,p){
		this->id_s = id_s;
		this->marker = m;
		this-> type = t;
		this->position[3] = 0;
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
	
	this->position[3] = 1;
	exponent = exp;
	this->angle = angle;

}

void SpotLight :: updateL(){
	glLightf(this->id,GL_SPOT_EXPONENT,exponent);
	this->update();
}
