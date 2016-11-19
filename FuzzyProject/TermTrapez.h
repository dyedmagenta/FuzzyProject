#pragma once
class TermTrapez
{
public:
	TermTrapez();
	~TermTrapez();
	float getValue(int x);
	void setPoints(int point, int pointNum);
	int getPoint(int pointNum);
private:
	int points[4] = { 0, 0, 0, 0 };
};

