#include <iostream>
#include <algorithm>
#define N_JOBS 1002
#define MAX_R 10001

using namespace std;

/* data structures */

/* global variables */
int ratio[N_JOBS];
int jobs[N_JOBS];

/* function prototypes */
// compares jobs according to fee/day
bool cmp(const int, const int);

/* debug */

int main(){

	int t;
	int n; // number of jobs for the round
	int day, fee; // temporary
	//bool first = true;
	ratio[0] = MAX_R + 1;

	cin >> t >> ws;
	while(t--){

		//if(first) first = false; else cout << endl;

		// read jobs info
		cin >> n >> ws; ++n;
		for(int i = 1; i < n; ++i)
			{ cin >> day >> fee; cin.get(); ratio[i] = fee / day; }

		// create a job array
		for(int i = 0; i < n; ++i) jobs[i] = i;

		// sort according to fee/day
		sort(jobs, jobs + n, cmp);

		// output order
		if(n - 1) cout << jobs[1];
		for(int i = 2; i < n; ++i) cout << " " << jobs[i];

		cout << endl;
	}

  return 0;
}

/* functions */
bool cmp(const int a, const int b) { return ratio[a] > ratio[b]; }
