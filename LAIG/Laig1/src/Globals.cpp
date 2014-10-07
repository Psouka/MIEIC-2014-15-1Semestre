#include "Globals.h"

Globals :: Globals(){
}




void Globals :: updateDraw(GLenum m, GLenum s, float *b){
	drawMode = m;
	shading =s;
	background[0] = b[0];
	background[1] = b[1];
	background[2] = b[2];
	background[3] = b[3];
}
void Globals :: updateCulli(GLenum f, GLenum o){
	face = f;
	order = o;
}
void Globals :: updateLight(bool d, bool l, bool e, float *a){
	doublesided = d;
	local = l;
	enabled = e;
	ambient[0] = a[0];
	ambient[1] = a[1];
	ambient[2] = a[2];
	ambient[3] = a[3];
}