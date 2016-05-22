//Context Switch Test
//Christopher Bird
//May 17 2016

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <math.h>
#include <iomanip>

//#define numTests 1

using namespace std;

chrono::steady_clock::time_point introTime = chrono::high_resolution_clock::now();
chrono::steady_clock::time_point outroTime = chrono::high_resolution_clock::now();

void useless() {
	introTime = chrono::high_resolution_clock::now();
	this_thread::sleep_for(chrono::seconds(1));
	outroTime = chrono::high_resolution_clock::now();
}

int main() {
	chrono::duration<double, nano> fullTime = chrono::nanoseconds(0);
	chrono::duration<double, nano> fullTimeMin = chrono::seconds(10);
	chrono::duration<double, nano> fullTimeMax = chrono::nanoseconds(0);
	chrono::duration<double, nano> fullTimeAccum = chrono::nanoseconds(0);
	chrono::duration<double, nano> insideTime = chrono::nanoseconds(0);
	chrono::duration<double, nano> insideTimeMin = chrono::seconds(10);
	chrono::duration<double, nano> insideTimeMax = chrono::nanoseconds(0);
	chrono::duration<double, nano> insideTimeAccum = chrono::nanoseconds(0);
	chrono::duration<double, nano> invokeTime = chrono::nanoseconds(0);
	chrono::duration<double, nano> invokeTimeMin = chrono::seconds(10);
	chrono::duration<double, nano> invokeTimeMax = chrono::nanoseconds(0);
	chrono::duration<double, nano> invokeTimeAccum = chrono::nanoseconds(0);
	chrono::duration<double, nano> returnTime = chrono::nanoseconds(0);
	chrono::duration<double, nano> returnTimeMin = chrono::seconds(10);
	chrono::duration<double, nano> returnTimeMax = chrono::nanoseconds(0);
	chrono::duration<double, nano> returnTimeAccum = chrono::nanoseconds(0);
	double * fullArray;
	double * insideArray;
	double * invokeArray;
	double * returnArray;
	int numValues = 4;
	int testCases[4] = { 1, 10, 100, 1000 };
	double testResults[4][4];

	int numTests = 1;
	int x;
	/*cout << "Please enter number of tests as an integer." << endl;
	cin >> x;
	while (cin.fail() || x <= 0) {
			cout << "Please enter an integer greater than 0." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> x;
	}
	numTests = x;*/

	for (int j = 0; j < numValues; ++j) {
		numTests = testCases[j];
		cout << "Calculating Avg, Min, Max, and Std Dev for " << testCases[j] << " tests" << endl;
		fullArray = new double[numTests];
		insideArray = new double[numTests];
		invokeArray = new double[numTests];
		returnArray = new double[numTests];

		for (int i = 0; i < numTests; ++i) {
			chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
			useless();
			chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();

			//Work with all values found during tests, fill accumulator, find min/max
			fullTime = chrono::duration_cast<chrono::duration<double, nano>>(end - start);
			fullTimeAccum += fullTime;
			if (fullTime.count() < fullTimeMin.count())
				fullTimeMin = fullTime;
			if (fullTime.count() > fullTimeMax.count())
				fullTimeMax = fullTime;
			fullArray[i] = fullTime.count();

			insideTime = chrono::duration_cast<chrono::duration<double, nano>>(outroTime - introTime);
			insideTimeAccum += insideTime;
			if (insideTime.count() < insideTimeMin.count())
				insideTimeMin = insideTime;
			if (insideTime.count() > insideTimeMax.count())
				insideTimeMax = insideTime;
			insideArray[i] = insideTime.count();

			invokeTime = chrono::duration_cast<chrono::duration<double, nano>>(introTime - start);
			invokeTimeAccum += invokeTime;
			if (invokeTime.count() < invokeTimeMin.count())
				invokeTimeMin = invokeTime;
			if (invokeTime.count() > invokeTimeMax.count())
				invokeTimeMax = invokeTime;
			invokeArray[i] = invokeTime.count();

			returnTime = chrono::duration_cast<chrono::duration<double, nano>>(end - outroTime);
			returnTimeAccum += returnTime;
			if (returnTime.count() < returnTimeMin.count())
				returnTimeMin = returnTime;
			if (returnTime.count() > returnTimeMax.count())
				returnTimeMax = returnTime;
			returnArray[i] = returnTime.count();

			cout << "-";
		}
		//Find average for each of the four main values
		chrono::duration<double, nano> fullTimeAvg = fullTimeAccum / numTests;
		chrono::duration<double, nano> insideTimeAvg = insideTimeAccum / numTests;
		chrono::duration<double, nano> invokeTimeAvg = invokeTimeAccum / numTests;
		chrono::duration<double, nano> returnTimeAvg = returnTimeAccum / numTests;
		double fullAccumS = 0.0;
		double insideAccumS = 0.0;
		double invokeAccumS = 0.0;
		double returnAccumS = 0.0;

		for (int i = 0; i < numTests; ++i) {
			//Subtract avg from each value in array and square the result
			fullAccumS += pow((fullArray[i] - fullTimeAvg.count()), 2.0);
			insideAccumS += pow((insideArray[i] - insideTimeAvg.count()), 2.0);
			invokeAccumS += pow((invokeArray[i] - invokeTimeAvg.count()), 2.0);
			returnAccumS += pow((returnArray[i] - returnTimeAvg.count()), 2.0);
		}
		double fullStdDev = pow((fullAccumS / numTests), 0.5);
		double fullStdDevPerc = (fullStdDev / fullTimeAvg.count()) * 100;
		testResults[0][j] = fullStdDevPerc;
		double insideStdDev = pow((insideAccumS / numTests), 0.5);
		double insideStdDevPerc = (insideStdDev / insideTimeAvg.count()) * 100;
		testResults[1][j] = insideStdDevPerc;
		double invokeStdDev = pow((invokeAccumS / numTests), 0.5);
		double invokeStdDevPerc = (invokeStdDev / invokeTimeAvg.count()) * 100;
		testResults[2][j] = invokeStdDevPerc;
		double returnStdDev = pow((returnAccumS / numTests), 0.5);
		double returnStdDevPerc = (returnStdDev / returnTimeAvg.count()) * 100;
		testResults[3][j] = returnStdDevPerc;
		//Find mean of differences and square root

		double fullMaxDev = (fullTimeMax.count() - fullTimeAvg.count()) / fullStdDev;
		double fullMinDev = (fullTimeAvg.count() - fullTimeMin.count()) / fullStdDev;
		double insideMaxDev = (insideTimeMax.count() - insideTimeAvg.count()) / insideStdDev;
		double insideMinDev = (insideTimeAvg.count() - insideTimeMin.count()) / insideStdDev;
		double invokeMaxDev = (invokeTimeMax.count() - invokeTimeAvg.count()) / invokeStdDev;
		double invokeMinDev = (invokeTimeAvg.count() - invokeTimeMin.count()) / invokeStdDev;
		double returnMaxDev = (returnTimeMax.count() - returnTimeAvg.count()) / returnStdDev;
		double returnMinDev = (returnTimeAvg.count() - returnTimeMin.count()) / returnStdDev;


		//Print important info
		cout << fixed << endl << "Full Time Avg: " << fullTimeAvg.count() << " ns" << endl;
		cout << "Full Time Max: " << fullTimeMax.count() << " ns" << endl;
		cout << "Full Time Min: " << fullTimeMin.count() << " ns" << endl;
		cout << "Full Time Std Dev: " << fullStdDev << " ns" << endl;
		cout << "Full Time Std Dev Percent: " << fullStdDevPerc << endl;
		cout << "# Std Devs from Avg (Max): " << fullMaxDev << endl;
		cout << "# Std Devs from Avg (Min): " << fullMinDev << endl << endl;

		cout << "Between Switches Avg: " << insideTimeAvg.count() << " ns" << endl;
		cout << "Between Switches Max: " << insideTimeMax.count() << " ns" << endl;
		cout << "Between Switches Min: " << insideTimeMin.count() << " ns" << endl;
		cout << "Between Switches Std Dev: " << insideStdDev << " ns" << endl;
		cout << "Between Switches Std Dev Percent: " << insideStdDevPerc << endl;
		cout << "# Std Devs from Avg (Max): " << insideMaxDev << endl;
		cout << "# Std Devs from Avg (Min): " << insideMinDev << endl << endl;

		cout << "Invoke Time Avg: " << invokeTimeAvg.count() << " ns" << endl;
		cout << "Invoke Time Max: " << invokeTimeMax.count() << " ns" << endl;
		cout << "Invoke Time Min: " << invokeTimeMin.count() << " ns" << endl;
		cout << "Invoke Time Std Dev: " << invokeStdDev << " ns" << endl;
		cout << "Invoke Time Std Dev Percent: " << invokeStdDevPerc << endl;
		cout << "# Std Devs from Avg (Max): " << invokeMaxDev << endl;
		cout << "# Std Devs from Avg (Min): " << invokeMinDev << endl << endl;

		cout << "Return Time Avg: " << returnTimeAvg.count() << " ns" << endl;
		cout << "Return Time Max: " << returnTimeMax.count() << " ns" << endl;
		cout << "Return Time Min: " << returnTimeMin.count() << " ns" << endl;
		cout << "Return Time Std Dev: " << returnStdDev << " ns" << endl;
		cout << "Return Time Std Dev Percent: " << returnStdDevPerc << endl;
		cout << "# Std Devs from Avg (Max): " << returnMaxDev << endl;
		cout << "# Std Devs from Avg (Min): " << returnMinDev << endl << endl;
	}

	cout << "FINAL RESULTS: " << endl;
	for (int i = 0; i < 4; ++i) {
		int tempTests = (i * 10 != 0) ? pow(10, i) : 0;
		cout << "For " << tempTests << " tests: " << endl;
		cout << "Full Std Dev Perc: " << testResults[0][i] << endl;
		cout << "Between Switches Std Dev Perc: " << testResults[1][i] << endl;
		cout << "Invoke Time Std Dev Perc: " << testResults[2][i] << endl;
		cout << "Return Time Std Dev Perc: " << testResults[3][i] << endl;
	}


	cin.ignore();
	string userInp;
	getline(cin, userInp);

	return 0;
}