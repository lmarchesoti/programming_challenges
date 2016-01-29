#include <iostream>
#define MAXN 100	// maximum number of allowed queens

using namespace std;

/* data structures */

/* global variables */
int n;	// number of queens on the chessboard
int s[MAXN];	// solution array
bool in_sol[MAXN];	// solution presence array
int n_solutions;		// solution counter

/* function prototypes */
// calculates the number of solutions for the nqueens
// problem with n queens
void nqueens(int);

// initializes pertinent global variables
void init();

// returns true if this choice should be pruned
bool prune(int, int);

// increases solution counter
void process_solution();

/* debug */

int main(){

	while(cin >> n, n) { init(); nqueens(0); cout << n_solutions << endl; }

  return 0;
}

/* functions */
void nqueens(int k){

	if(k == n) { process_solution(); return; }

	for(int i = 0; i < n; ++i){

		if(in_sol[i]) continue;

		if(prune(k, i)) continue;

		in_sol[i] = true; s[k] = i; nqueens(k+1);

		in_sol[i] = false;

	}

	return;
}

void init(){

	n_solutions = 0;

	for(int i = 0; i < MAXN; ++i) in_sol[i] = false;

	return;
}

bool prune(int k, int c){

	// prunes diagonal
	// if any previously chosen queen threatens this position
	for(int i = 1; i <= k; ++i)
		if((s[k-i] == c+i) || (s[k-i] == c-i))
			return true;

	return false;
}

void process_solution(){ ++n_solutions; return; }
