#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include <string>
#include "CGFtexture.h"
using namespace std;

class Texture : public CGFtexture
{
	string id, file;
	
public:
	float tex_s, tex_t;
	Texture(string id);
	Texture(string i, string f, float tex_s,float tex_t);
	Texture();
	string getFile();
	string getId();

};


#endif