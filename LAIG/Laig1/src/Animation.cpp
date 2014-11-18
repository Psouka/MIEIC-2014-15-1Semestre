#include "Animation.h"

void normalize(vector<float> &vec) {
	float normal = sqrtf(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));

	for(unsigned int i = 0; i < vec.size(); i++) {
		vec[i] = vec[i] / normal;
	}
}


Animation:: Animation(string id,float span)
	:id(id),span(span){

}

string Animation:: getId(){
	return id;
}

LinearAnimation::LinearAnimation(string id, float span, vector<vector<float>> controlPoint)
	:Animation(id,span),controlPoint(controlPoint){
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

}

void LinearAnimation::apply() {
	glRotated(rotation, 0, 1, 0);
	glTranslated(this->transX, this->transY, this->transZ);
}

void LinearAnimation::update(unsigned long t) {

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

	normalize(temp);

	//posição por unidade de tempo
	for(unsigned i = 0; i < temp.size(); i++) {
		temp[i] = temp[i] * vel;
	}

	//se passar do ponto de controlo ignora o resto do incremento
	if(abs((transX + temp[0]) > abs(controlPoint[idPC+1][0])) ||
		abs((transX + temp[1]) > abs(controlPoint[idPC+1][1])) ||
		abs((transX + temp[2]) > abs(controlPoint[idPC+1][2]))) {
			transX = controlPoint[idPC+1][0];
			transY = controlPoint[idPC+1][1];
			transZ = controlPoint[idPC+1][2];
	}
	else { //incremento da translacção
		transX = transX + temp[0];
		transY = transY + temp[1];
		transZ = transZ + temp[2];
	}

	if(transX == controlPoint[idPC+1][0] && transY == controlPoint[idPC+1][1] && transZ == controlPoint[idPC+1][2]) 
		idPC++;

	if(idPC == controlPoint.size() -1) {
		idPC == 0;
	}

	//actualizar o tempo
	time = t;

}

CircularAnimation :: CircularAnimation(string id, float span, float* center, float radius, float startAng, float rotAng)
	:Animation(id,span),radius(radius),startAng(startAng),rotAng(rotAng) {

		this->center[0] = center[0];
		this->center[1] = center[1];
		this->center[2] = center[2];
}

void CircularAnimation::update(unsigned long t) {

}

void CircularAnimation::apply() {

}

