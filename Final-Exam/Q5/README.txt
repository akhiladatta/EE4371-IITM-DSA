Problem: Best possible investment return
-------------------------

You are given an initial investment amount S, 
return percentages for set of investment options(n),
t number of years to invest in, 
and possible change fee(f) applicable whenever you are changing investment option from present year to next year.

You need to find the maximum possible returns for your initial investment.

Given:
2 <= t <= 30
2 <= n <= 1000
1,000 <= S <= 1,00,00,000
20 <= f <= 2,000
r_ij > 1

Input Format :

S
t
n
f
r11 r12 .... r1n
r21 r22 .... r2n
....
...
...
rt1 rt2 .... rtn

Output Format :
I11 I12 .... I1n
I21 I22 .... I2n
....
...
...
It1 It2 .... Itn

Sample Input :

10000
2
2
100
1.05 1.10
1.12 1.08

Sample Output :

0 10000
10900 0

Explanation : Maximum possible return is possible if we invest in 2nd investment option for the 1st year and 
              1st investment option for the 2nd year.

i.e ((10000*1.1)-100) * 1.12 = 12208

Note : you need to output investment amount for each instrument(n) for year year as matrix above

A checker script is added in the folder, to check whether you have missed fee constraint while you invest in next years.

A sample code investmentsample.cc has been provided that can help you to read the inputs, 
but this is optional, and you may write your own code if you are more comfortable with that.

######## CHECKER ########
./checker input.txt output1.txt					// checking output1.txt(correct output)
./checker input.txt output1w.txt				// invested 1100 in 2 year 2nd option instead of 1090(wrong output)
./checker input.txt output2.txt					// checking output2.txt(correct output)
./checker input.txt output2w.txt				// while changing investments in 2nd year, fee is not considered
