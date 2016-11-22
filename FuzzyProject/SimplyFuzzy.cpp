#include "SimplyFuzzy.h"

SimplyFuzzy::SimplyFuzzy()
{
	/*
	INPUTS					Outputs/Rules
	[0] - Very Close		[0] - Back Max Speed
	[1] - Close			 	[1] - Back Med Speed
	[2] - Med				[2] - Back Min Speed
	[3] - Far				[3] - Forward Min Speed
	[4] - Forward Med Speed
	[5] - Forward Max Speed
	*/
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
	inputTerms[3].setPoints(250, 2);
	inputTerms[3].setPoints(300, 3);

	//Outpts -255 MIN .. MAX 255
	//Outputs must be symmetrical
	outPutTerms[0].setPoints(-255, 0);
	outPutTerms[0].setPoints(-225, 1);
	outPutTerms[0].setPoints(-185, 2);
	outPutTerms[0].setPoints(-155, 3);

	outPutTerms[1].setPoints(-185, 0);
	outPutTerms[1].setPoints(-155, 1);
	outPutTerms[1].setPoints(-115, 2);
	outPutTerms[1].setPoints(-85, 3);

	outPutTerms[2].setPoints(-115, 0);
	outPutTerms[2].setPoints(-85, 1);
	outPutTerms[2].setPoints(-45, 2);
	outPutTerms[2].setPoints(-15, 3);

	outPutTerms[3].setPoints(15, 0);
	outPutTerms[3].setPoints(45, 1);
	outPutTerms[3].setPoints(85, 2);
	outPutTerms[3].setPoints(115, 3);

	outPutTerms[4].setPoints(85, 0);
	outPutTerms[4].setPoints(115, 1);
	outPutTerms[4].setPoints(155, 2);
	outPutTerms[4].setPoints(185, 3);

	outPutTerms[5].setPoints(155, 0);
	outPutTerms[5].setPoints(185, 1);
	outPutTerms[5].setPoints(225, 2);
	outPutTerms[5].setPoints(255, 3);

	for (int i = 0; i < 6; i++)
	{
		rulesTails[i] = &rules[i];
		outputValues[i] = 0.0;
	}
}


