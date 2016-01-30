#include <iostream>
#include <algorithm>
#include <cmath>
#define N_RELATIVES 500

using namespace std;

/* data structures */

/* global variables */
int relatives[N_RELATIVES];

/* function prototypes */

/* debug */

int main(){

	int t;
	int home; // vito's home
	int total; // total distance sum
	int relative; // temporary relative
	int n; // number of relatives

	cin >> t;
	while(t--){

		// read distances
		cin >> n; for(int i = 0; i < n; ++i) cin >> relatives[i];

		// sort distances
		sort(relatives, relatives+n);

		// pick best location as median
		home = relatives[n / 2];

		// calculate sum and print
		total = 0; while(n--) total += abs(home - relatives[n]);
		cout << total << endl;

	}

  return 0;
}

/* functions */
