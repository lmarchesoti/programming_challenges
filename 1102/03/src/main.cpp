#include <iostream>
#include <bitset>
#define LIMIT 3651

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */

/* debug */

int main(){

	int t; // number of test cases
	int days; // number of days
	int parties; // number of political parties
	int interval; // interval of attacks for current party
	bitset<LIMIT> calendar; // record of announced hartals

	cin >> t;

	// for each test case
	for(; t > 0; --t){

		// init
		cin >> days >> parties;
		calendar.reset();

		// for each party
		for(int i = 0; i < parties; ++i){

			cin >> interval;

			// mark hartals on calendar
			for(int day = interval; day <= days; day += interval)
				calendar[day] = 1;
		}

		// disconsider hartals on forbidden days
		for(int i = 6; i < LIMIT; i += 7){ calendar[i] = 0; calendar[i + 1] = 0; }

		// print number of hartals
		cout << calendar.count() << endl;
	}

  return 0;
}

/* functions */
