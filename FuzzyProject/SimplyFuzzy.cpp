#include "SimplyFuzzy.h"

#include<iostream>


SimplyFuzzy::SimplyFuzzy()
{

	inputTerms[0].setPoints(-10, 0);
	inputTerms[0].setPoints(0, 1);
	inputTerms[0].setPoints(0, 2);
	inputTerms[0].setPoints(10, 3);
	
	inputTerms[1].setPoints(0, 0);
	inputTerms[1].setPoints(10, 1);
	inputTerms[1].setPoints(20, 2);
	inputTerms[1].setPoints(30, 3);

	inputTerms[2].setPoints(20, 0);
	inputTerms[2].setPoints(30, 1);
	inputTerms[2].setPoints(40, 2);
	inputTerms[2].setPoints(50, 3);

	inputTerms[3].setPoints(45, 0);
	inputTerms[3].setPoints(55, 1);
	inputTerms[3].setPoints(200, 2);
	inputTerms[3].setPoints(200, 3);

	outPutTerms[0].setPoints(-305,0);
	outPutTerms[0].setPoints(-255,1);
	outPutTerms[0].setPoints(-255,2);
	outPutTerms[0].setPoints(-205, 3);

	outPutTerms[1].setPoints(-200, 0);
	outPutTerms[1].setPoints(-150, 1);
	outPutTerms[1].setPoints(-150, 2);
	outPutTerms[1].setPoints(-100, 3);

	outPutTerms[2].setPoints(-105, 0);
	outPutTerms[2].setPoints(-55, 1);
	outPutTerms[2].setPoints(-55, 2);
	outPutTerms[2].setPoints(-5, 3);

	outPutTerms[5].setPoints(305, 0);
	outPutTerms[5].setPoints(255, 1);
	outPutTerms[5].setPoints(255, 2);
	outPutTerms[5].setPoints(205, 3);

	outPutTerms[4].setPoints(200, 0);
	outPutTerms[4].setPoints(150, 1);
	outPutTerms[4].setPoints(150, 2);
	outPutTerms[4].setPoints(100, 3);

	outPutTerms[3].setPoints(105, 0);
	outPutTerms[3].setPoints(55, 1);
	outPutTerms[3].setPoints(55, 2);
	outPutTerms[3].setPoints(5, 3);

}


