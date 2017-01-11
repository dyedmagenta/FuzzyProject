#ifndef SIMPLYFUZZY_H
#define SIMPLYFUZZY_H

#include "stdlib.h"
#include "Term.h"

struct Node {
	float value = 0;
	Node* next = NULL;
};

class SimplyFuzzy
{
public:
	SimplyFuzzy();
	~SimplyFuzzy();
	/**
	 *  \brief
	 *  Intializes input and output terms for 3 distance sensors as inputs and 2 wheels as outputs
	 *  Works as helper method for a constructor
	 *  In .ino should be called after allocating memory
	 *  Values are in SimplyFuzzy.cpp
	 */
	void init();
	/**
	 * \brief
	 * Sets values of inputs
	 *
	 * \param left
	 * Distance from left sensor
	 *
	 * \param mid
	 * Distance from middle sensor
	 *
	 * \param right
	 * Distance from right sensor
	 */
	void setInputs(int left, int mid, int right);
	/**
	 * \brief
	 * Calculates speed value for a wheel
	 *
	 * \param isLeft
	 * true		- returns speed for left wheel
	 * false	- returns speed for right wheel
	 *
	 * \return
	 * Speed value
	 */
	int getOutput(bool isLeft);

private:
	Term inputTerms[4];
	Term outputTerms[6];
	float outputValues[6];

	float leftValues[4];
	float midValues[4];
	float rightValues[4];

	int maxInput;
	int minInput;

	/*
	 * Array of pointers to the last node of ruleLists
	 * used for easier addition of new values to the list
	 */
	Node* rulesTails[6];
	/*
	 * Array of linked lists of values for each output
	 */
	Node ruleLists[6];

	/*
	* Returns maximum value from specified rule
	*/
	float maxValue(int ruleNum);
	/*
	* returns maximum value from array
	*/
	static float maxValue(float arr[], int arrSize);
	/*
	 * Returns minimum value
	 */
	static float minValue(float a, float b, float c);
	/*
	 * Adds value to a link list
	 */
	void addNode(int ruleNum, float value);
	void cleanVariables();
	void rulesLeft();
	void rulesRight();
};
#endif // !SIMPLYFUZZY_H
