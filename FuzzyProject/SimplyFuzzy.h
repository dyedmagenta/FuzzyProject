#ifndef SIMPLYFUZZY_H
#define SIMPLYFUZZY_H

#include<math.h>
#include<malloc.h>

#include "TermTrapez.h"

struct Node {

	float value = 0;
	Node* next = NULL;
};

class SimplyFuzzy
{
public:
	SimplyFuzzy();
	~SimplyFuzzy();
	void init();
	void setInputs(int left, int mid, int right);
	
	float getOutput(bool isLeft);

private:
	TermTrapez inputTerms[4];
	TermTrapez outPutTerms[6];
	float outputValues[6];

	float leftValues[4];
	float midValues[4];
	float rightValues[4];

	Node* rulesTails[6];
	Node rules[6];

	float maxmax(int ruleNum);
	float maxmax(float arr[], int arrSize);
	float minmin(float a, float b, float c);
	void addNode(int ruleNum, float value);
	void cleanVariables();
	void rulesLeft();
	void rulesRight();
};
#endif // !SIMPLYFUZZY_H
