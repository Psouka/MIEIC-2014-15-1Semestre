#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include "Shader.h"
#include "CGFobject.h"
#include "Textures.h"
using namespace std;

class Primitives: CGFobject {

public:
	Primitives();
	virtual void update(unsigned long t) = 0;
	virtual void draw(Texture* t)=0;
	float length_s, length_t;
};

class Circle: public Primitives {

	float radius;
	int slices;

public:
	Circle(float rad, int slices);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Rectangle: public Primitives {

	float x1, y1, x2, y2;

public:
	Rectangle(float x1,float y1, float x2, float y2);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Triangle: public Primitives {

	float x1, y1, z1, x2, y2, z2, x3, y3, z3;

public:
	Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Cylinder: public Primitives {

	float base,top,height,angle;
	int slices, stacks;

public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	void draw(Texture* t);
	void update(unsigned long t){};

};

class Sphere: public Primitives {

	float radius;
	int slices,stacks;

public:
	Sphere(float radius, int slices, int stacks);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Torus: public Primitives {

	float inner,outer;
	int slices, loops;

public:
	Torus(float inner, float outer, int slices, int loops);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Plane:public Primitives{
	static const GLfloat ctrlpoints[4][3];
	static const GLfloat normals[4][3];
	static const GLfloat textures[4][2];
	unsigned int parts;
public :
	Plane(unsigned int p  = 10);
	void draw(Texture* t);
	void update(unsigned long t){};
};



class Patch:public Primitives{
	int order, partsU,partsV;
	GLenum compute;
	float* controlPoints;
	float* texCoords;
public:
	Patch(int o, int pU,int pV, string c, vector<float> controlPoint);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Vehicle:public Primitives{
public:
	Vehicle();
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Flag:public Plane{
	Texture* texture;
	Shader* shader;
public :
	Flag(Texture * t);
	void draw(Texture* t);
	void update(unsigned long t);
	void setWind(int wind);
};

#endif