#include <iostream>
using namespace std;

int main(){
	double s;
	cin >> s;	// total investment
	int t,n;
	float f;
	cin >> t;	// no of years to invest
	cin >> n;	// no of instruments to invest in
	cin >> f;	// fee to be leived if investment instrument is changed (Assumption : for the first year, no fee)
	float *retTable = new float[t*n];
	float *rr = new float[t*n]; // array to store all the returns for investment options
	// taking the returns for given years and for no of investments
	for(int i=0; i<t; i++){
		for(int j=0; j<n; j++){
			cin >> rr[i*n+j];	// (i+1)th year and (j+1)th investment option
		}
	}
	
	//
	// YOUR CODE HERE
	//

	for(int i=0; i<t; i++){
		for(int j=0; j<n; j++)
			cout << retTable[i*n+j] << " ";
		cout << endl;	
	}

    return 0;
}