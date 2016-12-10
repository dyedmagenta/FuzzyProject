#include <iostream>

#include "SimplyFuzzy.h"



/*
 * Console Example
 */
int main() {
	printf("INPUTS\nLEFT MID RIGHT \n");

	SimplyFuzzy sf;
	
	int a, b, c;
	while (std::cin >> a >> b >> c) {
		sf.setInputs(a, b, c);
		float dd = sf.getOutput(true);
		std::cout << "\n LEFT SPEED:" << dd << "\n";
		dd = sf.getOutput(false);
		std::cout << "RIGHT SPEED:" << dd << "\n";
		printf("\nINPUTS\nLEFT MID RIGHT \n");
	}

	system("pause");

	return 0;
}

