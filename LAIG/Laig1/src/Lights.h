#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "CGFlight.h"
#include "CGFobject.h"
#include <string>

class Light: public CGFlight {
	string id_s;
	string type;
	bool marker;
	
public:
	int active;
	Light();
	Light(string id,unsigned int iID, float* p, string t, bool m);
	bool getMarker();
	string getid_s();
	bool getEnable();
	void turnOn();
	void turnOff();
	virtual void updateL();

};


class SpotLight : public Light{
	float target[3];
	float exponent;

public:
	SpotLight(string id_s,unsigned int iID, float* p, string t, bool m, float*targ, float exp, float angle);
	void updateL();

};



#endif