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
	
	int getLeftOutput(int Left, int Mid, int Right);
	int getRightOutput(int Left, int Mid, int Right);
private:
	TermTrapez inputTerms[4];
	TermTrapez outPutTerms[6];
	int centers[6];

	Node* rulesTails[6];
	Node rules[6];

	void resetOutput();
	void updateOutput(int outputNum, float y);
	float maxmax(int ruleNum);
	float minmin(float a, float b, float c);
	void addNode(int ruleNum, float value);
	void clearNodes();
};
#endif // !SIMPLYFUZZY_H
