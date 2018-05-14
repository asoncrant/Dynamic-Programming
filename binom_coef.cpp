#include <Rcpp.h>
#include <map>
#include <algorithm>

using namespace Rcpp;
using namespace std;

///////////////////////////////////////
///////////////////////////////////////

// function to calculate factorial
int fac(int n) {
  if ( n < 2 ) return 1; // return 1 when n=0,1
  int ret = 1;
  for(int i=2; i <= n; ++i)
    ret *= i;  // calculate factorial
  return ret;
}

// compute choose(n,k) using factorial
// [[Rcpp::export]]
int choose_fac(int n, int k) {
  return fac(n)/fac(k)/fac(n-k);
}

// compute choose(n,k) using dynamic programming
// [[Rcpp::export]]
int choose_dp(int n, int k) {
  //create matrix to be filled with values as we go
  int sol[n+1][k+1];
  int i, j;
  ///////////////////////////////////////////////////
  //////////////////////////////////////////////////
  for(i = 0; i <= n; i++){
    for(j = 0; j<=i && j<=k; j++){
      if (j == 0 || j == i){
        sol[i][j] = 1;
      }
      else{
        sol[i][j] = sol[i-1][j-1] + sol[i-1][j];
      }
    }
  }
  return sol[n][k];
}
