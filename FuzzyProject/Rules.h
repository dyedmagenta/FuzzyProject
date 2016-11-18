#pragma once
class Rules
{
public:
	Rules();
	Rules(int inTermsNumber, int inputsNumber, int outputsNumber, int outTermsNumber);



	~Rules();
private:
	int* inputs;
	int* outputs;

};

