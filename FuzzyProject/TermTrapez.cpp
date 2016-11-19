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
	if (x < points[0] || x > points[3])
		return 0.0;
	float value = 0;
	if (x >= points[0] && x <= points[1])
		value = (float)(x - points[0]) / (float)(points[1] - points[0]);
	if (x >= points[1] && x <= points[2])
		value = 1;
	if (x >= points[2] && x <= points[3])
		value = (float)(points[3] - x) / (float)(points[3] - points[2]);
	

	return value;
}
