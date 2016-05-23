//Context Switch Data Main
//Christopher Bird 
//22 May 2016

#include <iostream>
#include "switchData.h"
#include <string>
#include <iomanip>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;

chrono::steady_clock::time_point introTime = chrono::high_resolution_clock::now();
chrono::steady_clock::time_point outroTime = chrono::high_resolution_clock::now();
int i = 0;

void uselessFunct() {
	introTime = chrono::high_resolution_clock::now();
	this_thread::sleep_for(chrono::milliseconds(1));
	outroTime = chrono::high_resolution_clock::now();
}

int main() {
	int numValues = 100;
	switchData fourTimes[4];
	for (int i = 0; i < 4; ++i)
		fourTimes[i].setValues(numValues);
	chrono::duration<double, nano> currTimes[4];
	string stringName[4] = { "Full Time", "Between Switches", "Invoke Switch", "Return Switch" };
	int numTimes = 4;
	for (int i = 0; i < numValues; ++i) {
		
		chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
		uselessFunct();
		chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();
		
		currTimes[0] = end - start;
		currTimes[1] = outroTime - introTime;
		currTimes[2] = introTime - start;
		currTimes[3] = end - outroTime;

		for (int j = 0; j < numTimes; ++j) {
			fourTimes[j].addValue(currTimes[j]);
			fourTimes[j].addToAccum(currTimes[j]);
			fourTimes[j].checkMin(currTimes[j]);
			fourTimes[j].checkMax(currTimes[j]);
		}
	}
	for (int i = 0; i < numTimes; ++i) {
		//fourTimes[i].resetIndex();
		fourTimes[i].calcAvg();
		fourTimes[i].calcStdDev();
		cout << "Data for " << stringName[i] << endl;
		fourTimes[i].printData();
	}

	string userInp;
	getline(cin, userInp);
	return 0;
}