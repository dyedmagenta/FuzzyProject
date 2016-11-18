#include "FuzzySet.h"





FuzzySet::FuzzySet(float size, float step) {
	this->size = size;
	this->step = step;
	//fills array with zeros
	this->setArray[0] = new float[size];
	for (int i = 0; i < 3; i++) {
		memset(this->setArray[i], 0, sizeof(float) * this->size);
	}
}
void FuzzySet::showSet() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < this->size; j++) {
			printf("%f ", this->setArray[i][j]);
		}
	}
}