#include "Appearance.h"
#include <vector>
#include <string>
#include <iostream>
#include "Appearance.h"


Appearance :: Appearance(string id, string textureref, CGFappearance* app){
	this->id = id;
	this->textureref = textureref;
	this->app = app;

}


CGFappearance* Appearance :: getApp(){
return app;
}


void Appearance ::setAppearance(CGFappearance* a){
app = a;
}

string  Appearance ::getAppId(){
return id;
}