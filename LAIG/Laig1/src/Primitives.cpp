#include <vector>
#include <string>
#include <iostream>
#include "Primitives.h"

#define PI 3.14159265359


Primitives::Primitives(): CGFobject() {

}

Rectangle::Rectangle(float x1,float y1, float x2, float y2): Primitives() {

	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Rectangle::draw(Texture* t) {
	float xT,yT;
	if(t->getId() != "NULL")
	{
		float lenT = t->tex_s, heiT = t->tex_s, lenO = x2-x1,heiO = y2-y1;
		xT = lenO/lenT;
		yT = heiO/heiT;
	}
	else
		xT = yT = 1;

	glPushMatrix();
	glBegin(GL_POLYGON);

	glNormal3f(x1, y1,1);
	glTexCoord2f(0,0);
	glVertex2f(x1, y1);

	glNormal3f(x2, y1,1);
	glTexCoord2f(xT,0);
	glVertex2f(x2, y1);

	glNormal3f(x2, y2,1);
	glTexCoord2f(xT,yT);
	glVertex2f(x2, y2);

	glNormal3f(x1, y1,1);
	glTexCoord2f(0,yT);
	glVertex2f(x1, y2);
	glEnd();
	glPopMatrix();
}

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3): Primitives() {

	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->z1 = z1;
	this->z2 = z2;
	this->z3 = z3;
}

void Triangle::draw(Texture* t) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0,0);
	glVertex3f(x1,y1,z1);
	glTexCoord2f(1,0);
	glVertex3f(x2,y2,z2);
	glTexCoord2f(0.5,1);
	glVertex3f(x3,y3,z3);
	glEnd();
	glPopMatrix();
}

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks): Primitives() {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	this->angle = 2 * acos(-1.0) / slices;
}

void Cylinder::draw(Texture* t) {

	GLUquadricObj *disk, *disk1;
	GLUquadricObj *cylind;

	cylind = gluNewQuadric();
	disk = gluNewQuadric();
	disk1 = gluNewQuadric();

	//Bot
	glPushMatrix();
	glRotatef(180,0,1,0);
	gluQuadricNormals(disk, GLU_SMOOTH);
	gluQuadricTexture(disk, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	if(t != NULL) {
		glBindTexture(GL_TEXTURE_2D, t->getTexId());
	}
	gluDisk(disk, 0, base, slices, slices);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	//Cilindro
	glPushMatrix();
	gluQuadricNormals(cylind, GLU_SMOOTH);
	gluQuadricTexture(cylind, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	if(t != NULL) {
		glBindTexture(GL_TEXTURE_2D, t->getTexId());
	}
	gluCylinder(cylind, base, top, height, slices, stacks);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	//Top
	glPushMatrix();
	glTranslatef(0,0,this->height);
	gluQuadricNormals(disk1, GLU_SMOOTH);
	gluQuadricTexture(disk1, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	if(t != NULL) {
		glBindTexture(GL_TEXTURE_2D, t->getTexId());
	}
	gluDisk(disk1, 0, top, slices, slices);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
Sphere::Sphere(float radius, int slices, int stacks): Primitives() {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

void Sphere::draw(Texture* t) {
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	if(t != NULL) {
		glBindTexture(GL_TEXTURE_2D, t->getTexId());
	}
	gluSphere(qObj, radius, slices, stacks);
}

Torus::Torus(float inner, float outer, int slices, int loops): Primitives() {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}



void Torus::draw(Texture* t)  {
	float vNormal[3];
	double majorStep = 2.0f*PI / loops;
	double minorStep = 2.0f*PI / slices;
	int i, j;

	for (i=0; i<loops; ++i) 
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat) cos(a0);
		GLfloat y0 = (GLfloat) sin(a0);
		GLfloat x1 = (GLfloat) cos(a1);
		GLfloat y1 = (GLfloat) sin(a1);

		glBegin(GL_TRIANGLE_STRIP);
		for (j=0; j<=slices; ++j) 
		{
			double b = j * minorStep;
			GLfloat c = (GLfloat) cos(b);
			GLfloat r = inner * c + outer;
			GLfloat z = inner * (GLfloat) sin(b);

			// First point
			glTexCoord2f((float)(i)/(float)(loops), (float)(j)/(float)(slices));
			vNormal[0] = x0*c;
			vNormal[1] = y0*c;
			vNormal[2] = z/inner;
			// gltNormalizeVector(vNormal);
			glNormal3fv(vNormal);
			glVertex3f(x0*r, y0*r, z);

			glTexCoord2f((float)(i+1)/(float)(loops), (float)(j)/(float)(slices));
			vNormal[0] = x1*c;
			vNormal[1] = y1*c;
			vNormal[2] = z/inner;
			glNormal3fv(vNormal);
			glVertex3f(x1*r, y1*r, z);
		}
		glEnd();
	}
}