#include <GL/glew.h>
#include "Shader.h"

Shader :: ~Shader(){
	delete(Texture);
}

Shader :: Shader(CGFtexture *Texture)
	:Texture(Texture){

		init("shaders/flagShader.vert", "shaders/flagShader.frag");

		CGFshader::bind();
		// initialize in memory
		this->startTime = 0.0;
		this->deltaTime = 0.0;
		this->wind = 5;

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
	if(startTime == 0)
	{
		startTime = time;
	}
	else
	{
		deltaTime = time - startTime;
	}
}