#pragma once
//idk if ^ is alright
#ifndef FuzzyInput_H
#define FuzzyInput_H

#include <stdio.h>
#include <stdlib.h> //malloc

#include "FuzzyTerm.h"

class FuzzyInput
{
public:
	FuzzyInput(float size, int termNumber);
	~FuzzyInput();
	void addTerm(FuzzyTerm fuzzyTerm);
	void getFuzzyInput(int input, float* fuzzyInputArr);
	//Test
	void showSet();

private:
	float size;
	int termNumber;
	int arrCur = 0;
	float** setArray;
	//void calculate();


};


#endif