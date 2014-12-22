#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include "Shader.h"
#include "CGFobject.h"
#include "Appearance.h"
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

class Rect: public Primitives {

	float x1, y1, x2, y2;

public:
	Rect(float x1,float y1, float x2, float y2);
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

class Plane : public Primitives{
	static const GLfloat ctrlpoints[4][3];
	static const GLfloat normals[4][3];
	static const GLfloat textures[4][2];
	unsigned int parts;
public :
	Plane(unsigned int p  = 10);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Patch : public Primitives{
	int order, partsU,partsV;
	GLenum compute;
	float* controlPoints;
	float* texCoords;
public:
	~Patch();
	Patch(int o, int pU,int pV, string c, vector<float> controlPoint);
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Vehicle : public Primitives{
	CGFappearance * text_top;
	CGFappearance * text_bot;

	vector<Patch*> top;
	vector<Rect*>bot;
	vector<Cylinder*>mid;
public:
	~Vehicle();
	Vehicle();
	void draw(Texture* t);
	void update(unsigned long t){};
};

class Flag : public Plane{
	CGFtexture* texture;
	Shader* shader;
public :
	~Flag();
	Flag(CGFtexture * t);
	void draw(Texture* t);
	void update(unsigned long t);
	void setWind(int wind);
};



class Piece : public Primitives{
	unsigned int x,y;
	Cylinder* cyl;
	Appearance* playerApp;

public:
	Piece(Appearance* playerText);
	~Piece();
	void draw(Texture* t);
	void update(unsigned long t){};
};


class Board: public Primitives {
	vector< vector<char> > board;
	Rect* rec;

	bool isSelected(int column, int row);

public:	
	vector<int> selectedColumns;
	vector<int> selectedRows;

	int nSpaces;
	Board();
	~Board(void);
	void init(int nSpaces);

	vector<char> getPositions();
	void setPositions(vector<char> newPos);

	vector<char> undo();

	void selectSpace(int column, int row);
	void clearSelected();

	void draw(Texture* t);
	void update(unsigned long t){};
};
#endif