#include <iostream>

#include "SimplyFuzzy.h"

int main() {
	printf("INPUTS\nLEFT MID RIGHT \n");

	SimplyFuzzy sf;
	
	int a, b, c;
	while (std::cin >> a >> b >> c) {
		
		float dd = sf.getLeftOutput(a, b, c);
		std::cout << "\n LEFT SPEED:" << dd << "\n";
		dd = sf.getRightOutput(a, b, c);
		std::cout << "RIGHT SPEED:" << dd << "\n";
		printf("\nINPUTS\nLEFT MID RIGHT \n");

	}
	

	system("pause");

	return 0;
}
