#include "Textures.h"


Texture::Texture(): CGFtexture() {

}

Texture::~Texture(){
}


Texture::Texture(string i, string f, float tex_s,float tex_t): CGFtexture(f) {
	id = i;
	file = f;
	this->tex_s =  tex_s;
	this->tex_t = tex_t;
}

Texture::Texture(string id): CGFtexture() {
	this->id = id;
}

string Texture::getFile() {
	return file;
}

string Texture::getId() {
	return id;
}

int Texture::getTexId() {
	return texID;
}