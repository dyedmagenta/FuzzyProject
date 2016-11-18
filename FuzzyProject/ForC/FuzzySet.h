#pragma once
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h> //memset

#include "FuzzyTerm.h"

#ifndef FUZZYSET_H
#define FUZZYSET_H

class FuzzySet
{
public:
	FuzzySet(float size, float step);
	void addTerm(FuzzyTerm fuzzyTerm);
	//Test
	void showSet();

private:
	float size;
	float step;
	float* setArray[3];

	void calculate();


};


#endif