#ifndef SIMPLYFUZZY_H
#define SIMPLYFUZZY_H

#include<math.h>

#include "TermTrapez.h"


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
	float centers[6];


	void resetOutput();
	void updateOutput(int outputNum, float y);
	float minmin(float a, float b, float c);
};
#endif // !SIMPLYFUZZY_H
