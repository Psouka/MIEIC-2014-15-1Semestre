#include "Appearance.h"
#include <vector>
#include <string>
#include <iostream>


Appearance :: Appearance(float*a,float *d,float *s, float shi, string id, string textureref)
:CGFappearance(a,d,s,shi){
	this->id = id;
	this->textureref = textureref;
}

Appearance ::Appearance(string text_ref){
	this->textureref = text_ref;
}

string  Appearance ::get_text_ref(){
return textureref;
}


string  Appearance ::getAppId(){
return id;
}

void Appearance ::setAppTexture(Texture * t){
	if(t->getId() != "NULL"){
	this->setTexture(t);
	this->setTextureWrap(GL_REPEAT,GL_REPEAT);}
	APPTexture = t;
}