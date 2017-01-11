
#ifndef TERM_H
#define TERM_H
#include <math.h>
/*
 * Can be used for declaring Singleton, Triangle or Trapezoid term 
 * 
 * Example:
		//Setting Singleton A=B=C=D
		Term singleton;
		singleton.setPoints(50, 0); //A
		singleton.setPoints(50, 1); //B
		singleton.setPoints(50, 2); //C
		singleton.setPoints(50, 3); //D
		
		//Setting Triangle A, B=C, D
		Term triangle;
		triangle.setPoints(40, 0); //A
		triangle.setPoints(50, 1); //B
		triangle.setPoints(50, 2); //C
		triangle.setPoints(60, 3); //D
		
		//Setting Trapezoid A, B, C, D
		Term trapezoid;	
		trapezoid.setPoints(40, 0); //A
		trapezoid.setPoints(45, 1); //B
		trapezoid.setPoints(55, 2); //C
		trapezoid.setPoints(60, 3); //D
 *	
 *	Next point should be greater or equal than previous one
 *	A <= B <= C <= D
 */
class Term
{
public:
	float getValue(int x);
	void setPoints(int point, int pointNum);
	int getPoint(int pointNum);
	void setMax(float m);
	float getMax() const;
	void updateTerm(float y);
private:
	int points[4] = { 0, 0, 0, 0 };
	float max = 1.0;
	bool isZero = false;
	int newPoint(int lastPoint, int firstPoint, float y);
};
#endif // !TERM_H
