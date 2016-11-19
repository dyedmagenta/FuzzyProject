#include <iostream>


#include <stdio.h>

#include "SimplyFuzzy.h"

int main() {
	printf("INPUTS LEFT MID RIGHT \n");	
	
	SimplyFuzzy sf;
	int a, b, c;
	while (std::cin >> a >> b >> c) {
		c = sf.getLeftOutput(a, b, c);
		std::cout << "\nLEFT:" << c << "\n";
		c = sf.getRightOutput(a, b, c);
		std::cout << "RIGHT:" << c << "\n";
	}
	

	system("pause");

	return 0;
}
