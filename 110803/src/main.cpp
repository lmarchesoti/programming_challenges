#include <iostream>
#define MAX 13

using namespace std;

/* data structures */

/* global variables */
int n;
int p, r;
int count;
bool SL[MAX], SR[MAX];

/* function prototypes */
// checks if a solution has been reached
bool solution(const int);

// checks if current solution has the required number
// of people facing left and right unobstructed as required
// and increases counter if so
void process_solution();

// finds solution through backtracking
void backtrack(const int);

/* debug */

int main(){

	int t;

	cin >> t;

	while(t--){

		cin >> n >> p >> r;

		count = 0;
		backtrack(0);

		cout << count << endl;
	}

  return 0;
}

/* functions */
bool solution(const int k) { return (k == n); }

void process_solution(){

	int ul = 0, ur = 0; // unblocked left/right counters

	for(int i = 0; i < n; ++i) if(SL[i]) ++ul;
	for(int i = 0; i < n; ++i) if(SR[i]) ++ur;

	if((ul == p) && (ur == r)) ++count;

	return;
}

void backtrack(const int k){

	if(solution(k)) { process_solution(); return; }

	SL[k] = true;	 SR[k] = true;	backtrack(k+1);
	SL[k] = true;  SR[k] = false; backtrack(k+1);
	SL[k] = false; SR[k] = true;	backtrack(k+1);
	SL[k] = false; SR[k] = false; backtrack(k+1);

	return;
}
