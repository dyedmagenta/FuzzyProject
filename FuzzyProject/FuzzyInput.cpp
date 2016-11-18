#include "FuzzyInput.h"

FuzzyInput::FuzzyInput(float size, int termNumber) {
	this->size = size;
	this->termNumber = termNumber;

	//fills array with zeros
	this->setArray = (float**)malloc(sizeof(*setArray)*termNumber);
	for (int i = 0; i < 3; i++) {
		//this->setArray[i] = new float[size];
		this->setArray[i] = (float*)malloc(sizeof(float)*size);
		for (int j = 0; j < size; j++) {
			setArray[i][j] = 0.0;
		}
	}
	
	
}

void FuzzyInput::showSet() {
	printf("\n\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < this->size; j++) {
			printf("%f ", this->setArray[i][j]);
		}
		printf("\n\n");
	}
}

void FuzzyInput::addTerm(FuzzyTerm ft) {
	if (ft.getTermType() == ft.termTypes[0]) return;
	if (ft.getTermType() == ft.termTypes[1]) {
		float x = ft.getA().x;
		float y = ft.getA().y;
		setArray[arrCur][(int)x] = y;
	} else if (ft.getTermType() == ft.termTypes[2]) {
		float start = ft.getA().x;
		float stop = ft.getB().x;

		for (int i = start; i <= stop; i++) {
			if (start < stop) {
				setArray[arrCur][i] = (i - start) / (stop - start);
			}
			else {
				setArray[arrCur][i] = (stop - i) / (start - stop);
			}
		}
	}
	else if (ft.getTermType() == ft.termTypes[3]) {
		float start = ft.getA().x;
		float stop = ft.getC().x;
		float peak = ft.getB().x;

		for (int i = start; i <= stop; i++) {
			if (i <= peak) {
				setArray[arrCur][i] = (i - start) / (peak - start);
			} else{
				setArray[arrCur][i] = (stop - i) / (stop - peak);
			}
		}
	}
	else if (ft.getTermType() == ft.termTypes[3]) {
		float start = ft.getA().x;
		float stop = ft.getD().x;
		float peak1 = ft.getB().x;
		float peak2 = ft.getC().x;

		for (int i = start; i <= stop; i++) {
			if (i <= peak1) {
				setArray[arrCur][i] = (i - start) / (peak1 - start);
			}
			else if(i <= peak2){
				setArray[arrCur][i] = 1;
			}
			else {
				setArray[arrCur][i] = (stop - i) / (stop - peak2);
			}
		}
	}	
arrCur++;

}

/*free this malloc!!!!*/
void FuzzyInput::getFuzzyInput(int input, float* fuzzyInputArr) {
	fuzzyInputArr = (float*)malloc(sizeof(float)*termNumber);
	for (int i = 0; i < termNumber; i++) {
		fuzzyInputArr[i] = setArray[i][input];
	}
}

FuzzyInput::~FuzzyInput() {

	for (int i = 0; i < termNumber; i++)
		free(setArray[i]);
	free(setArray);
}