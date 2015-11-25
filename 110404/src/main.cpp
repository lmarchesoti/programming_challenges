#include <iostream>
#include <iomanip>
#include <algorithm>
#define APP_MAX 102
#define LINE_S 255

using namespace std;

/* data structures */
typedef struct { int start, end; } t_block;

/* global variables */
t_block appointments[APP_MAX];
t_block naps[APP_MAX];
int n; // number of appointments + first sentinel

/* function prototypes */
// reads appointments and inserts sentinels at start/end
void read_apps();

// comparison function for appointment start
bool comp_start(const t_block, const t_block);

// comparison function for nap duration
bool comp_duration(const t_block, const t_block);

// rank_t time
int rank_t(const int, const int);

int hours(const int);

int minutes(const int);

// prints result
void pretty_print(const int, const t_block);

/* debug */

int main(){

	for(int t = 1; !cin.eof(); ++t){

		// read appointments
		read_apps();

		// sort read appointments by starting time(assume no overlap)
		sort(appointments+1, appointments + n, comp_start);

		// extract naps
		for(int i = 0; i < n; ++i)
			naps[i] = { appointments[i].end, appointments[i + 1].start };

		// sort naps
		sort(naps, naps + n, comp_duration);

		// pick longest(last) nap
		pretty_print(t, naps[n - 1]);

	}

  return 0;
}

/* functions */
void read_apps(){

	int st_h, st_m, ed_h, ed_m;
	char colon = ':';

	cin >> n; ++n;
	appointments[0] = { rank_t(10, 0), rank_t(10, 0) }; // start of day

	for(int i = 1; i < n; ++i) {

		cin >> st_h >> colon >> st_m;
		cin >> ed_h >> colon >> ed_m;
		cin.ignore(LINE_S, '\n');

		appointments[i] = { rank_t(st_h, st_m), rank_t(ed_h, ed_m) };
	}

	appointments[n] = { rank_t(18, 0), rank_t(18, 0) }; // end of day
	cin >> ws;
	
	return;
}

bool comp_start(const t_block a, const t_block b)
	{ return a.start < b.start; }

bool comp_duration(const t_block a, const t_block b){

	int da, db; // durations

	da = a.end - a.start;
	db = b.end - b.start;

	if(da == db) return a.start > b.start;
	return da < db;
}

int rank_t(const int h, const int m) { return 60 * h + m; }

int hours(const int t) { return t / 60; }

int minutes(const int t) { return t % 60; }

void pretty_print(const int t, const t_block nap){

	int h, m; // temporary hour/minute

	cout << "Day #" << t
			 << ": the longest nap starts at "
			 << hours(nap.start) << ":" 
			 << setfill('0') << setw(2)
			 << minutes(nap.start)
			 << " and will last for ";

	h = hours(nap.end - nap.start);
	if(h) cout << h << " hours and ";
	cout << minutes(nap.end - nap.start) << " minutes." << endl;

	return;
}
