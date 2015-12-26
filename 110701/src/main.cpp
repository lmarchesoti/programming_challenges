#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// returns wether the parameter has an exact square root
bool light(unsigned int);

/* debug */

int main(){

	unsigned int n;

	while(cin >> n, n != 0)
		{ if(light(n)) cout << "yes" << endl; else cout << "no" << endl; }

  return 0;
}

/* functions */
bool light(unsigned int n){

	unsigned int sqn = ceil(sqrt(n));

	return (sqn*sqn == n) ? true : false;
}
