//Context Switch Data Org Class
//Christopher Bird 
//22 May 2016

#include<iostream>
#include<chrono>

using namespace std;

class switchData {
public:
	switchData();
	~switchData();
	void setValues(int numValues);
	void addToAccum(chrono::duration<double, nano> current);
	void addToSAccum(chrono::duration<double, nano> current);
	void addValue(chrono::duration<double, nano> current);
	void checkMax(chrono::duration<double, nano> current);
	void checkMin(chrono::duration<double, nano> current);
	inline void resetIndex() { currIndex = 0; }
	void calcAvg();
	void calcStdDev();
	void printData();

private:
	chrono::duration<double, nano> accum;
	double stdDevAccum;
	chrono::duration<double, nano> min;
	chrono::duration<double, nano> max;
	chrono::duration<double, nano> average;
	chrono::duration<double, nano> stdDevAvg;
	int numTests;
	int currIndex;
	double * testValues;
	double stdDev;
	double stdDevPerc;

};