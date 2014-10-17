#include "Appearance.h"
#include <vector>
#include <string>
#include <iostream>


Appearance :: Appearance(float*a,float *d,float *s, float shi, string id, string textureref)
:CGFappearance(a,d,s,shi){
	this->id = id;
	this->textureref = textureref;
}

string  Appearance ::getAppId(){
return id;
}

void Appearance ::setAppTexture(Texture * t){
	this->setTexture(t);
	APPTexture = t;
}