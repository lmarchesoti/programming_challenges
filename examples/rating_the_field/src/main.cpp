#include <iostream>
#include <algorithm>
#include <cmath>

#define BESTHEIGHT 180
#define BESTWEIGHT 75

using namespace std;

/* data structures */
typedef struct {

	int height, weight;
	string fname, lname;
} suitor;

/* global variables */
vector<suitor> suitors;

/* function prototypes */
// compares two suitors
// returns true if the first goes before the second
bool cmp(suitor, suitor);

// fixes suitor scores
void fix_scores();

/* debug */

int main(){

	suitor s; // temp

	// read suitors
	while(!cin.eof()) {

		cin >> s.fname >> s.lname >> s.height >> s.weight >> ws;

		suitors.push_back(s);
	}

	fix_scores();

	// sort suitors
	sort(suitors.begin(), suitors.end(), cmp);

	// print suitor list
	for(int i = 0; i < suitors.size(); ++i)
		cout << suitors[i].lname << ", " << suitors[i].fname << endl;

  return 0;
}

/* functions */
bool cmp(suitor a, suitor b){

	int c; // temporary string comparison score

	if(a.height < b.height) return true;
	if(a.height > b.height) return false;

	if(a.weight < b.weight) return true;
	if(a.weight > b.weight) return false;

	// compare last name alphabetically
	c = a.lname.compare(b.lname);
	if(c < 0) return true;
	if(c > 0) return false;

	// compare first name alphabetically
	c = a.fname.compare(b.fname);
	if(c < 0) return true;
	if(c > 0) return false;

	return true;
}

void fix_scores(){

	for(int i = 0; i < suitors.size(); ++i){

		// height score is the distance to the best
		suitors[i].height = abs(suitors[i].height - BESTHEIGHT);

		// weight score is the closest possible to the best
		// without going over, in which case the difference applies.
		// Thus we use the negative value
		// for cases where it doesn't go over and start counting
		// positive difference in cases it does.
		if(suitors[i].weight > BESTWEIGHT)
			suitors[i].weight = suitors[i].weight - BESTWEIGHT;
		else suitors[i].weight = -suitors[i].weight;

	}

	return;
}
