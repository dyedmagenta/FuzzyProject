#include "FuzzyMain.h"


FuzzyMain::FuzzyMain()
{
	FuzzyInput fi(100, 3);
	FuzzyTerm low(Point(0, 1), Point(10, 0)), med(Point(10, 0), Point(30, 1), Point(40, 0)), high(Point(35, 0), Point(45, 1));
	fi.addTerm(low);
	fi.addTerm(med);
	fi.addTerm(high);
	fi.showSet();

	Rules r;
	//addRule();

	
}


FuzzyMain::~FuzzyMain()
{
}
