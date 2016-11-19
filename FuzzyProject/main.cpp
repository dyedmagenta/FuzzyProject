#include <iostream>


#include <stdio.h>

#include "SimplyFuzzy.h"

int main() {
	printf("Hello World \n");	
	
	SimplyFuzzy sf;
	int a, b, c;
	while (std::cin >> a >> b >> c) {
		c = sf.getLeftOutput(a, b, c);
		std::cout << "\n" << c << "\n";
	}
	

	system("pause");

	return 0;
}
