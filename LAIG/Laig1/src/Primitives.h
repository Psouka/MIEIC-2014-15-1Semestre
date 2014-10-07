#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include "CGFobject.h"
using namespace std;

class Primitives
{
public:
	Primitives();
	virtual void draw()=0;
	float length_s, length_t;
};

class Circle : public Primitives
{
	float radius;
	int slices;
public:
	Circle(float rad, int slices);
	void draw();
};

class Rectangle : public Primitives
{
	float x1, y1, x2, y2;
public:
	Rectangle(float x1,float y1, float x2, float y2);
	void draw();
};

class Triangle : public Primitives
{
	float x1, y1, z1, x2, y2, z2, x3, y3, z3;
public:
	Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	void draw();
};

class Cylinder : public Primitives
{
	float base,top,height;
	int slices, stacks;
public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	void draw();
	
};

class Sphere : public Primitives
{
	float radius;
	int slices,stacks;
public:
	Sphere(float radius, int slices, int stacks);
	void draw();
};

class Torus : public Primitives
{
	float inner,outer;
	int slices, loops;
public:
	Torus(float inner, float outer, int slices, int loops);
	void draw();
};



#endif