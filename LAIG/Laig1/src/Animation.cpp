#include "Animation.h"

# define PI 3.14159265358979323846

vector<float> normalize(vector<float> vec) {
	vector<float> temp = vec;
	float normal = sqrtf(pow(temp[0], 2) + pow(temp[1], 2) + pow(temp[2], 2));

	for(unsigned int i = 0; i < temp.size(); i++) {
		temp[i] = temp[i] / normal;
	}
	return temp;
}

Animation::Animation(string id,float span) {
	this->id = id;
	this->span = span;
	this->start = false;
}

string Animation::getId(){
	return id;
}

void LinearAnimation::init(unsigned long t) {
	this->distance = 0;

	for(unsigned int i = 0; i < this->controlPoint.size() - 1; i++) {
		this->distance += sqrtf( pow(this->controlPoint[i+1][0] - this->controlPoint[i][0], 2) +
			pow(this->controlPoint[i+1][1] - this->controlPoint[i][1], 2) +
			pow(this->controlPoint[i+1][2] - this->controlPoint[i][2], 2));
	}

	this->idPC = 0;
	this->transX = this->controlPoint[this->idPC][0];
	this->transY = this->controlPoint[this->idPC][0];
	this->transZ = this->controlPoint[this->idPC][0];
	this->start = true;
	this->stop = false;
	this->time = t;
}

LinearAnimation::LinearAnimation(string id, float span, vector<vector<float>> controlPoint)
	:Animation(id,span),controlPoint(controlPoint){
		start = false;
}

void LinearAnimation::apply() {
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(this->transX, this->transY, this->transZ);
}

void LinearAnimation::update(unsigned long t) {

	if(!start) {
		init(t);
		return;
	}

	if(!stop) {
		//vector da deslocação
		vector<float> temp;
		temp.push_back(controlPoint[idPC+1][0] - controlPoint[idPC][0]);
		temp.push_back(controlPoint[idPC+1][1] - controlPoint[idPC][1]);
		temp.push_back(controlPoint[idPC+1][2] - controlPoint[idPC][2]);

		//calcular o angulo em relação ao eixo dos yy

		float prodEsc = temp[0] * 0 + temp[2] * 1;
		float norma = sqrtf(pow(temp[0], 2) + pow(temp[2], 2));
		rotation = acos(prodEsc/norma);

		//calcular a velocidade 
		unsigned long elapsed = t - time;

		float vel = (distance/(span*1000))*(elapsed);

		temp = normalize(temp);

		//posição por unidade de tempo
		for(unsigned i = 0; i < temp.size(); i++) {
			temp[i] = temp[i] * vel;
		}

		//incremento da translacção
		transX = transX + temp[0];
		transY = transY + temp[1];
		transZ = transZ + temp[2];

		//se passar do ponto de controlo ignora o resto do incremento
		if(abs((transX + temp[0]) > abs(controlPoint[idPC+1][0])))
			transX = controlPoint[idPC+1][0];
		if(abs((transY + temp[1]) > abs(controlPoint[idPC+1][1])))
			transY = controlPoint[idPC+1][1];
		if(abs((transZ + temp[2]) > abs(controlPoint[idPC+1][2])))
			transZ = controlPoint[idPC+1][2];


		if(transX == controlPoint[idPC+1][0] && transY == controlPoint[idPC+1][1] && transZ == controlPoint[idPC+1][2]) 
			idPC++;

		if(idPC == controlPoint.size() -1) {
			stop = true;
		}

		//actualizar o tempo
		time = t;
	}

}

CircularAnimation::CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng)
	:Animation(id,span),radius(radius),startAng(startAng),rotAng(rotAng) {

		this->center[0] = center[0];
		this->center[1] = center[1];
		this->center[2] = center[2];

		this->stop = false;
}

void CircularAnimation::init(unsigned long t) {

	this->rotation = startAng;

	this->transX = center[0] + this->radius*cos(this->startAng);
	this->transY = center[1] + 0;
	this->transZ = center[2] + this->radius*sin(this->startAng);

	this->distance = 2*PI*this->radius;

	this->velAng = this->distance / (this->span*1000);

	this->time = t;
}


void CircularAnimation::update(unsigned long t) {
	if(!stop) {

		unsigned long elapsed = t - time;
		rotation += velAng * elapsed;

		float angle = (startAng + rotation) * PI/180;

		transX = center[0] + radius*cos(angle);
		transY = center[1] + 0;
		transZ = center[2] + radius*sin(angle);

		time = t;

		if(abs(rotation) >= abs(startAng + rotation)) {
			stop = true;
		}
	}
}

void CircularAnimation::apply() {

	glRotatef(rotation, 0, 1, 0);
	glTranslatef(this->transX, this->transY, this->transZ);
}

NoAnimation::NoAnimation()
	:Animation("",0){
}
void NoAnimation::update(unsigned long t){}
void NoAnimation::apply(){}
void NoAnimation::init(unsigned long t){}