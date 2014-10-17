#include "Textures.h"


Texture :: Texture(string i, string f, float tex_s,float tex_t)
	:CGFtexture(f){
		id = i;
		file = f;
		this->tex_s =  tex_s;
		this->tex_t = tex_t;
}

Texture :: Texture()
	:CGFtexture(NULL){}

string Texture ::getFile(){
	return file;
}

string Texture ::getId(){
	return id;
}