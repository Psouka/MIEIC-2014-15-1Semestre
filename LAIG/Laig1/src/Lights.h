#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "CGFlight.h"
#include "CGFobject.h"
#include <string>

class Light : public CGFlight
{
	string id_s;
	string type;
	bool marker;

public:
	Light();
	Light(string id,unsigned int iID, float* p, string t, bool m);
	CGFlight * getLight();
	bool getMarker();

};


class SpotLight : public Light{
	float target[3];
	float exponent;

public:
	SpotLight(string id_s,unsigned int iID, float* p, string t, bool m, float*targ, float exp, float angle);

};


Light :: Light()
	: CGFlight(NULL,NULL){
}

Light :: Light(string id_s,unsigned int iID,float *p,string t, bool m)
	:CGFlight(iID,p){
		this->id_s = id_s;
		this->marker = m;
		this-> type = t;
}

bool Light::getMarker(){
	return marker;
}


SpotLight :: SpotLight(string id_s,unsigned int iID, float* p, string t,bool m, float*targ, float exp, float angle)
	: Light(id_s,iID,p,t,m)
{

	target[0] = targ[0];
	target[1] = targ[1];
	target[2] = targ[2];

	this->direction[0] = target[0]-position[0];
	this->direction[1] = target[1]-position[1];
	this->direction[2] = target[2]-position[2];

	exponent = exp;
	this->angle = angle;
	glLightf(this->id,GL_SPOT_EXPONENT,exponent);
	glLightf(this->id,GL_SPOT_CUTOFF,angle);
	glLightfv(this->id,GL_SPOT_DIRECTION,target);


}

#endif