#include <vector>
#include <string>
#include <iostream>
#include "Primitives.h"
#define PI 3.14159265359
Primitives :: Primitives(){

}

Rectangle :: Rectangle(float x1,float y1, float x2, float y2){

	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Rectangle :: draw(){
	glPushMatrix();
glNormal3f(0,0,1);
	glBegin(GL_POLYGON);
		glTexCoord2f(0,0);
		glVertex3d(x1,y1,0);

		glTexCoord2f(1,0);
		glVertex3d(x2,y1,0);
		
		glTexCoord2f(1,1);
		glVertex3d(x2,y2,0);
		
		glTexCoord2f(0,1);
		glVertex3d(x1,y2,0);
	glEnd();
	glPopMatrix();
}

Triangle :: Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3){

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

void Triangle :: draw(){
		glPushMatrix();
		//glNormal3f(x,y,z);
	glBegin(GL_TRIANGLES);
			glTexCoord2f(0,0);
			glVertex3f(x1,y1,z1);
			glTexCoord2f(1,0);
			glVertex3f(x2,y2,z2);
			glTexCoord2f(1,1);
			glVertex3f(x3,y3,z3);
	glEnd();
}

Cylinder :: Cylinder(float base, float top, float height, int slices, int stacks){
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	this->angle = 2 * acos(-1.0) / slices;
}

void Cylinder :: draw(){
	glPushMatrix();
	glRotated(90,1,0,0);


	// Base

	glBegin(GL_POLYGON);
	glNormal3d(0, -1, 0);
	for (int i = 0; i < slices; i++) {
		glTexCoord2d((cos(angle * i) / 2) + 0.5, (sin(angle * i) / 2) + 0.5);
		glVertex3d(cos(angle * i + PI/2)*base, 0, sin(angle * i + PI/2)*base);
	}
	glEnd();

	// Topo

	glBegin(GL_POLYGON);
	glNormal3d(0, 1, 0);
	for (int i = slices; i > 0; i--) {
		glTexCoord2d((cos(angle * i) / 2) - 0.5, (sin(angle * i) / 2) - 0.5);
		glVertex3d(cos(angle * i + PI/2)*top, height, sin(angle * i + PI/2)*top);
	}
	glEnd();

	glPopMatrix();

	// Lados
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	gluCylinder(qObj, base, top, height, slices, stacks);
}

Sphere :: Sphere(float radius, int slices, int stacks){
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

void Sphere :: draw(){
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);

	gluSphere(qObj, radius, slices, stacks);
}

Torus :: Torus(float inner, float outer, int slices, int loops){
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void Torus :: draw(){
	glutSolidTorus(inner, outer, slices, loops);
}