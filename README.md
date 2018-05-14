# Dynamic-Programming
This repositoy contains various projects using dynamic programming, that is, recursively called functions that save as they go. Note that these programs are built using Rcpp, and are meant to be called in R via the Rcpp package.


## Binomial Coefficient
This program calculates the binomial coefficient (https://en.wikipedia.org/wiki/Binomial_coefficient). 


## Money-Changer 
This program enumerates all of the possible ways to make change from a desired amount of currency. To run this file, download and run in the command line with several sys argument: the amount of money to be changed followed by all denominations. For example, you could ask to convert $100 using standard bills by running this file in the command line as follows:

python money_changer.py 100 100 50 20 10 5 1


## Edit Distance
This program takes two words and returns the edit distance between them. By "edit distance", we mean the cost of turning one word into the other where the individual cost of changing a mis-match in characters and inserting characters are specified by the user. Documentation on how to use the functions can be found in the file itself. Again, this file should be loaded and called in R via Rcpp. 


