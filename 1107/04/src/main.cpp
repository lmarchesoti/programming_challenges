#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// returns the greatest common divisor of two numbers
int gcd(int, int);

// returns wether m divides n!
bool simplify_by_gcd(int, int);

// returns wether m divides n! by using factors
bool simplify_by_factors(int, int);

/* debug */

int main(){

	int m, n;

	while(cin >> n >> m){

		if(simplify_by_factors(m, n))
			cout << m << " divides " << n << "!" << endl;
		else cout << m << " does not divide " << n << "!" << endl;

	}

  return 0;
}

/* functions */
int gcd(int a, int b){

	if(b > a) return gcd(b, a);

	if(b == 0) return a;

	return gcd(b, a%b);
}

bool simplify_by_gcd(int m, int n){

/*
	int g; // temporary gcd

	for(int i = 1; (i <= n) && (m != 1); ++i){

		g = gcd(m, i);

		m /= g;
	}
*/

/*
	for(int i = 1; i <= n; ++i){

		// find next prime factor of i
		if(i%2) { f = 2; 

		// divide m if possible
		for(int j = 1; j <= (sqrt(i)+1); ++j)
			if (!(i%j) && !(m%j)) m /= j;

	}

*/
	if (m == 1) return true;

	return false;
}

bool simplify_by_factors(int m, int n){

	int c; // current factorial digit
	int sqc; // square root of current

	// for every value of n to 1
	// compute all the prime factors of c <- n
	// and divide m by the ones that apply
	do {

		c = n; // even
		while(!(c%2)) c /= 2, m /= 2;

		// odd
		for(int f = 3, sqc = sqrt(c) + 1; f <= sqc; f += 2){ 

			if((c%f) == 0){ // f is a factor of c

				c /= f; sqc = sqrt(c) + 1;
				if((m%f) == 0) m /= f; // f also divides m
			};

		}

		if((c > 1) && (m%c)) m /= c; // c is prime
	} while((m != 1) && --n);

	if (m == 1) return true;

	return false;
}
