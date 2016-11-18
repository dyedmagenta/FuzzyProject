#include "FuzzyTerm.h"


FuzzyTerm::FuzzyTerm() {
	this->a = Point(0, 0);
	this->b = Point(0, 0);
	this->c = Point(0, 0);
	this->d = Point(0, 0);
	//termTypes[n] n - number of points, 0 - no points, 1 - singleton, 2 slope, 3 triangle, 4 trapezoid
	this->termType = this->termTypes[0];
}
FuzzyTerm::FuzzyTerm(Point a) {
	this->a = a;
	this->termType = this->termTypes[1];
}
FuzzyTerm::FuzzyTerm(Point a, Point b) {
	this->a = a;
	this->b = b;
	this->termType = this->termTypes[2];
}
FuzzyTerm::FuzzyTerm(Point a, Point b, Point c) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->termType = this->termTypes[3];
}
FuzzyTerm::FuzzyTerm(Point a, Point b, Point c, Point d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->termType = this->termTypes[4];
}

Point FuzzyTerm::getA() {
	return this->a;
}
Point FuzzyTerm::getB() {
	return this->b;
}
Point FuzzyTerm::getC() {
	return this->c;
}
Point FuzzyTerm::getD() {
	return this->d;
}

char FuzzyTerm::getTermType() {
	return this->termType;
}