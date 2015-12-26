#include <iostream>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
long long int land(const int);

/* debug */

int main(){

	int t;
	int n;

	cin >> t;

	while(t--){

		cin >> n;

		cout << land(n) << endl;

	}

  return 0;
}

/* functions */
long long int land(const int n){

	switch(n) {

		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
		case 3: return 4;
		case 4: return 8;
		default: return land(n - 1) + (n - 3) * (n - 1);

	}
}
