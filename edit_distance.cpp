#include <Rcpp.h>
#include <iostream>
#include <string>

using namespace Rcpp;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
// editDistance() function
// - Note that this is not an Rcpp function, but a function
//   only called within C++
// - Arguments:
//   > s1 : The first (reference) string to align
//   > s2 : The second (alternative) string to align
//   > cost : A matrix to contain cost to each node (negative if not stored)
//   > move : A matrix to contain the optimal move to each node (negative if not stored)
//   > r  : row    index (0..s1.size()), indicating the position in s1
//   > c  : column index (0..s1.size()), indicating the position in s2
//   > mcost : cost of single letter mismatch
//   > icost : cost of single latter insertion/deletion
// - Return value:
//   > the optimal edit distance
// - Expected behavior:
//   > cost matrix will store the optimal cost from (0,0)...(r,c)
//   > move matrix will store the optimal previous move from (0,0)...(r,c)
//////////////////////////////////////////////////////////////////////////////

int editDistance(string& s1, string& s2, IntegerMatrix& cost, IntegerMatrix& move, int r, int c, int mcost, int icost) {
  ////////////////////////////////////////////////////////
  // TODO : FILL IN THE BLANK to satisfy the specs above
  ////////////////////////////////////////////////////////
	if ( cost(r,c) < 0 ) {
	    if ( r == 0 ) {
	      if ( c == 0 ) cost(r,c) = 0;
	      else{
	      	cost(r,c) = editDistance(s1, s2, cost, move, r, c-1, mcost, icost) + icost;
	      	move(r, c) = 1;
	      }
	    }
	    else if ( c == 0 ) {
	    	cost(r,c) = editDistance(s1, s2, cost, move,r-1, c, mcost, icost) + icost;  
	    	move(r, c) = 2;
	    }
	    else {
	      int iDist = editDistance(s1, s2, cost, move, r, c-1, mcost, icost) + icost;
	      int dDist = editDistance(s1, s2, cost, move, r-1, c, mcost, icost) + icost;
	      //cout << s1[r-1] << " " << s2[c-1] << " " << (s1[r-1] != s2[c-1]) << endl;
	      int mDist = editDistance(s1, s2, cost, move, r-1 , c-1, mcost, icost) + (mcost*(s1[r-1]!=s2[c-1]));
	      if ( iDist < dDist ) { // if insertion cost < deletion cost
	      	if (iDist < mDist) {
	      	cost(r, c) = iDist; // if insertion cost also < mismatch cost
	      	move(r, c) = 1;
	      	}
	      	else {
	      	cost(r, c) = mDist; // mismatch is cheapest
	      	move(r, c) = 0;
	      	//cost(r,c) = iDist < mDist ? iDist : mDist;
	      	}
	      }
	      else { // deletion cost <= insertion cost
	      	if (dDist < mDist) { 
	      	cost(r, c) = dDist; // deletion also cheaper than mismatch
	      	move(r, c) = 2;
	      	}
	      	else {
	      	cost(r, c) = mDist; // mismatch is cheapest
	      	move(r, c) = 0;
	      	//cost(r,c) = dDist < mDist ? dDist : mDist;
	      	}
	      }
	    }
	  }
	return cost(r,c);
}

/////////////////////////////////////////////////////////////////////////
// alignWords() function (Exported by Rcpp)
// - Arguments:
//   > s1 : The first (reference) string to align
//   > s2 : The second (alternative) string to align
//   > mcost : Cost of single letter mismatch
//   > icost : Cost of single latter insertion/deletion
// - Return values: A List containing the following attributes:
//   > distance  : Optimal edit distance between the string
//   > first     : A modified version of the first string to include gaps
//                 as '-' so that attributes have same length
//   > alignment : Alignment between letters 
//   >             '.' indicates match,
//   >             '*' indicates mismatch,
//   >             'I' indicates insertion from first to second string
//   >             'D' indicates insertion from first to second string
//   > second    : A modified version of the first string to include gaps
//                 so that attributes have same length
//
//   For example, an example can be
//   distance  : 6
//   first     : ALGORI-THM
//   alignment : ..***.I.**
//   second    : ALTRUISTIC
//////////////////////////////////////////////////////////////////////////
// [[Rcpp::export]]
List alignWords(string s1, string s2, int mcost, int icost) {
  ////////////////////////////////////////////////////////
  // TODO : FILL IN THE BLANK to satisfy the specs above
  ////////////////////////////////////////////////////////  
	int r = (int)s1.size();
	int c = (int)s2.size();
	IntegerMatrix cost(r+1, c+1);
	IntegerMatrix move(r+1, c+1);
	fill(cost.begin(), cost.end(), -1);
	fill(move.begin(), move.end(), -1);
	int distance = editDistance(s1, s2, cost, move, r, c, mcost, icost);

	// create alignment string using move matrix
	string alignment = "";
  	while ( ( r > 0 ) || ( c > 0 ) ) {
    if ( move(r,c) == 0) { //if match or mismatch
    	if (s1[r-1] != s2[c-1]) { // mismatch --> prepend "*"
    	alignment = "*" + alignment; --c; --r; 
    	} 
    	else { // match --> prepend "."
    	alignment = "." + alignment; --r; --c;
    	} 
    }
    else if ( move(r, c) == 1) {// insert --> prepend "I"
    alignment = "I" + alignment; --c;
    } 
    else {// deletion --> prepend "D"
    alignment = "D" + alignment; --r;
	} 
  	}

	int n = alignment.size();
	for (int i =0; i < n; i++){
		if (alignment[i] == 'I'){
			s1.insert(i, "-");
		}
		if (alignment[i] == 'D'){
			s2.insert(i, "-");
		}
	}
	return List::create(Named("distance") = distance, Named("first") = s1, Named("alignment") = alignment, Named("second") = s2);
}
