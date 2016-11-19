#pragma once
class TermTrapez
{
public:
	TermTrapez();
	~TermTrapez();
	float getValue(int x);
	void setPoints(int point, int pointNum);
	int getPoint(int pointNum);
	void setMax(float m);
	float getMax();
private:
	int points[4] = { 0, 0, 0, 0 };
	float max = 1.0;
};

