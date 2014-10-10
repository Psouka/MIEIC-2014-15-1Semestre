#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include "GL\gl.h"
#include <string>

using namespace std;

class Globals{
public:
	//drawing
	GLenum drawMode, shading;
	float background[4];
	//culling
	GLenum face, order;
	//Lightning
	bool doublesided , local , enabled;
	float ambient[4];

	Globals();
	void updateDraw(GLenum m, GLenum s, float *b);
	void updateCulli(GLenum f, GLenum o);
	void updateLight(bool d, bool l, bool e, float *a);

};

#endif

/*
<drawing mode="ss" shading="ss" background="ff ff ff ff" />
 
        <!-- Parametros de culling -->
        <!-- Valores para cullface: "none", "back" , "front" ou "both" -->
        <!-- Valores para cullorder : "ccw" ou "cw" -->
        <culling face="ss" order="ss" />
 
        <!-- Parametros de iluminacao; seguem os parametros do OpenGL  -->
        <lighting doublesided="tt" local="tt" enabled="tt" ambient="ff ff ff ff" />



*/
