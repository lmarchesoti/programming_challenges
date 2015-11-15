#include <cstdio>
#include <bitset>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */

/* debug */

int main(){

	int n; // number of items in the sequence
	bitset<3000> set; // difference record
	int prev, cur, diff; // temporary values to iterate in sequence
	bool jolly; // answer flag

	// read number of items in sequence
	while(scanf("%d", &n) != EOF){

		set.reset(); // reset set

		scanf("%d", &prev); // read first item if any

		// until sequence end
		for(int i = 1; i < n; ++i){

			// read next difference
			scanf("%d", &cur);
			diff = abs(prev - cur);

			set[diff] = 1; // mark difference

			prev = cur; // set previous to current
		}

		// print result
		jolly = true;
		for(int i = 1; (i < n) && jolly; ++i)
			if(!set.test(i)) jolly = false;

		if(jolly) printf("Jolly\n");
		else printf("Not jolly\n");
	}

  return 0;
}

/* functions */
