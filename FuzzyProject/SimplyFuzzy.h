#pragma once

#include <cstdlib>
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



};

