#include <iostream>

using namespace std;

/* data structures */

/* global variables */
unsigned int x, y;
unsigned int d; // difference y - x
unsigned int s; // current sequence size

/* function prototypes */
int seq(const unsigned int);

/* debug */

int main(){

	int t;

	cin >> t;

	while(t--){

		cin >> x >> y;

		d = y - x; s = 1; // init

		if (d == 0) cout << 0 << endl;
		else cout << seq(1) << endl;

	}

  return 0;
}

/* functions */
int seq(const unsigned int Ts){

	int Tsp1 = Ts + s/2 + s%2;

	if ((Ts <= d) && (d < Tsp1)) return s;
	else { ++s; return seq(Tsp1); }

}
