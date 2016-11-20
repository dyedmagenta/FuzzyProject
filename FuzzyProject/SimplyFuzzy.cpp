#include "SimplyFuzzy.h"

SimplyFuzzy::SimplyFuzzy()
{
	/*
	INPUTS					Outputs
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
	outPutTerms[0].setPoints(-255,0);
	outPutTerms[0].setPoints(-225,1);
	outPutTerms[0].setPoints(-185,2);
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

	for (int i = 0; i < 6; i++) {
		centers[i] = (float)(outPutTerms[i].getPoint(3) - outPutTerms[i].getPoint(0)) / (float)2.0 + outPutTerms[i].getPoint(0);
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



	float ffmax = 0; // maxmax(5);
	float ffmed = 0; // maxmax(4);
	float ffmin = 0; // maxmax(3);
	float bbmin = 0; // maxmax(2);
	float bbmed = 0; // maxmax(1);
	float bbmax = 0; // maxmax(0);
	 
	float fmax = 0;
	float fmed = 0;
	float fmin = 0;
	float bmin = 0;
	float bmed = 0;
	float bmax = 0;

	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[3], midValues[3], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[3], midValues[3], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[3], midValues[3], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[3], midValues[3], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[3], midValues[2], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[3], midValues[2], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[3], midValues[2], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[3], midValues[2], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmin = minmin(leftValues[3], midValues[1], rightValues[3]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[3], midValues[1], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[3], midValues[1], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[3], midValues[1], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[3], midValues[0], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[2], midValues[3], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[2], midValues[3], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[2], midValues[3], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[2], midValues[3], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[2], midValues[2], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[2], midValues[2], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[2], midValues[2], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[2], midValues[2], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[2], midValues[1], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[2], midValues[1], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[2], midValues[1], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[2], midValues[1], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[2], midValues[0], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[2], midValues[0], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[2], midValues[0], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[2], midValues[0], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[1], midValues[3], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;

	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[1], midValues[3], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[1], midValues[3], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[1], midValues[3], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[1], midValues[2], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;

	}
	/*BMID*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		bmed = minmin(leftValues[1], midValues[2], rightValues[2]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[1], midValues[2], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[1], midValues[2], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[1], midValues[1], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[1], midValues[1], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[1], midValues[1], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[1], midValues[1], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[1], midValues[0], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[1], midValues[0], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		bmed = minmin(leftValues[1], midValues[0], rightValues[1]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[1], midValues[0], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[0], midValues[3], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[0], midValues[3], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[0], midValues[3], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[0], midValues[3], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[0], midValues[2], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[0], midValues[2], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[0], midValues[2], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[0], midValues[2], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[0], midValues[1], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[0], midValues[1], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[0], midValues[1], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[0], midValues[1], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[0], midValues[0], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[0], midValues[0], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[0], midValues[0], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[0], midValues[0], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}


	float cog = (float)(bbmax*centers[0] + bbmed*centers[1] + bbmin*centers[2] + ffmin*centers[3] + ffmed*centers[4] + ffmax*centers[5]) / (bbmax + bbmed + bbmin + ffmin + ffmed + ffmax);

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

	float ffmax = 0; // maxmax(5);
	float ffmed = 0; // maxmax(4);
	float ffmin = 0; // maxmax(3);
	float bbmin = 0; // maxmax(2);
	float bbmed = 0; // maxmax(1);
	float bbmax = 0; // maxmax(0);

	float fmax = 0;
	float fmed = 0;
	float fmin = 0;
	float bmin = 0;
	float bmed = 0;
	float bmax = 0;

	//F F
	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[3], midValues[3], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[3], midValues[3], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmax = minmin(leftValues[3], midValues[3], rightValues[1]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[3], midValues[3], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//F M
	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[3], midValues[2], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[3], midValues[2], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmax = minmin(leftValues[3], midValues[2], rightValues[1]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[3], midValues[2], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//F C
	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmax = minmin(leftValues[3], midValues[1], rightValues[3]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[3], midValues[1], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmax = minmin(leftValues[3], midValues[1], rightValues[1]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[3] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[3], midValues[1], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//F V
	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[3] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[3], midValues[0], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//M F
	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[2], midValues[3], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[2], midValues[3], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[2], midValues[3], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[2] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[2], midValues[3], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//M M
	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[2], midValues[2], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[2], midValues[2], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[2], midValues[2], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[2], midValues[2], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//M C
	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmin = minmin(leftValues[2], midValues[1], rightValues[3]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[2], midValues[1], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmin = minmin(leftValues[2], midValues[1], rightValues[1]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[2] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[2], midValues[1], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//M V
	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[2], midValues[0], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmax = minmin(leftValues[2], midValues[0], rightValues[2]);
		if (ffmax < fmax)
			ffmax = fmax;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[2], midValues[0], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[2] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[2], midValues[0], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//C F
	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		fmin = minmin(leftValues[1], midValues[3], rightValues[3]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[1], midValues[3], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[1], midValues[3], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[1], midValues[3], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//C M
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		fmin = minmin(leftValues[1], midValues[2], rightValues[3]);
		if (ffmin < fmin)
			ffmin = fmin;
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmed = minmin(leftValues[1], midValues[2], rightValues[2]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[1], midValues[2], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[1], midValues[2], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//C C
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		fmin = minmin(leftValues[1], midValues[1], rightValues[3]);
		if (ffmin < fmin)
			ffmin = fmin;
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		bmed = minmin(leftValues[1], midValues[1], rightValues[2]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[1], midValues[1], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[1], midValues[1], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//C V
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		fmed = minmin(leftValues[1], midValues[0], rightValues[3]);
		if (ffmed < fmed)
			ffmed = fmed;
	}
	/*fmid*/
	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		bmed = minmin(leftValues[1], midValues[0], rightValues[2]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		fmed = minmin(leftValues[1], midValues[0], rightValues[1]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	if (leftValues[1] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		bmed = minmin(leftValues[1], midValues[0], rightValues[0]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	//V F
	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[0], midValues[3], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[0], midValues[3], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[0], midValues[3], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[0] != 0 && midValues[3] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[0], midValues[3], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//V M
	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[0], midValues[2], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[0], midValues[2], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[0], midValues[2], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[0] != 0 && midValues[2] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[0], midValues[2], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//V C
	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[0], midValues[1], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[0], midValues[2], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[0], midValues[1], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[0] != 0 && midValues[1] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[0], midValues[1], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}

	//V V
	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[3] != 0) {
		bmed = minmin(leftValues[0], midValues[0], rightValues[3]);
		if (bbmed < bmed)
			bbmed = bmed;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[2] != 0) {
		fmin = minmin(leftValues[0], midValues[0], rightValues[2]);
		if (ffmin < fmin)
			ffmin = fmin;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[1] != 0) {
		bmin = minmin(leftValues[0], midValues[0], rightValues[1]);
		if (bbmin < bmin)
			bbmin = bmin;
	}

	if (leftValues[0] != 0 && midValues[0] != 0 && rightValues[0] != 0) {
		fmed = minmin(leftValues[0], midValues[0], rightValues[0]);
		if (ffmed < fmed)
			ffmed = fmed;
	}
/*
	outPutTerms[0].setMax(bbmax);
	outPutTerms[1].setMax(bbmed);
	outPutTerms[2].setMax(bbmin);
	outPutTerms[3].setMax(ffmin);
	outPutTerms[4].setMax(ffmed);
	outPutTerms[5].setMax(ffmax);*/




	float cog = (bbmax*centers[0] + bbmed*centers[1] + bbmin*centers[2] + ffmin*centers[3] + ffmed*centers[4] + ffmax*centers[5]) / (bbmax + bbmed + bbmin + ffmin + ffmed + ffmax);

	return cog;
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

void SimplyFuzzy::resetOutput() {
	for (int i = 0; i < 6; i++)
	{
		outPutTerms[i].setMax(1.0);
		updateOutput(i, 1.0);
	}
}

/*
	Calculates x of the after giving new y, 
	used for getting fuzzy outputs
*/
void SimplyFuzzy::updateOutput(int outputNum, float y) {
	if (y == 0.0) return;
	float a = outPutTerms[outputNum].getMax() / (outPutTerms[outputNum].getPoint(1) - outPutTerms[outputNum].getPoint(0));
	float b = -a * outPutTerms[outputNum].getPoint(0);
	int nPoint = (int) ((y - b) / a);
	outPutTerms[outputNum].setPoints(nPoint, 1);
	nPoint = outPutTerms[outputNum].getPoint(3) + (outPutTerms[outputNum].getPoint(1) - outPutTerms[outputNum].getPoint(0));
	outPutTerms[outputNum].setPoints(nPoint, 2);
}

SimplyFuzzy::~SimplyFuzzy() 
{
}
