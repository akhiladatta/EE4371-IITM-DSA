/*
Author: Atul Balaji (EE16B002)
Date: 11-11-2018
Question 5 - End Sem
*/

/*
In this question, we are required to find the best investment strategy for the given parameters.
For this, we make use of a dynamic programming approach to update the return table stepwise.
First, the amount in the first row is assigned as S for all the investment schemes. 
Using this, we calculate the return at the year end, for all years and which scheme in the previous year has led to this. 
After this, at the last year, we find the scheme which has yielded maximum return. 
This is selected and the retTable is made zero for the other instruments in that row.
Then, we backtrack to all previous years to find the index from which this has originated. 
Finally, we end up with a table having the optimal scheme, with one non zero amount in a row. 
*/

#include <iostream>
#include <iomanip>
using namespace std;

// Backtrack function to update values of retTable based on the max_index
void backtrack(int t,int &max_index,int n,float **retTable, int **parent_idx)
{
    int i,j;
    for (i=t-1;i>=0;i--)
    {
        for (j=0;j<n;j++)
        {
            if (j != max_index)
                retTable[i][j] = 0;                 // Make the entries of retTable corresponding to other indices to zero.
        }
        max_index = parent_idx[i][max_index];
    }
}

// Find the maximum index for the last row (year), which has been stored in curr_arr
void find_max(int &max_index,int t,int n,float **retTable,float **rr,float *curr_arr)
{   
    int max, i;
    max = retTable[t-1][0]*rr[t-1][0];
    max_index = 0;

    for(i=0;i<n;i++)
    {
        if(curr_arr[i] > max)
        {
            max = retTable[t-1][i]*rr[t-1][i];
            max_index = i;
        }
    }
}

// Function to ouptut the optimal strategy
void strategy(double S, int t, int n, float f)
{
    int **parent_idx = new int*[t];
    float **retTable = new float*[t];
    float *prev_arr = new float[n];
    float *curr_arr = new float[n];
    float **rr = new float*[t];                     // array to store all the returns for investment options

	// Read returns matrix
	for(int i=0; i<t; i++)
    {   
        rr[i] = new float[n];
		for(int j=0; j<n; j++)
        {
			cin >> rr[i][j];                    	// (i+1)th year and (j+1)th investment option
		}
	}

    int i,j,k,l;
    for (i=0;i<t;i++)
    {
        retTable[i] = new float[n];
        parent_idx[i] = new int[n];
        for(j=0;j<n;j++)
        {
            prev_arr[j] = 0;
            curr_arr[j] = 0;
            if(i == 0)
                retTable[i][j] = S;
            else
                retTable[i][j] = 0;
        }
    }
    
    float max = 0;
    int max_index;

    // Update the retTable initially
    for(i=0;i<t-1;i++)
    {
        for(k=0;k<n;k++)
        {
            for(j=0;j<n;j++)
            {    
                prev_arr[j] = retTable[i][j]*rr[i][j];
                // Changing instrument incurs fee
                if(j!=k && ((prev_arr[j] - f)*rr[i+1][k] > curr_arr[k]))
                {
                    parent_idx[i+1][k] = j;
                    curr_arr[k] = (prev_arr[j]-f)*rr[i+1][k];
                    retTable[i+1][k] = (prev_arr[j]-f);
                }
                // Retaining instrument
                else if( j==k && (prev_arr[j]*rr[i+1][k] > curr_arr[k]))
                {
                    parent_idx[i+1][k] = j;
                    curr_arr[k] = prev_arr[j]*rr[i+1][k];
                    retTable[i+1][k] = prev_arr[j];
                }
            }
        }
    }

    // Find max value and max index for last row'
    find_max(max_index,t,n,retTable,rr,curr_arr);
    int max_index_final = max_index;

    // Backtrack from last year, to find the appropriate investment for each year 
    backtrack(t,max_index,n,retTable,parent_idx);

    // Print the return table 
    for(int i=0; i<t; i++)
    {
		for(int j=0; j<n; j++)
			cout << fixed << setprecision(5) << retTable[i][j] << " ";
		cout << endl;	
	}
    // cout << fixed << setprecision(5) << retTable[t-1][max_index_final]*rr[t-1][max_index_final];
    // cout << endl;
}

int main()
{
	int t,n;
	float f;
	double S;

	cin >> S;	            // total investment
	cin >> t;	            // no of years to invest
	cin >> n;	            // no of instruments to invest in
	cin >> f;	            // fee to be leived if investment instrument is changed (Assumption : for the first year, no fee)

    strategy(S,t,n,f);      // Call the strategy with amount, no.of years, no.of instruments and fees

    return 0;
}