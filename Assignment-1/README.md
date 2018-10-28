# Assignment-1

* This assignment is meant as an exercise to use your basic C programming skills. 
* Given a set of words in a file, you must find all anagrams in it and print them in alphabetical order.

## Input

* First line of input contains number of words (N) in the set.
* Next N lines have one word per line, where each word consists of the letters 'a'-'z' (may be capital), numbers and the apostrophe (') symbol.
* When comparing anagrams, ignore whether a letter was capital or lower case.

### Example Input

acts  
ball  
cats  
dog  
elephant  
fish  
god  
hand  
scat  
cast

## Output

* The output file must contain no.of anagrams and for each set, the no.of words in that set and the words themselves in alphabetical order.
* For the above example input, the output is:  
    Line 1: number of anagram sets found  
    Line 2: number of anagrams in first set (K)  
    Line 3 to K+2: list of anagrams in first set, one word per line, in alphabetical order.  
    Repeat for next set etc. till all anagrams printed out

### Example Output

2  
4  
acts  
cast  
cats  
scat  
2  
dog  
god  

## Approach

* Read words into an array `words`.
* Sort the letters in each word of the array and store it in a new array `sorted_letters`.
* Sort the words of this array and maintain an array of original indices.
* Print the anagram sets in order of appearance in the input and sort by alphabetical order in each set.