#include <iostream>
#define MAXN 100 // max number of items

using namespace std;

/* data structures */

/* global variables */
int n;				// number of items
bool s[MAXN];	// solution array

/* function prototypes */
// prints all subsets up to the required number of items
void subsets(int);

// prints the current solution
void process_solution();

/* debug */

int main(){

	while(cin >> n, n){ subsets(0); }

  return 0;
}

/* functions */
void subsets(int k){

	// k starts at 0, so k = n is the n+1'th level of recursion
	if(k == n) { process_solution(); return; }

	s[k] = false; subsets(k+1);
	s[k] = true ; subsets(k+1);

	return;
}

// { items }
void process_solution(){

	cout << "{ ";
	for(int i = 0; i < n; ++i) if(s[i]) cout << i << " ";
	cout << "}" << endl;

	return; 
}