int SimplyFuzzy::getLeftOutput(int left, int mid, int right) {
	/*
		[0] - VeryClose
		[1] - Close
		[2] - Med
		[3] - Far	
	*/
	//Values from each term
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

	std::vector<float> fmax;
	std::vector<float> fmed;
	std::vector<float> fmin;
	std::vector<float> bmin;
	std::vector<float> bmed;
	std::vector<float> bmax;

	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[3], midValues[3], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[3], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[3], midValues[3], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[3], midValues[3], rightValues[0]));
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[2], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[2], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[3], midValues[2], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[3], midValues[2], rightValues[0]));
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmin.push_back(minmin(leftValues[3], midValues[1], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[1], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[3], midValues[1], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[3], midValues[1], rightValues[0]));
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[0], rightValues[3]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[0], rightValues[2]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmed.push_back(minmin(leftValues[3], midValues[0], rightValues[1]));
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[3], midValues[0], rightValues[0]));
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[2], midValues[3], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmin.push_back(minmin(leftValues[2], midValues[3], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[3], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[3], rightValues[0]));
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[2], midValues[2], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmin.push_back(minmin(leftValues[2], midValues[2], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		bmin.push_back(minmin(leftValues[2], midValues[2], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[2], rightValues[0]));
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[2], midValues[1], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmin.push_back(minmin(leftValues[2], midValues[1], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		bmin.push_back(minmin(leftValues[2], midValues[1], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[1], rightValues[0]));
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[0], rightValues[3]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmin.push_back(minmin(leftValues[2], midValues[0], rightValues[2]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[0], rightValues[1]));
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[2], midValues[0], rightValues[0]));
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[1], midValues[3], rightValues[3]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax.push_back(minmin(leftValues[1], midValues[3], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[3], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		fmed.push_back(minmin(leftValues[1], midValues[3], rightValues[0]));
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[1], midValues[2], rightValues[3]));
	}
	/*BMID*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[2], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[2], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[2], rightValues[0]));
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmax.push_back(minmin(leftValues[1], midValues[1], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[1], midValues[1], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[1], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		fmed.push_back(minmin(leftValues[1], midValues[1], rightValues[0]));
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[0], rightValues[3]));
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmed.push_back(minmin(leftValues[1], midValues[0], rightValues[2]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		bmed.push_back(minmin(leftValues[1], midValues[0], rightValues[1]));
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		fmed.push_back(minmin(leftValues[1], midValues[0], rightValues[0]));
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[0], midValues[3], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax.push_back(minmin(leftValues[0], midValues[3], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[0], midValues[3], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[0], midValues[3], rightValues[0]));
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[0], midValues[2], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmax.push_back(minmin(leftValues[0], midValues[2], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[0], midValues[2], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[0], midValues[2], rightValues[0]));
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[0], midValues[1], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmax.push_back(minmin(leftValues[0], midValues[1], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[0], midValues[1], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[0], midValues[1], rightValues[0]));
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed.push_back(minmin(leftValues[0], midValues[0], rightValues[3]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmax.push_back(minmin(leftValues[0], midValues[0], rightValues[2]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmin.push_back(minmin(leftValues[0], midValues[0], rightValues[1]));
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed.push_back(minmin(leftValues[0], midValues[0], rightValues[0]));
	}

	float ffmax = maxmax(fmax);
	float ffmed = maxmax(fmed);
	float ffmin = maxmax(fmin);
	float bbmin = maxmax(bmin);
	float bbmed = maxmax(bmed);
	float bbmax = maxmax(bmax);

	TermTrapez outPutTerms[6];

	outPutTerms[0].setMax(bbmax);
	outPutTerms[1].setMax(bbmed);
	outPutTerms[2].setMax(bbmin);
	outPutTerms[3].setMax(ffmin);
	outPutTerms[4].setMax(ffmed);
	outPutTerms[5].setMax(ffmax);

	updateOutput(0, bbmax);
	updateOutput(1, bbmed);
	updateOutput(2, bbmin);
	updateOutput(3, ffmin);
	updateOutput(4, ffmed);
	updateOutput(5, ffmax);

	float cog = (bbmax*outPutTerms[0].getPoint(1) + bbmed*outPutTerms[1].getPoint(1) + bbmin*outPutTerms[2].getPoint(1) + ffmin*outPutTerms[3].getPoint(1) + ffmed*outPutTerms[4].getPoint(1) + ffmax*outPutTerms[1].getPoint(1)) / (bbmax + bbmed + bbmin + ffmin + ffmed + ffmax);
	return (int)cog;
}


float SimplyFuzzy::maxmax(std::vector<float> &v) {
	std::vector<float>* myV = &v;

	int siz = std::distance(myV->begin(), myV->end());

	float max = 0;

	for (int i = 0; i < siz; i++) {
		if (myV->at(i) > max)
			max = myV->at(i);
	}
	return max;
}



float SimplyFuzzy::minmin(float a, float b, float c) {
	return std::fminf(a, std::fminf(b, c));
}

void SimplyFuzzy::resetOutput() {
	for (int i = 0; i < 6; i++)
	{
		outPutTerms[i].setMax(1.0);
		updateOutput(i, 1.0);
	}
}

void SimplyFuzzy::updateOutput(int outputNum, float y) {
	if (y == 0.0) return;
	float a = 1.0 / (outPutTerms[outputNum].getPoint(1) - outPutTerms[outputNum].getPoint(0));
	float b = -a * outPutTerms[outputNum].getPoint(0);
	int nPoint = (y - b) / a;
	outPutTerms[outputNum].setPoints(nPoint, 1);
	outPutTerms[outputNum].setPoints(nPoint, 2);
}


SimplyFuzzy::~SimplyFuzzy() {}