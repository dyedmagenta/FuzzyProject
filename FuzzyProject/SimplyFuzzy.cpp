#include "SimplyFuzzy.h"

/*
 * INPUTS
 * inputTerms[0] - Very Close	(-15, 25)
 * inputTerms[1] - Close		(10, 50)
 * inputTerms[2] - Med			(35, 75)
 * inputTerms[3] - Far			(60, 300)
 *
 * Outputs values range from -255 MIN to MAX 255
 * In some cases first term should be symmetrical in respect to the lowest value
 * and last symmetrical in respect to highest value so the centre of gravity is
 * calculated right
 *
 * OUTPUTS
 * outputTerms[0] - Back Max Speed		(-255, -155)
 * outputTerms[1] - Back Med Speed		(-185, -85)
 * outputTerms[2] - Back Min Speed		(-115, -15)
 * outputTerms[3] - Forward Min Speed	(15, 115)
 * outputTerms[4] - Forward Med Speed	(85, 185)
 * outputTerms[5] - Forward Max Speed	(155, 255)
 */
SimplyFuzzy::SimplyFuzzy()
{
	init();
}

void SimplyFuzzy::init() {

	minInput = 0;
	maxInput = 255;

	inputTerms[0].setPoints(-15, 0);
	inputTerms[0].setPoints(0, 1);
	inputTerms[0].setPoints(10, 2);
	inputTerms[0].setPoints(25, 3);

	inputTerms[1].setPoints(10, 0);
	inputTerms[1].setPoints(25, 1);
	inputTerms[1].setPoints(35, 2);
	inputTerms[1].setPoints(50, 3);

	inputTerms[2].setPoints(35, 0);
	inputTerms[2].setPoints(50, 1);
	inputTerms[2].setPoints(60, 2);
	inputTerms[2].setPoints(75, 3);

	inputTerms[3].setPoints(60, 0);
	inputTerms[3].setPoints(75, 1);
	inputTerms[3].setPoints(255, 2);
	inputTerms[3].setPoints(270, 3);

	outputTerms[0].setPoints(-200, 0);
	outputTerms[0].setPoints(-175, 1);
	outputTerms[0].setPoints(-135, 2);
	outputTerms[0].setPoints(-105, 3);

	outputTerms[1].setPoints(-135, 0);
	outputTerms[1].setPoints(-105, 1);
	outputTerms[1].setPoints(-115, 2);
	outputTerms[1].setPoints(-85, 3);

	outputTerms[2].setPoints(-115, 0);
	outputTerms[2].setPoints(-85, 1);
	outputTerms[2].setPoints(-70, 2);
	outputTerms[2].setPoints(-60, 3);

	outputTerms[3].setPoints(40, 0);
	outputTerms[3].setPoints(45, 1);
	outputTerms[3].setPoints(50, 2);
	outputTerms[3].setPoints(55, 3);

	outputTerms[4].setPoints(50, 0);
	outputTerms[4].setPoints(55, 1);
	outputTerms[4].setPoints(65, 2);
	outputTerms[4].setPoints(95, 3);

	outputTerms[5].setPoints(65, 0);
	outputTerms[5].setPoints(95, 1);
	outputTerms[5].setPoints(125, 2);
	outputTerms[5].setPoints(150, 3);

	for (int i = 0; i < 6; i++)
	{
		rulesTails[i] = &ruleLists[i];
		outputValues[i] = 0.0;
	}
}

SimplyFuzzy::~SimplyFuzzy()
{
	cleanVariables();
}

void SimplyFuzzy::setInputs(int left, int mid, int right) {

	if (left > maxInput) left = maxInput;
	if (mid > maxInput) mid = maxInput;
	if (right > maxInput) right = maxInput;

	if (left < minInput) left = minInput;
	if (mid < minInput) mid = minInput;
	if (right < minInput) right = minInput;


	for (int i = 0; i < 4; i++) {
		leftValues[i] = inputTerms[i].getValue(left);
		midValues[i] = inputTerms[i].getValue(mid);
		rightValues[i] = inputTerms[i].getValue(right);
	}
}

