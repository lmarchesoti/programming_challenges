#include <cstdio>
#include <iostream>
#include <algorithm>
#define NCONTESTANTS 101
#define NPROBLEMS 10
#define PENALTY 20

using namespace std;

/* data structures */
typedef struct s_contestant{

	int team; // team code
	int score; // number of scored problems
	int penalty; // penalty time
	bool submitted; // flags participation
	int wrong[NPROBLEMS]; // score log
} CONTESTANT;

/* global variables */

/* function prototypes */
bool comp(CONTESTANT a, CONTESTANT b);

/* debug */

int main(){

	char *s; // input string
	int t; // number of test cases
	int c_code; // contestant code
	int problem; // problem submitted
	int time; // time to submission
	char flag; // judge answer
	bool first = true;
	CONTESTANT contestants[NCONTESTANTS];

	cin >> t;

	for(; t > 0; --t){

		if(first) first = false; else cout << endl;

		// init
		for(int i = 1; i < NCONTESTANTS; ++i)
			contestants[i] = {i, 0, 0, false, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

		cin >> ws;

		// until end of test case
		while((cin.peek() != '\n') && !cin.eof()){

			// update contestant
			cin >> c_code >> problem >> time >> flag; cin.get();

			if(contestants[c_code].wrong[problem] != -1){
				switch(flag){

					case 'C':

						++contestants[c_code].score;
						contestants[c_code].penalty += time;
						contestants[c_code].penalty += contestants[c_code].wrong[problem] * PENALTY;
						contestants[c_code].submitted = true;
						contestants[c_code].wrong[problem] = -1;
						break;

					case 'I': // mark wrong submission
						++contestants[c_code].wrong[problem];
						contestants[c_code].submitted = true;
						break;

					default: // count participation
						contestants[c_code].submitted = true;
						break;

				}
			}
		}

		// sort contestants
		sort(contestants+1, contestants+NCONTESTANTS, comp);

		// display
		for(int i = 1; i < NCONTESTANTS ; ++i)
			if(contestants[i].submitted)
				printf("%d %d %d\n", contestants[i].team, contestants[i].score, contestants[i].penalty);

	}

  return 0;
}

/* functions */
bool comp(CONTESTANT a, CONTESTANT b){

	if(a.score > b.score) return true;
	if(b.score > a.score) return false;

	if(a.penalty < b.penalty) return true;
	if(b.penalty < a.penalty) return false;

	if(a.team < b.team) return true;
	if(b.team < a.team) return false;

	return true;
}