float SimplyFuzzy::getLeftOutput(int left, int mid, int right) {
	float leftValues[4];
	float midValues[4];
	float rightValues[4];

	leftValues[0] = inputTerms[0].getValue(left);
	leftValues[1] = inputTerms[1].getValue(left);
	leftValues[2] = inputTerms[2].getValue(left);
	leftValues[3] = inputTerms[3].getValue(left);

	midValues[0] = inputTerms[0].getValue(mid);
	midValues[1] = inputTerms[1].getValue(mid);
	midValues[2] = inputTerms[2].getValue(mid);
	midValues[3] = inputTerms[3].getValue(mid);

	rightValues[0] = inputTerms[0].getValue(right);
	rightValues[1] = inputTerms[1].getValue(right);
	rightValues[2] = inputTerms[2].getValue(right);
	rightValues[3] = inputTerms[3].getValue(right);

	/*	Rules
	5	  4     3     2     1     0
	FMAX, FMED, FMIN, BMIN, BMED, BMAX
	*/
	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[3], midValues[3], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[3], midValues[3], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[3], midValues[3], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[3], midValues[3], rightValues[0]));
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[3], midValues[2], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[3], midValues[2], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[3], midValues[2], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[3], midValues[2], rightValues[0]));
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minmin(leftValues[3], midValues[1], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[3], midValues[1], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[3], midValues[1], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[3], midValues[1], rightValues[0]));
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[3], midValues[0], rightValues[0]));
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[2], midValues[3], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[2], midValues[3], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[2], midValues[3], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[2], midValues[3], rightValues[0]));
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[2], midValues[2], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[2], midValues[2], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[2], midValues[2], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[2], midValues[2], rightValues[0]));
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[2], midValues[1], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[2], midValues[1], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[2], midValues[1], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[2], midValues[1], rightValues[0]));
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[2], midValues[0], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[2], midValues[0], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[2], midValues[0], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[2], midValues[0], rightValues[0]));
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[1], midValues[3], rightValues[3]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[1], midValues[3], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[1], midValues[3], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[1], midValues[3], rightValues[0]));
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[1], midValues[2], rightValues[3]));
	}
	/*BMID*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(1, minmin(leftValues[1], midValues[2], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[1], midValues[2], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[1], midValues[2], rightValues[0]));
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[1], midValues[1], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[1], midValues[1], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[1], midValues[1], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[1], midValues[1], rightValues[0]));
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[1], midValues[0], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[1], midValues[0], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(1, minmin(leftValues[1], midValues[0], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[1], midValues[0], rightValues[0]));
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[0], midValues[3], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[0], midValues[3], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[0], midValues[3], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[0], midValues[3], rightValues[0]));
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[0], midValues[2], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[0], midValues[2], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[0], midValues[2], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[0], midValues[2], rightValues[0]));
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[0], midValues[1], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[0], midValues[1], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[0], midValues[1], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[0], midValues[1], rightValues[0]));
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[0], midValues[0], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[0], midValues[0], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[0], midValues[0], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[0], midValues[0], rightValues[0]));
	}

	for (int i = 0; i < 6; i++) {
		outputValues[i] = maxmax(i);
		outPutTerms[i].updateTerm(outputValues[i]);
		
	}
	


	float cog = calculateCoG();

	cleanVariables();
	return cog;
}


float SimplyFuzzy::getRightOutput(int left, int mid, int right) {

	float leftValues[4];
	float midValues[4];
	float rightValues[4];

	leftValues[0] = inputTerms[0].getValue(left);
	leftValues[1] = inputTerms[1].getValue(left);
	leftValues[2] = inputTerms[2].getValue(left);
	leftValues[3] = inputTerms[3].getValue(left);

	midValues[0] = inputTerms[0].getValue(mid);
	midValues[1] = inputTerms[1].getValue(mid);
	midValues[2] = inputTerms[2].getValue(mid);
	midValues[3] = inputTerms[3].getValue(mid);

	rightValues[0] = inputTerms[0].getValue(right);
	rightValues[1] = inputTerms[1].getValue(right);
	rightValues[2] = inputTerms[2].getValue(right);
	rightValues[3] = inputTerms[3].getValue(right);

	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[3], midValues[3], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[3], midValues[3], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(5, minmin(leftValues[3], midValues[3], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[3], midValues[3], rightValues[0]));
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[3], midValues[2], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[3], midValues[2], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(5, minmin(leftValues[3], midValues[2], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[3], midValues[2], rightValues[0]));
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(5, minmin(leftValues[3], midValues[1], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[3], midValues[1], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(5, minmin(leftValues[3], midValues[1], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[3], midValues[1], rightValues[0]));
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[3], midValues[0], rightValues[0]));
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[2], midValues[3], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[2], midValues[3], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[2], midValues[3], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[2], midValues[3], rightValues[0]));
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[2], midValues[2], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[2], midValues[2], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[2], midValues[2], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[2], midValues[2], rightValues[0]));
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minmin(leftValues[2], midValues[1], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[2], midValues[1], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(3, minmin(leftValues[2], midValues[1], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[2], midValues[1], rightValues[0]));
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[2], midValues[0], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(5, minmin(leftValues[2], midValues[0], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[2], midValues[0], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[2], midValues[0], rightValues[0]));
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(3, minmin(leftValues[1], midValues[3], rightValues[3]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[1], midValues[3], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[1], midValues[3], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[1], midValues[3], rightValues[0]));
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(3, minmin(leftValues[1], midValues[2], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(4, minmin(leftValues[1], midValues[2], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[1], midValues[2], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[1], midValues[2], rightValues[0]));
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(3, minmin(leftValues[1], midValues[1], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(1, minmin(leftValues[1], midValues[1], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[1], midValues[1], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[1], midValues[1], rightValues[0]));
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(4, minmin(leftValues[1], midValues[0], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(1, minmin(leftValues[1], midValues[0], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(4, minmin(leftValues[1], midValues[0], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(1, minmin(leftValues[1], midValues[0], rightValues[0]));
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[0], midValues[3], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[0], midValues[3], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[0], midValues[3], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[0], midValues[3], rightValues[0]));
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[0], midValues[2], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[0], midValues[2], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[0], midValues[2], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[0], midValues[2], rightValues[0]));
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[0], midValues[1], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[0], midValues[1], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[0], midValues[1], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[0], midValues[1], rightValues[0]));
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		addNode(1, minmin(leftValues[0], midValues[0], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		addNode(3, minmin(leftValues[0], midValues[0], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		addNode(2, minmin(leftValues[0], midValues[0], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		addNode(4, minmin(leftValues[0], midValues[0], rightValues[0]));
	}

	float ffmax = maxmax(5);
	float ffmed = maxmax(4);
	float ffmin = maxmax(3);
	float bbmin = maxmax(2);
	float bbmed = maxmax(1);
	float bbmax = maxmax(0);


	for (int i = 0; i < 6; i++) {
		outputValues[i] = maxmax(i);
		outPutTerms[i].updateTerm(outputValues[i]);
	}

	float cog = calculateCoG();

	cleanVariables();
	return cog;
}

/*	Rules
5	  4     3     2     1     0
FMAX, FMED, FMIN, BMIN, BMED, BMAX
*/
float SimplyFuzzy::calculateCoG() {
	float centSum = 0.0;
	float valueSum=0;
	float temp[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	
	for (int i = outPutTerms[0].getPoint(0); i < outPutTerms[5].getPoint(3); i++) {
		
		for(int j = 0; j<6; j++)
		{
			temp[j] = outPutTerms[j].getValue(i);
		}
		float tt = maxmax(temp, 6);
		valueSum += tt;
		centSum += tt*i;
	}
	centSum = centSum / valueSum;

	return centSum;
}

float SimplyFuzzy::maxmax(float arr[], int arrSize) {
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

float SimplyFuzzy::maxmax(int ruleNum) {
	Node* nodeCursor = &rules[ruleNum];
	float max = nodeCursor->value;

	while (nodeCursor->next != NULL) {
		nodeCursor = nodeCursor->next;
		if (nodeCursor->value > max)
			max = nodeCursor->value;
	}
	return max;
}

float SimplyFuzzy::minmin(float a, float b, float c) {
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

SimplyFuzzy::~SimplyFuzzy()
{
	cleanVariables();
}

void SimplyFuzzy::cleanVariables() {
	Node* cur;
	for (int i = 0; i < 6; i++)
	{
		cur = &rules[i];
		while (rulesTails[i] != &rules[i])
		{

			if (cur->next->next == NULL) {
				rulesTails[i] = cur;
				free(cur->next);
				cur->next = NULL;
				cur = &rules[i];
			}
			else {
				cur = cur->next;
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		outPutTerms[i].updateTerm(1.0);
		outputValues[i] = 0;
	}
}