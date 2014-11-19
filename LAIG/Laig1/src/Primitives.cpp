#include <vector>
#include <string>
#include <iostream>
#include "Primitives.h"

#define PI 3.14159265359


Primitives::Primitives():CGFobject() {
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
		float lenT = t->tex_s, heiT = t->tex_t, lenO = x2-x1,heiO = y2-y1;
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
	if(t != NULL)
		glBindTexture(GL_TEXTURE_2D, t->getTexId());
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

Plane ::Plane(unsigned int p)
	:Primitives(),parts(p){}

const GLfloat Plane::ctrlpoints[4][3] = {
	{ 0.5, 0.0, -0.5}, 
	{ 0.5, 0.0, 0.5},
	{-0.5, 0.0, -0.5}, 
	{-0.5, 0.0, 0.5}};

const GLfloat Plane::normals[4][3] = {{ 0.0, 0.0, 1.0},
{ 0.0, 0.0, 1.0}, 
{ 0.0, 0.0, 1.0},
{ 0.0, 0.0, 1.0} };

const GLfloat Plane::textures[4][2] = {{ 0.0, 0.0},
{ 0.0, 1.0}, 
{ 1.0, 0.0},
{ 1.0, 1.0} };

void Plane ::draw(Texture* t){

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 3*2, 2,  &ctrlpoints[0][0]);

	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2, 0.0, 1.0, 3*2, 2,  &normals[0][0]);

	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2, 0.0, 1.0, 2*2, 2,  &textures[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0); 

	glEvalMesh2(GL_FILL, 0, parts, 0, parts);
}

Patch :: ~Patch(){
	delete(controlPoints);
	delete(texCoords);
}

Patch ::Patch(int o, int pU,int pV, string c, vector<float> controlPoint)
	:Primitives(),order(o),partsU(pU),partsV(pV){

		if(c == "fill")
			compute = GL_FILL;
		else if(c == "point")
			compute = GL_POINT;
		else if(c == "line")
			compute = GL_LINE;

		this->texCoords = new float[controlPoint.size()/3 * 2];
		float step = 1.0 / order;
		for(unsigned int i = 0; i < controlPoint.size()/3; i++)
		{
			int offset = i * 2;
			int sOffset = i % (order + 1);
			int tOffset = i / (order + 1);
			float s = sOffset * step;
			float t = tOffset * step;
			texCoords[offset] = s;
			texCoords[offset+1] = t;
		}


		controlPoints = new GLfloat[controlPoint.size()];
		for(unsigned int i = 0; i < controlPoint.size(); i++)
			controlPoints[i] = controlPoint[i];

}

void Patch ::draw(Texture* t){

	glEnable(GL_AUTO_NORMAL);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order+1, 0.0, 1.0, 3*(order+1), order+1,  &controlPoints[0]);	

	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, (order+1), 0.0, 1.0, (order+1)*2, (order+1), &texCoords[0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	// para este conjunto de interpoladores:
	//    na direccao U, serao efectuadas divisoes em 40 passos
	//        quando a variável U varia de 0 a 1
	//    na direccao V, serao efectuadas divisoes em 60 passos
	//        quando a variável U varia de 0 a 1
	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);


	glEvalMesh2(compute, 0, partsU, 0, partsV);

}


Vehicle ::~Vehicle(){
	for(unsigned int i = 0; i < top.size(); i++)
		delete(top[i]);

	for(unsigned int i = 0; i < mid.size(); i++)
		delete(mid[i]);
	for(unsigned int i = 0; i < bot.size(); i++)
		delete(bot[i]);
}



Vehicle ::Vehicle(){

	this->text_top = new CGFappearance("rainbow.jpg",1,1);
	this->text_bot = new CGFappearance("box.jpg",1,1);


	vector<float> controlPoint;

	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(7.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(2.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);

	/////////////////////////////////////

	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(0.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(14.0);

	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(4.0);

	////////////////////////////////////////

	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(-7.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(-2.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);

	/*
	<controlpoint x="0.0" y="7.0" z="0.0" />
	<controlpoint x="8.0" y="8.0" z="0.0" />
	<controlpoint x="2.0" y="0.0" z="0.0" />

	<controlpoint x="0.0" y="5.0" z="0.0" />
	<controlpoint x="0.0" y="8.0" z="8.0" />
	<controlpoint x="0.0" y="0.0" z="5.0" />

	<controlpoint x="0.0" y="7.0" z="0.0" />
	<controlpoint x="-8.0" y="8.0" z="0.0" />
	<controlpoint x="-2.0" y="0.0" z="0.0" />
	*/

	top.push_back(new Patch(2, 10,10, "fill", controlPoint));

	controlPoint.clear();


	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(-7.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(-2.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);


	/////////////////////////////////////

	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(0.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(-14.0);

	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(-4.0);

	////////////////////////////////////////

	controlPoint.push_back(0.0);
	controlPoint.push_back(7.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(7.0);
	controlPoint.push_back(8.0);
	controlPoint.push_back(0.0);

	controlPoint.push_back(2.0);
	controlPoint.push_back(0.0);
	controlPoint.push_back(0.0);

	top.push_back(new Patch(2, 10,10, "fill", controlPoint));


	mid.push_back(new Cylinder(0.05,0.05,2.5,5,5));

	bot.push_back(new Rectangle(-1.5,-5,1.5,-2));

}

void Vehicle ::draw(Texture* t){
	
	text_top->apply();

	for(unsigned int i = 0; i < top.size(); i++)
		top[i]->draw(t);
		

	
	text_bot->apply();
	int ang = 0;
	float transl = 1.5;
	for(int i = 0; i < 4; i++,ang += 90)
	{

		glPushMatrix();
		glRotated(ang,0,1,0);
		glTranslated(0,0,transl);
		bot[0]->draw(t);
		glPopMatrix();

		glPushMatrix();
		glRotated(ang,0,1,0);
		glTranslated(0,0,-transl);
		bot[0]->draw(t);
		glPopMatrix();
	}
	
	//parte debaixo da caixa
	glPushMatrix();
	glRotated(-90,1,0,0);
	glTranslated(0,3.5,-5);
	bot[0]->draw(t);
	glPopMatrix();

	//parte debaixo da caixa mas virada para baixo
	glPushMatrix();
	glRotated(90,1,0,0);
	glTranslated(0,3.5,5);
	bot[0]->draw(t);
	glPopMatrix();



	//cilindros
	text_bot->apply();
	glPushMatrix();
	glRotated(-90,1,0,0);
	glTranslated(1.5,1.5,-2);
	mid[0]->draw(t);
	glPopMatrix();


	glPushMatrix();
	glRotated(-90,1,0,0);
	glTranslated(-1.5,1.5,-2);
	mid[0]->draw(t);
	glPopMatrix();


	glPushMatrix();
	glRotated(-90,1,0,0);
	glTranslated(-1.5,-1.5,-2);
	mid[0]->draw(t);
	glPopMatrix();


	glPushMatrix();
	glRotated(-90,1,0,0);
	glTranslated(1.5,-1.5,-2);
	mid[0]->draw(t);
	glPopMatrix();

}

Flag :: ~Flag(){
	delete(shader);
	delete(texture);
}

Flag ::Flag(CGFtexture * t)
	:Plane(60),shader(new Shader(t)){

}

void Flag ::draw(Texture* t)
{
	this->shader->bind();

	Plane::draw(t);

	this->shader->unbind();
}

void Flag::update(unsigned long t)
{
	float time_s = t * 0.001; 

	this->shader->setTime(time_s);
}

void Flag::setWind(int wind)
{
	this->shader->wind = wind;
}