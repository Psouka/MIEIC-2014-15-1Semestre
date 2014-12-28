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
	this->stop = false;
}

string Animation::getId(){
	return id;
}

bool Animation::getStop() {
	return stop;
}

vector<float> Animation::getFinalPos() {
	return finalPos;
}

vector<float> Animation::getInitialPos() {
	return initialPos;
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
	this->transY = this->controlPoint[this->idPC][1];
	this->transZ = this->controlPoint[this->idPC][2];
	this->start = true;
	this->time = t;
}

LinearAnimation::LinearAnimation(string id, float span, vector<vector<float>> controlPoint)
	:Animation(id,span),controlPoint(controlPoint){
		start = false;
		this->finalPos = this->controlPoint[controlPoint.size() -1];
		this->initialPos = this->controlPoint[0];

}

void LinearAnimation::apply() {
	glTranslatef(this->transX, this->transY, this->transZ);
	glRotatef(rotation, 0, 1, 0);
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

		if(temp[0] !=0 && temp[1] != 0) {
			float prodEsc = temp[0] * 0 + temp[2] * 1;
			float norma = sqrtf(pow(temp[0], 2) + pow(temp[2], 2));
			rotation = acos(prodEsc/norma);
		}
		else 
			rotation = 0;

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
		if(abs(transX) > abs(controlPoint[idPC+1][0]))
			transX = controlPoint[idPC+1][0];
		if(abs(transY) > abs(controlPoint[idPC+1][1]))
			transY = controlPoint[idPC+1][1];
		if(abs(transZ) > abs(controlPoint[idPC+1][2]))
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
		this->radius = radius;
		vector<float> temp(3);
		temp[0] = this->center[0]+this->radius*cos(rotAng);
		temp[1] = this->center[1];
		temp[2] = this->center[2]+this->radius*sin(rotAng);
		this->finalPos = temp;
		vector<float> temp1(3);
		temp1[0] = this->center[0]+this->radius*cos(startAng);
		temp1[1] = this->center[1];
		temp1[2] = this->center[2]+this->radius*sin(startAng);
		this->initialPos = temp1;
}

void CircularAnimation::init(unsigned long t) {

	this->rotation = startAng;

	this->velAng = rotAng / (span*1000);

	this->start = true;

	this->time = t;
}

void CircularAnimation::update(unsigned long t) {

	if(!start) {
		init(t);
		return;
	}

	if(!stop) {

		unsigned long elapsed = t - time;
		time = t;

		rotation += velAng * elapsed;

		float angle = (startAng + rotation) * PI/180;

		if(abs(rotation) >= abs(startAng+rotAng)) {
			rotation = rotAng;
			stop = true;
		}
	}
}

void CircularAnimation::apply() {
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(radius, 0, 0);
}

NoAnimation::NoAnimation()
	:Animation("",0){
}
void NoAnimation::update(unsigned long t){}
void NoAnimation::apply(){}
void NoAnimation::init(unsigned long t){}