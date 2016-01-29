#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// prints the prime factorization of the given
// number on a single line
void factor(long int);

/* debug */

int main(){

	long int n; // number to factor

	while(cin>> n, n){ factor(n); cout << endl; }

  return 0;
}

/* functions */
void factor(long int n){

	if(n == 1) cout << 1;

	// take out twos
	while((n%2) == 0) { cout << "2 "; n /= 2; }

	// take out odd factors
	for(long int i = 3; i < (sqrt(n)+1);)
		{ if((n%i) == 0) { cout << i << " "; n /= i; } else i += 2; }

	if(n > 1) cout << n;

	return;

}
