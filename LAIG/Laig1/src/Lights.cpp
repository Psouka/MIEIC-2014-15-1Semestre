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



SpotLight :: SpotLight(string id_s,unsigned int iID, float* p, string t,bool m, float*targ, float exp, float angle)
	: Light(id_s,iID,p,t,m)
{

	target[0] = targ[0];
	target[1] = targ[1];
	target[2] = targ[2];
	
	this->position[3] = 1;
//	this->direction[0] = target[0]-position[0];
//	this->direction[1] = target[1]-position[1];
//	this->direction[2] = target[2]-position[2];
	exponent = exp;
//	this->angle = angle;

}