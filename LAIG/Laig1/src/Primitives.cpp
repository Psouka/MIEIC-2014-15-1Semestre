#include <vector>
#include <string>
#include <iostream>
#include "Primitives.h"
#define PI 3.14159265359
Primitives :: Primitives()
	:CGFobject(){

}

Rectangle :: Rectangle(float x1,float y1, float x2, float y2)
	:Primitives(){

		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
}

void Rectangle :: draw(Texture* t){
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

Triangle :: Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
	:Primitives(){

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

void Triangle :: draw(Texture* t){
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

Cylinder :: Cylinder(float base, float top, float height, int slices, int stacks)
	:Primitives(){
		this->base = base;
		this->top = top;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
		this->angle = 2 * acos(-1.0) / slices;
}

void Cylinder :: draw(Texture* t){
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

Sphere :: Sphere(float radius, int slices, int stacks)
	:Primitives(){
		this->radius = radius;
		this->slices = slices;
		this->stacks = stacks;
}

void Sphere :: draw(Texture* t){
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricTexture(qObj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	gluSphere(qObj, radius, slices, stacks);
}

Torus :: Torus(float inner, float outer, int slices, int loops)
	:Primitives(){
		this->inner = inner;
		this->outer = outer;
		this->slices = slices;
		this->loops = loops;
}

void Torus :: draw(Texture* t){
		int i, j;
		GLfloat theta, phi, theta1;
		GLfloat cosTheta, sinTheta;
		GLfloat cosTheta1, sinTheta1;
		GLfloat ringDelta, sideDelta;

		ringDelta = 2.0 * PI / loops;
		sideDelta = 2.0 * PI / slices;

		theta = 0.0;
		cosTheta = 1.0;
		sinTheta = 0.0;
		for (i = loops - 1; i >= 0; i--) {
			theta1 = theta + ringDelta;
			cosTheta1 = cos(theta1);
			sinTheta1 = sin(theta1);
			glBegin(GL_QUAD_STRIP);
			phi = 0.0;
			for (j = slices; j >= 0; j--) {
				GLfloat cosPhi, sinPhi, dist;

				phi += sideDelta;
				cosPhi = cos(phi);
				sinPhi = sin(phi);
				dist = outer + inner * cosPhi;
				//v = arccos (Y/R)/2p
//u = [arccos ((X/(R + r*cos(2 pv))]2p


				glNormal3f(cosTheta1 * cosPhi, -sinTheta1  *cosPhi, sinPhi);
				glTexCoord2d(acos((-sinTheta1  *dist))/inner / 2*PI,acos((cosTheta1  *dist)/(inner + cosTheta1) * 2*PI));
				glVertex3f(cosTheta1  *dist, -sinTheta1  *dist, inner * sinPhi);


				glNormal3f(cosTheta  *cosPhi, -sinTheta  *cosPhi, sinPhi);
				glTexCoord2d(acos((-sinTheta1 * dist))/inner / 2*PI,acos((cosTheta1  *dist)/(inner + cosTheta1) * 2*PI));
				glVertex3f(cosTheta  *dist, -sinTheta * dist,  inner * sinPhi);
			}
			glEnd();
			theta = theta1;
			cosTheta = cosTheta1;
			sinTheta = sinTheta1;
}

}