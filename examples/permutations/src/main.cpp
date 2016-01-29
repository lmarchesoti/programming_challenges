#include <iostream>
#define MAX 100 // max elements to process

using namespace std;

/* data structures */

/* global variables */
int n;						// total number of items in permutation
bool in_sol[MAX];	// array to check if element is in solution
int s[MAX];				// solution array

/* function prototypes */
// prints all permutations of up to n items
void perm(int);

// prints the current solution
void process_solution();

/* debug */

int main(){

	while(cin >> n, n) { perm(0); }

  return 0;
}

/* functions */
void perm(int k){

	// k = n is the n+1'th level of recursion
	if(k == n) { process_solution(); return; }

	// test all unused possibilities for this position
	for(int i = 0; i < n; ++i){

		if(in_sol[i]) continue;

		// lock and use i at this position
		in_sol[i] = true; s[k] = i; perm(k+1);

		in_sol[i] = false; // unlock for subsequent calls
	}

	return;
}

// { items }
void process_solution(){

	cout << "{ ";
	for(int i = 0; i < n; ++i) cout << s[i] << " ";
	cout << "}" << endl;

	return;
}
