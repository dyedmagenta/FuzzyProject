#include "SimplyFuzzy.h"



SimplyFuzzy::SimplyFuzzy()
{

	inputTerms[0].setPoints(-20, 0);
	inputTerms[0].setPoints(-10, 1);
	inputTerms[0].setPoints(0, 2);
	inputTerms[0].setPoints(10, 3);
	
	inputTerms[1].setPoints(0, 0);
	inputTerms[1].setPoints(10, 1);
	inputTerms[1].setPoints(20, 2);
	inputTerms[1].setPoints(30, 3);

	inputTerms[2].setPoints(20, 0);
	inputTerms[2].setPoints(30, 1);
	inputTerms[2].setPoints(40, 2);
	inputTerms[2].setPoints(50, 3);

	inputTerms[3].setPoints(45, 0);
	inputTerms[3].setPoints(55, 1);
	inputTerms[3].setPoints(200, 2);
	inputTerms[3].setPoints(200, 3);

}


SimplyFuzzy::~SimplyFuzzy()
{
	
}

int SimplyFuzzy::getLeftOutput(int Left, int Mid, int Right) {
	return 0;
}