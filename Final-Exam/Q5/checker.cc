#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
	if (argc < 3) {
		cout << "Not enough arguments!" << endl;
		return 1;
	}
	ifstream in1(argv[1]);
	ifstream in2(argv[2]);
	double s;
	in1 >> s;	// total investment
	int t,n;
	int f;
	in1 >> t;	// no of years to invest
	in1 >> n;	// no of instruments to invest in
	in1 >> f;	// fee to be leived if investment instrument is changed (Assumption : for the first year, no fee)
	double *startTable = new double[t*n];
	double *endTable = new double[t*n];
	double *inputSum = new double[t];
	double *rr = new double[t*n]; // array to store all the returns for investment options
	// taking the returns for given years and for no of investments
	for(int i=0; i<t; i++){
		for(int j=0; j<n; j++){
			in1 >> rr[i*n+j];	// (i+1)th year and (j+1)th investment option
		}
	}
	cout << "Start year amounts you have given" << endl;
	for(int i=0; i<t; i++){
		double sum = 0;
		for(int j=0; j<n; j++){
			in2 >> startTable[i*n+j];
			cout << startTable[i*n+j] << " ";
			sum += startTable[i*n+j];
		}
		// cout << "Sum : " << sum << endl;
		cout << endl;
	}
	cout << "End year amounts calculated" << endl;
	for(int i=0; i<t; i++){
		double sum = 0;
		for(int j=0; j<n; j++){
			endTable[i*n+j] = startTable[i*n+j]*rr[i*n+j];
			sum += endTable[i*n+j];
			cout << endTable[i*n+j] << " ";
		}
		inputSum[i] = sum;
		cout << "Sum : " << sum << endl;
		if(sum==0){
			cout << "wrong output from the program" << endl;
			return 1;
		}
	}
	for(int i=1; i<t; i++){
		bool changeFlag;
		double sum = 0;
		for(int j=0; j<n; j++){
			if(startTable[i*n+j]==endTable[(i-1)*n+j]){
				changeFlag = false;
			}
			else{
				changeFlag = true;
			}
			sum += startTable[i*n+j];
		}
		if(changeFlag){
			if(sum != (inputSum[i-1]-f)){
				// cout << sum << " " << inputSum[i] << endl;
				cout << "Checker Failed" << endl;
				return 1;
			}
		}
		else{
			if(sum != inputSum[i-1]){
				cout << "Checker Failed" << endl;
				return 1;
			}
		}
	}
	cout << "Checker Passed" << endl;
	// for(int i=0; i<t; i++){
	// 	cout << inputSum[i] << endl;
	// }

    return 0;
}