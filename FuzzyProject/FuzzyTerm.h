#pragma once

#ifndef FUZZYTERM_H
#define FUZZYTERM_H

struct Point {

	float x;
	float y;

	Point(float xX, float yY) :x(xX), y(yY) {};
	Point() : x(0), y(0) {};
};

class FuzzyTerm
{
public:
	//termTypes[n] n - number of points, 0 - no points, 1 - singleton, 2 slope, 3 triangle, 4 trapezoid
	const char termTypes[5] = { 'N', 'S', 'L', 't', 'T' };

	FuzzyTerm();
	FuzzyTerm(Point a);
	FuzzyTerm(Point a, Point b);
	FuzzyTerm(Point a, Point b, Point c);
	FuzzyTerm(Point a, Point b, Point c, Point d);
	Point getA();
	Point getB();
	Point getC();
	Point getD();
	char getTermType();
private:
	char termType;
	
	Point a;
	Point b;
	Point c;
	Point d;
	float* term;

};

#endif // !FUZZYTERM_H