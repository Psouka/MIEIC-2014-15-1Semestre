#include <vector>
#include <string>
#include <iostream>
#include "Primitives.h"

Primitives :: Primitives(){

}

Rectangle :: Rectangle(float x1,float y1, float x2, float y2){

	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Rectangle :: draw(){
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
}



Cylinder :: Cylinder(float base, float top, float height, int slices, int stacks){
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
}

void Cylinder :: draw(){
}


Sphere :: Sphere(float radius, int slices, int stacks){
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

void Sphere :: draw(){
}



Torus :: Torus(float inner, float outer, int slices, int loops){
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void Torus :: draw(){
}