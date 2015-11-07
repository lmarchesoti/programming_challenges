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
	bitset<LIMIT> valid; // mask of valid hartal days

	// set every day except for fridays and saturdays as valid
	valid.set();
	for(int i = 6; i < LIMIT; i += 7) valid[i] = 0;
	for(int i = 7; i < LIMIT; i += 7) valid[i] = 0;

	cin >> t;

	// for each test case
	for(; t > 0; --t){

		// init
		cin >> days >> parties;
		calendar.reset();

		// for each party
		for(int i = 0; i < parties; ++i){

			// read interval
			cin >> interval;

			// mark hartals on calendar
			for(int day = interval; day <= days; day += interval)
				calendar[day] = valid[day];
		}

		// print number of hartals
		cout << calendar.count() << endl;
	}

  return 0;
}

/* functions */
