//Context Switch Data Org Class
//Christopher Bird 
//22 May 2016

#include <iostream>
#include <iomanip>
#include <chrono>
#include <math.h>
#include "switchData.h"

using namespace std;

switchData::switchData() {
	//testValues = new double[numValues];
	//numTests = numValues;
	currIndex = 0;
	min = chrono::seconds(10);
	max = chrono::nanoseconds(0);
	accum = chrono::nanoseconds(0);
	stdDevAccum = 0.0;
	average = chrono::nanoseconds(0);
	stdDev = 0.0;
	stdDevPerc = 0.0;
}

switchData::~switchData() {
	delete testValues;
}

void switchData::setValues(int numValues) {
	testValues = new chrono::duration<double, nano>[numValues];
	numTests = numValues;
}

void switchData::addToAccum(chrono::duration<double, nano> current) {
	accum += current;
}

void switchData::addToSAccum(chrono::duration<double, nano> current) {
	//stdDevAccum += current.count();
}

void switchData::addValue(chrono::duration<double, nano> current) {
	testValues[currIndex] = current;
	currIndex++;
}

void switchData::checkMax(chrono::duration<double, nano> current) {
	if (current > max)
		max = current;
}

void switchData::checkMin(chrono::duration<double, nano> current) {
	if (current < min)
		min = current;
}

void switchData::calcAvg() {
	average = accum / numTests;
}

void switchData::calcStdDev() {
	for (int i = 0; i < numTests; ++i) {
		stdDevAccum += pow((testValues[i] - average).count(), 2.0);
	}
	stdDev = pow((stdDevAccum / numTests), 0.5);
}

void switchData::printData() {
	cout << fixed << "Average: " << average.count() << " ns" << endl;
	cout << "Min: " << min.count() << " ns" << endl;
	cout << "Max: " << max.count() << " ns" << endl;
	cout << "Std Dev: " << stdDev << " ns" << endl;
	cout << "Std Dev is " << (stdDev / average.count()) * 100 << "% of average" << endl << endl;
}

void switchData::printTest() {
	cout << fixed << testValues[currIndex].count() << "**" << endl;
}
