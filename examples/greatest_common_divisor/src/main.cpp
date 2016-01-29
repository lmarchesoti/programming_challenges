#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// calculates gcd of two numbers and finds factors
// for the equation ax + by = gdc(a, b)
int gcdf(int, int, int&, int&);

// calculates gcd of two numbers
int gcd(int, int);

/* debug */

int main(){

	int n, m; // numbers to find gcd
	int x, y; // factors of equation
	int g;		// temporary gcd

	while(cin >> n >> m, (n != 0) && (m != 0)){

		// with factors
		g = gcdf(n, m, x, y); 
		cout << g << " " << x << " " << y << endl;

		// without factors
		//cout << gcd(n, m) << endl;

	}

  return 0;
}

/* functions */
int gcd(int a, int b){

	// enforce relative orde
	if(b > a) return gcd(b, a);
	if((a%b) == 0) return b;

	return gcd(b, a%b);
}

int gcdf(int a, int b, int &x, int &y){

	int g; // temp gcd
	int x1, y1; // values for x' y'

	// enforce relative order
	if(b > a) return gcdf(b, a, y, x);
	if(b == 0) { x = 1; y = 0; return a; }

	g = gcdf(b, a%b, x1, y1);

	// calculate factors x and y
	x = y1; y = x1 - floor(a/b)*y1;

	return g;
}
