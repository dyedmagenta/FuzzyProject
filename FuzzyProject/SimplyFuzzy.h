#ifndef SIMPLYFUZZY_H
#define SIMPLYFUZZY_H

#include<math.h>
#include<stdlib.h>

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

	float getLeftOutput(int Left, int Mid, int Right);
	float getRightOutput(int Left, int Mid, int Right);
private:
	TermTrapez inputTerms[4];
	TermTrapez outPutTerms[6];
	float outputValues[6];

	Node* rulesTails[6];
	Node rules[6];

	float maxmax(int ruleNum);
	float maxmax(float arr[], int arrSize);
	float minmin(float a, float b, float c);
	void addNode(int ruleNum, float value);
	void cleanVariables();
	float calculateCoG();
};
#endif // !SIMPLYFUZZY_H
