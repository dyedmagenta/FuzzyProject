#include "Term.h"



void Term::setPoints(int point, int pointNum) {
	if (pointNum >= 4 || pointNum < 0) return;
	this->points[pointNum] = point;
}

int Term::getPoint(int pointNum) {
	return this->points[pointNum];
}

float Term::getValue(int x) {
	if (isZero) return 0.0;

	if (x < points[0] || x > points[3])
		return 0.0;
	float value = 0.0;
	if (x > points[0] && x < points[1])
		value = (float)(x - points[0]) / (float)(points[1] - points[0]);
	if (x >= points[1] && x <= points[2])
		value = max;
	if (x > points[2] && x < points[3])
		value = (float)(points[3] - x) / (float)(points[3] - points[2]);
	

	return value;
}
void Term::updateTerm(float y) {
	if (y == 0.0) {
		this->isZero = true;
		return;
	}
	if(this->points[0] != this->points[1])
	{
		this->points[1] = newPoint(this->points[1], this->points[0], y);
	}
	
	if (this->points[2] != this->points[3])
	{
		this->points[2] = newPoint(this->points[2], this->points[3], y);
	}
	
	// OLD	
	/*float a = this->max / (this->points[1] - this->points[0]);
	float b = -a * this->points[0];
	int nPoint = (int)((y - b) / a);
	this->points[1] = nPoint;
	nPoint = this->points[3] + (this->points[1] - this->points[0]);
	this->points[2] = nPoint;*/
	
	this->max = y;
	this->isZero = false;
}

int Term::newPoint(int lastPoint, int firstPoint, float y)
{
	float a = this->max / (lastPoint - firstPoint);
	float b = -a * firstPoint;
	return round((y - b) / a);
}

void Term::setMax(float m) {
	if (m == 0.0) {
		isZero = true;
	}
	else {
		this->max = m;
	}	
}

float Term::getMax() const
{
	return this->max;
}
