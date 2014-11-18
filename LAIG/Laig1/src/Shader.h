#ifndef _SHADER_H_
#define _SHADER_H_

#include "CGFshader.h"
#include "CGFapplication.h"

class Shader : public CGFshader {
	friend class Flag;
public:
	Shader();
	virtual void bind(CGFtexture *Texture);
	virtual void unbind();

	void setTime(float time);

protected:
	int baseTextureLoc;
	int wind;
	int windLoc;
	float deltaTime;
	int deltaTimeLoc;
	float startTime;
};

#endif