int SimplyFuzzy::getOutput(bool isLeft) {

	if (isLeft) {
		rulesLeft();
	}
	else {
		rulesRight();
	}

	for (int i = 0; i < 6; i++) {
		outputValues[i] = maxValue(i);
		outputTerms[i].updateTerm(outputValues[i]);
	}

	//Calculating Center of Gravity
	float cog = 0.0;
	float valueSum = 0;
	float temp[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

	for (int i = outputTerms[0].getPoint(0); i < outputTerms[5].getPoint(3); i++) {
		for (int j = 0; j<6; j++)
		{
			temp[j] = outputTerms[j].getValue(i);
		}
		float tt = maxValue(temp, 6);
		valueSum += tt;
		cog += tt*i;
	}
	cog = cog / valueSum;

	cleanVariables();
	return round(cog);
}

float SimplyFuzzy::maxValue(int ruleNum) {
	Node* nodeCursor = &ruleLists[ruleNum];
	float max = nodeCursor->value;

	while (nodeCursor->next != NULL) {
		nodeCursor = nodeCursor->next;
		if (nodeCursor->value > max)
			max = nodeCursor->value;
	}
	return max;
}

float SimplyFuzzy::maxValue(float arr[], int arrSize) {
	float max = arr[0];

	for (int i = 0; i < arrSize; i++) {
		if (arr[i] > max)
			max = arr[i];
	}

	return max;
}

void SimplyFuzzy::addNode(int ruleNum, float value) {
	Node* nNode = (Node*)malloc(sizeof(Node));
	nNode->value = value;
	nNode->next = NULL;
	rulesTails[ruleNum]->next = nNode;
	rulesTails[ruleNum] = nNode;
}

float SimplyFuzzy::minValue(float a, float b, float c) {
	if (a < b)
		if (a < c)
			return a;
		else
			return c;
	else
		if (b < c)
			return b;
		else
			return c;
}

void SimplyFuzzy::cleanVariables() {
	Node* cur;
	for (int i = 0; i < 6; i++)
	{
		cur = &ruleLists[i];
		while (rulesTails[i] != &ruleLists[i])
		{

			if (cur->next->next == NULL) {
				rulesTails[i] = cur;
				free(cur->next);
				cur->next = NULL;
				cur = &ruleLists[i];
			}
			else {
				cur = cur->next;
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		outputTerms[i].updateTerm(1.0);
		outputValues[i] = 0;
	}
}

void SimplyFuzzy::rulesLeft() {
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[3], midValues[3], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[3], midValues[3], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[3], midValues[3], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[3], midValues[3], rightValues[0]));
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[3], midValues[2], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[3], midValues[2], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[3], midValues[2], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[3], midValues[2], rightValues[0]));
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minValue(leftValues[3], midValues[1], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[3], midValues[1], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[3], midValues[1], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[3], midValues[1], rightValues[0]));
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[3], midValues[0], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(1, minValue(leftValues[3], midValues[0], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[3], midValues[0], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(0, minValue(leftValues[3], midValues[0], rightValues[0]));
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[2], midValues[3], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[2], midValues[3], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[2], midValues[3], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[2], midValues[3], rightValues[0]));
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[2], midValues[2], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[2], midValues[2], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[2], midValues[2], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[2], midValues[2], rightValues[0]));
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[2], midValues[1], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[2], midValues[1], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[2], midValues[1], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[2], midValues[1], rightValues[0]));
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[2], midValues[0], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[2], midValues[0], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[2], midValues[0], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[2], midValues[0], rightValues[0]));
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[1], midValues[3], rightValues[3]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[1], midValues[3], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[1], midValues[3], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[1], midValues[3], rightValues[0]));
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[1], midValues[2], rightValues[3]));
	}
	/*BMID*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(1, minValue(leftValues[1], midValues[2], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[1], midValues[2], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[1], midValues[2], rightValues[0]));
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[1], midValues[1], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[1], midValues[1], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[1], midValues[1], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[1], midValues[1], rightValues[0]));
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[1], midValues[0], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[1], midValues[0], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(1, minValue(leftValues[1], midValues[0], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[1], midValues[0], rightValues[0]));
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[0], midValues[3], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[0], midValues[3], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[0], midValues[3], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[0], midValues[3], rightValues[0]));
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[0], midValues[2], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[0], midValues[2], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[0], midValues[2], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[0], midValues[2], rightValues[0]));
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[0], midValues[1], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[0], midValues[1], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[0], midValues[1], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[0], midValues[1], rightValues[0]));
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[0], midValues[0], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[0], midValues[0], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[0], midValues[0], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[0], midValues[0], rightValues[0]));
	}
}

void SimplyFuzzy::rulesRight() {
	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[3], midValues[3], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[3], midValues[3], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(5, minValue(leftValues[3], midValues[3], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[3], midValues[3], rightValues[0]));
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[3], midValues[2], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[3], midValues[2], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(5, minValue(leftValues[3], midValues[2], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[3], midValues[2], rightValues[0]));
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minValue(leftValues[3], midValues[1], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[3], midValues[1], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(5, minValue(leftValues[3], midValues[1], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[3], midValues[1], rightValues[0]));
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[3], midValues[0], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[3], midValues[0], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[3], midValues[0], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[3], midValues[0], rightValues[0]));
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[2], midValues[3], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[2], midValues[3], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[2], midValues[3], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[2], midValues[3], rightValues[0]));
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[2], midValues[2], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[2], midValues[2], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[2], midValues[2], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[2], midValues[2], rightValues[0]));
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minValue(leftValues[2], midValues[1], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[2], midValues[1], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minValue(leftValues[2], midValues[1], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[2], midValues[1], rightValues[0]));
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[2], midValues[0], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(5, minValue(leftValues[2], midValues[0], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[2], midValues[0], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[2], midValues[0], rightValues[0]));
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(3, minValue(leftValues[1], midValues[3], rightValues[3]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[1], midValues[3], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[1], midValues[3], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[1], midValues[3], rightValues[0]));
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(3, minValue(leftValues[1], midValues[2], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(4, minValue(leftValues[1], midValues[2], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[1], midValues[2], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[1], midValues[2], rightValues[0]));
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minValue(leftValues[1], midValues[1], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(1, minValue(leftValues[1], midValues[1], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[1], midValues[1], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[1], midValues[1], rightValues[0]));
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minValue(leftValues[1], midValues[0], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(1, minValue(leftValues[1], midValues[0], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minValue(leftValues[1], midValues[0], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minValue(leftValues[1], midValues[0], rightValues[0]));
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[0], midValues[3], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[0], midValues[3], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[0], midValues[3], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[0], midValues[3], rightValues[0]));
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[0], midValues[2], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[0], midValues[2], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[0], midValues[2], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[0], midValues[2], rightValues[0]));
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[0], midValues[1], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[0], midValues[1], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[0], midValues[1], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[0], midValues[1], rightValues[0]));
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minValue(leftValues[0], midValues[0], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(3, minValue(leftValues[0], midValues[0], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(2, minValue(leftValues[0], midValues[0], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minValue(leftValues[0], midValues[0], rightValues[0]));
	}
}
