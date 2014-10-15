#include "Textures.h"


Texture :: Texture(string i, string f, float tex_s,float tex_t){
id = i;
file = f;
texlength_s = tex_s;
texlength_t = tex_t;
CGFtextura = new CGFtexture(file);
}

Texture :: Texture(){}


CGFtexture * Texture :: getTexture(){

	return CGFtextura;
}


string Texture ::getFile(){
return file;
}

string Texture ::getId(){
	return id;
}