#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// returns the number of digits of a number
int size(unsigned long int);

// reduces a number by a set amount of digits
unsigned long int reduce(unsigned long int, int);

// matches a number to the beginning of any power of 2
int match(unsigned int);

/* debug */

int main(){

	unsigned int n;
	int result;

	while(cin >> n){

		if(n == 0) cout << "no power of 2" << endl;
		else {

			result = match(n);

			if (result) cout << result << endl; else cout << "no power of 2" << endl; 
		}
	}

  return 0;
}

/* functions */
int size(unsigned long int n){

	int s = 0;

	while(n != 0) ++s, n /= 10;

	return s;

}

unsigned long int reduce(unsigned long int n, int s){

	while(s) n /= 10, --s;

	return n;

}

int match(unsigned int n){

	unsigned long int t; // temporary power of 2
	int s; // size of t

	for(int e = 7; e <= 6000000; ++e){

		t = pow(2, e);

		s = size(t);

		t = reduce(t, s/2 + 1);

		while(n <= t) if (n == t) return e; else t = reduce(t, 1);

	}

	return 0;

}
