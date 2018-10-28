/*
Author: Atul Balaji
Date: 17-08-2018
Program to find anagrams from a sequence of words
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_WORDS 20                         // maximum no.of words for an anagram set
#define MAX_CHARS 30                         // maximum no.of characters in a word
#define MAX_ANAGRAMS 10000                    // maximum no.of anagram sets

// Function prototypes
void sort_words(char words[][MAX_CHARS],int [], int, int);
void sort_int_array(int array[],int sortby[],int,int);

// Main function
int main()
{
    int num;
    scanf("%d",&num);                                          // get no.of words
    char words[num][MAX_CHARS];                                // array containing all words
    char str[MAX_CHARS];
    int i,j,l,u,v,t,p,q,r,s,swap,temp,x,z,c,len;

    // Read the words into the array
    for(j=0;j<num;j++)
        scanf("%s",words[j]);

    // Sort the letters in each word of the array in ascending alphabetical order.
    char sorted_letters[num][MAX_CHARS];
    for(l=0;l<num;l++)
    {
        strcpy(str,words[l]);
        len = strlen(str);
        for (p = 0; p < len-1; p++) 
        {
            for (q = p+1; q < len; q++) 
            {
                if (str[p] > str[q]) 
                {
                temp = str[p];
                str[p] = str[q];
                str[q] = temp;
                }
            }
        }
        strcpy(sorted_letters[l],str);
    }

    // Sort the words of the array 'sorted_letters' in ascending alphabetical order.
    int indices[num];                                             // Indices of the words array
    for(t=0;t<num;t++)
    {
        indices[t] = t;
    }
    sort_words(sorted_letters,indices,0,num-1);                   // Call the sort_words function to sort the array. Indices are also updated.                  

    // Find start and end positions of each anagram set in the sorted_letters array.
    int w;
    int y[num];
    int ctr = 0, ct = 0, m = 0,k = 0;
    for(x=1;x<num;x++)
    {   
        if(strcmp(sorted_letters[x],sorted_letters[x-1]) == 0)
        {
            y[ctr] = x-1;
            ctr++;
        }
    }

    int anagstart[MAX_ANAGRAMS];                    // Start index of the anagrams set wrt sorted_letters
    int anagend[MAX_ANAGRAMS];                      // End index of the anagrams set wrt sorted_letters
    int anagindex[MAX_ANAGRAMS];                    // Smallest value of indices array in this anagram set
    int anagindex1[MAX_ANAGRAMS];
    anagstart[ct] = y[0];
    for(z=0;z<ctr;z++)
    {
        if (y[z] != y[z+1]-1)
        {   
            ct++;
            anagend[ct-1] = y[z]+1;
            anagstart[ct] = y[z+1];
        }
    }

    int x1,x2,min;
    for(k=0;k<ct;k++)
    {
        x1 = anagstart[k];
        x2 = anagend[k];
        min = indices[x1];
        for(i=x1;i<=x2;i++)
        {
            if(indices[i] < min)
                min = indices[i];
        }
        anagindex[k] = min;                     // Minimum value of indices for this anagram set
        anagindex1[k] = min;

    }

    /* Sort anagstart and anagend arrays based on the values of anagindex. 
       If value of anagindex of set 1 is smaller than that of set 2, 
       it means that the earliest occurence of elements of set 1 is earlier than the earliest occurence of those of set 2.
    */  
    sort_int_array(anagstart,anagindex,0,ct-1);
    sort_int_array(anagend,anagindex1,0,ct-1);

    printf("%d",ct);                                                    // Print no.of anagram sets
    char anagram[MAX_WORDS][MAX_CHARS];                                 // Stores all words in an anagram set
    int ordered_indices[MAX_WORDS];                                     
    for(c=0;c<ct;c++)
    {   
        for(w=0;w<num;w++)
        {
            if (w == anagstart[c])
            {   
                m = anagend[c] - anagstart[c] + 1;
                printf("\n%d",m);                                       // Print no.of words in this anagram set
                for(k=0;k<m;k++)
                {
                    strcpy(anagram[k],words[indices[w+k]]);
                    ordered_indices[k] = k;
                }
                sort_words(anagram,ordered_indices,0,m-1);              // Sort words of the anagram set in ascending alphabetical order
                for(k=0;k<m;k++)
                {
                    printf("\n%s",anagram[k]);                          // Print the words
                }
            }
        }
    }
    printf("\n");
	return 0;
}

// Function to swap two numbers
void swap_nos(int* i1, int* i2)
{
    int temp = *i1;
    *i1 = *i2;
    *i2 = temp;
}

// Function to swap two strings
void swap_strings(char word1[], char word2[])
{
    char temp[MAX_CHARS];
    strcpy(temp,word1);
    strcpy(word1,word2);
    strcpy(word2,temp);
}

// Function to implement quicksort of all strings in an array
void sort_words(char wordarray[][MAX_CHARS],int ordered_indices[], int fl, int ll)
{
    int i,l;
    int p = (fl + ll)/2 ;
    if(fl>=ll)
    {
        return ; 
    }
    swap_strings(wordarray[fl],wordarray[p]);
    swap_nos(&ordered_indices[fl],&ordered_indices[p]);
    l = fl;
    for(i=fl+1;i<=ll;i++)
    {
        if(strcmp(wordarray[i],wordarray[fl]) < 0)
        {
            l += 1;
            swap_strings(wordarray[l],wordarray[i]);
            swap_nos(&ordered_indices[l],&ordered_indices[i]);
        }
    }
    swap_strings(wordarray[fl],wordarray[l]);
    swap_nos(&ordered_indices[fl],&ordered_indices[l]);
    sort_words(wordarray,ordered_indices,fl,l-1);
    sort_words(wordarray,ordered_indices,l+1,ll);
}

// Function to implement quicksort of a given integer array according to it's index in the sortby array. 
void sort_int_array(int array[],int sortby[],int m,int n)
{   
    int key,i,j,k,l;
    if( m < n)
    {
        k = (m + n)/2;
        swap_nos(&sortby[m],&sortby[k]);
        swap_nos(&array[m],&array[k]);
        key = sortby[m];
        i = m + 1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (sortby[i] <= key))
                i++;
            while((j >= m) && (sortby[j] > key))
                j--;
            if( i < j)
            {
                swap_nos(&sortby[i],&sortby[j]);
                swap_nos(&array[i],&array[j]);
            }
        }
        /* swap two elements */
        swap_nos(&sortby[m],&sortby[j]);
        swap_nos(&array[m],&array[j]);
 
        /* recursively sort the lesser array */
        sort_int_array(array,sortby,m,j-1);
        sort_int_array(array,sortby,j+1,n);
    }
}