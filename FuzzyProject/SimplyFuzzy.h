#ifndef SIMPLYFUZZY_H
#define SIMPLYFUZZY_H

#include <cstdlib>
#include<vector>
#include<math.h>
#include <iterator>

#include "TermTrapez.h"

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
	float centers[6];

	void resetOutput();
	void updateOutput(int outputNum, float y);
	float maxmax(std::vector<float> &v);
	float minmin(float a, float b, float c);

};
#endif // !SIMPLYFUZZY_H
