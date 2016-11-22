#include "TermTrapez.h"



TermTrapez::TermTrapez()
{
}


TermTrapez::~TermTrapez()
{
}

void TermTrapez::setPoints(int point, int pointNum) {
	if (pointNum >= 4 || pointNum < 0) return;
	this->points[pointNum] = point;
}
int TermTrapez::getPoint(int pointNum) {
	return this->points[pointNum];
}

float TermTrapez::getValue(int x) {
	if (isZero) return 0.0;

	if (x < points[0] || x > points[3])
		return 0.0;
	float value = 0;
	if (x > points[0] && x < points[1])
		value = (float)(x - points[0]) / (float)(points[1] - points[0]);
	if (x >= points[1] && x <= points[2])
		value = max;
	if (x > points[2] && x < points[3])
		value = (float)(points[3] - x) / (float)(points[3] - points[2]);
	

	return value;
}

void TermTrapez::updateTerm(float y) {
	if (y == 0.0) {
		this->isZero = true;
		return;
	}
	float a = this->max / (this->points[1] - this->points[0]);
	float b = -a * this->points[0];
	int nPoint = (int)((y - b) / a);
	this->points[1] = nPoint;
	nPoint = this->points[3] + (this->points[1] - this->points[0]);
	this->points[2] = nPoint;
	this->max = y;
	this->isZero = false;
}

void TermTrapez::setMax(float m) {
	if (m == 0.0) {
		isZero = true;
	}
	else {
		this->max = m;
	}	
}

float TermTrapez::getMax() {
	return this->max;
}