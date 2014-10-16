#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "CGFlight.h"
#include "CGFobject.h"
#include <string>

class Light : public CGFlight
{
	string id;
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
	float exponent, angle;

public:
	SpotLight(string id,unsigned int iID, float* p, string t, bool m, float*targ, float exp, float angle);

};


Light :: Light()
: CGFlight(NULL,NULL){
}

Light :: Light(string id,unsigned int iID,float *p,string t, bool m)
:CGFlight(iID,p){
	this->id = id;
	this->marker = m;
	this-> type = t;
}

bool Light::getMarker(){
	return marker;
}


SpotLight :: SpotLight(string id,unsigned int iID, float* p, string t,bool m, float*targ, float exp, float angle)
	: Light(id,iID,p,t,m)
{
	float direction[3] = {(target[0]-position[0]),(target[1]-position[1]),(target[2]-position[2])};
	this->direction[0] = direction[0];
	this->direction[1] = direction[1];
	this->direction[2] = direction[2];

	exponent = exp;
	this->angle = angle;
}

#endif