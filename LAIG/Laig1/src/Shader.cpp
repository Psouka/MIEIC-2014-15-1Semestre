#include <GL/glew.h>
#include "Shader.h"

Shader :: Shader(CGFtexture *Texture)
:Texture(Texture){

init("data/shader.vert", "data/shader.frag");

	CGFshader::bind();

	// get the uniform location for the sampler
	baseTextureLoc = glGetUniformLocation(id(), "baseTexture");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseTextureLoc, 0);

	// initialize in memory
	this->startTime = 0.0;
	this->deltaTime = 0.0;
	this->wind = 0;

	windLoc = glGetUniformLocation(id(), "wind");
	glUniform1f(windLoc, wind);

	deltaTimeLoc = glGetUniformLocation(id(), "deltaTime");
	glUniform1f(deltaTimeLoc, deltaTime);

	CGFshader::unbind();

}


void Shader::bind()
{
	CGFshader::bind();

	// update uniforms
	glUniform1f(windLoc, wind);
	glUniform1f(deltaTimeLoc, deltaTime);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	Texture->apply();
}

void Shader::unbind(){
	CGFshader::unbind();
}

void Shader::setTime(float time)
{
	if(this->startTime == 0)
	{
		this->startTime = time;
	}
	else
	{
		this->deltaTime = time - startTime;
	}
}