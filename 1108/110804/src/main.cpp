#include <iostream>
#define NMAX 36

using namespace std;

/* data structures */

/* global variables */
bool town[NMAX];
bool adj[NMAX][NMAX];
int n; // number of cities
int sol; // solution
int ssize; // current solution size counter

/* function prototypes */
// checks if current solution is better than the recorded one
void process_solution();

// checks if a neighbor town has a station
bool neighbor(int);

// checks if the current solution is valid
bool solution(int);

// build solution
void backtrack(int);

/* debug */

int main(){

	int m; // number of adjacent towns
	int t1, t2; // temporary adjacent towns

	while(cin >> n >> m, n || m){

		// init adjacency matrix
		for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) adj[i][j] = false;

		// fill adjacency matrix
		while(m--){ cin >> t1 >> t2; adj[t1][t2] = true; adj[t2][t1] = true; }

		// backtrack to solution
		ssize = 0; sol = n; backtrack(0);

		cout << sol << endl;
	}

  return 0;
}

/* functions */
void process_solution(){ if(sol > ssize) sol = ssize; return; }

bool neighbor(int t){

	for(int i = 1; i <= n; ++i)
		if(adj[t][i] && town[i]) return true;

	return false;
}

bool solution(int k){

	if(ssize == 0) return false;

	for(int i = 1; i <= n; ++i)
		if(!town[i] && !neighbor(i)) return false;

	return true;
}

void backtrack(int k){

	if(n == k) { if(solution(k)) process_solution(); return; }

	// only two options
	++ssize; town[k] = true; backtrack(k+1);

	--ssize; town[k] = false; backtrack(k+1);

	return;
}
