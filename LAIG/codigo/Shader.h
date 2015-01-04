#ifndef _SHADER_H_
#define _SHADER_H_

#include "CGFshader.h"
#include "CGFapplication.h"

class Shader : public CGFshader{
	CGFtexture *Texture;
	int windLoc;
	float deltaTime;
	int deltaTimeLoc;
	float startTime;
public:
	~Shader();
	Shader(CGFtexture *Texture);
	virtual void bind();
	virtual void unbind();
	void setTime(float time);
	int wind;
};

#endif