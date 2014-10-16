#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "CGFobject.h"
#include <string>
#include "CGFtexture.h"
using namespace std;

class Texture
{
	string id, file;
	float texlength_s, texlength_t;
	CGFtexture *CGFtextura;
	
	
public:
	Texture(string i, string f, float tex_s,float tex_t);
	Texture();
	CGFtexture * getTexture();
	string getFile();
	string getId();

};


#endif