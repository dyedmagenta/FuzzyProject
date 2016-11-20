#include <iostream>


#include <stdio.h>

#include "SimplyFuzzy.h"

int main() {
	printf("INPUTS LEFT MID RIGHT \n");	
	
	SimplyFuzzy sf;
	int a, b, c;
	while (std::cin >> a >> b >> c) {
		int dd = sf.getLeftOutput(a, b, c);
		std::cout << "\nLEFT:" << dd << "\n";
		dd = sf.getRightOutput(a, b, c);
		std::cout << "RIGHT:" << dd << "\n";
	}
	

	system("pause");

	return 0;
}
