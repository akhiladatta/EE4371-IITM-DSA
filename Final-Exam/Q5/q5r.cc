#include <stdlib.h>
#include <stdio.h>

using namespace std;

int plan_investment(float** rr,double s, int t, int n, float f)
{    
    int i,j,k,l;
    float max_return = 0;
    float *retTable[t];   // Optimal investment returns at each year for each investment option. (I_ij)
    
    int *I = (int*) malloc(sizeof(int)*n);
    float *temp_a = (float*) malloc(sizeof(float)*n);
    float *temp_b = (float*) malloc(sizeof(float)*n);
    
    for(i=0;i<t;i++)
    {
        retTable[i] = (float*) malloc(sizeof(float)*n);
        for(j=0;j<n;j++)
        {
            I[j] = -1;
            temp_b[j] = 0;
            temp_a[j] = 0;
            if(i==0)
                retTable[i][j] = s;
            else
                retTable[i][j] = 0;
        }
    }

    float max=0;
    int max_index;

    // setting the returns for given years and for no of investments to zero initially
	for(i=0; i<t-1; i++)
    {
        for(k=0;k<n;k++)
        {
            for(j=0; j<n; j++)
            {    
                temp_a[j] = retTable[i][j]*rr[i][j];
                if(j!=k && ((temp_a[j]-f)*rr[i+1][k] > temp_b[k]))
                {
                    temp_b[k] = (temp_a[j]-f)*rr[i+1][k];
                    I[k] = j;
                }
                else if( j==k && (temp_a[j]*rr[i+1][k] > temp_b[k]))
                {
                    temp_b[k] = temp_a[j]*rr[i+1][k];
                    I[k] = j;
                }
            }
        }

        max = temp_b[0];
        max_index = 0;

        for(l=0;l<n;l++)
        {
            if(temp_b[l]>max)
            {
                max = temp_b[l];
                max_index = l;
            }
        }
        
        for(l=0;l<n;l++)
        {

            if(l!=I[l])
            {
                retTable[i+1][l] = temp_a[I[l]] - f;
            }
            else if(l==I[l])
            {
                retTable[i+1][l] = temp_a[I[l]];
            }

            if(l!=I[max_index])
            {
                retTable[i][l] = 0;
            }
        }
    }

    for(l=0;l<n;l++)
    {
        if(l!=max_index)
        {
            retTable[t-1][l] = 0;
        }
    }

    for(int i=0; i<t; i++)
    {
		for(int j=0; j<n; j++)
            printf("%.5f ",retTable[i][j]);
        
        printf("\n");
	}
    printf("final return=%.3f\n",retTable[t-1][max_index]*rr[t-1][max_index]);

   return 0;
}

int main(){

	double s;
	scanf("%lf\n",&s); 	  // total investment
	int t,n;
	float f;
	scanf("%d\n",&t);	  // no of years to invest
	scanf("%d\n",&n);     // no of instruments to invest in
	scanf("%f\n",&f);     // fee to be leived if investment instrument is changed (Assumption : for the first year, no fee)


	float *rr[t];         // array to store all the returns for investment options
    // float return = 0;

	// taking the returns for given years and for no of investments
	for(int i=0; i<t; i++){

        rr[i] = (float*) malloc(sizeof(float)*n);

		for(int j=0; j<n; j++){
			scanf("%f",&rr[i][j]);	// (i+1)th year and (j+1)th investment option
		}
        
	}
	
    plan_investment(rr,s,t,n,f);

    return 0;
}