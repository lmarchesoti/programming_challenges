#include <iostream>
#include <cmath>
#define MAXW 25000	// maximum words
#define MAXL 16			// maximum word size

using namespace std;

/* data structures */

/* global variables */
int n; // word count
string w[MAXW]; // word vector
//char w[MAXW][MAXL]; // word vector
bool steps[MAXW][MAXW]; // adjacency matrix for steps

/* function prototypes */
// checks if two words form a step
bool step(int, int);

// init graph
void init();

// returns max edit step ladder
int ladder();

/* debug */

int main(){

	n = 0; // read dictionary
	while(!cin.eof()) cin >> w[n++];

	init(); // init graph

	// build graph
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j)
			if(step(i, j)) { steps[i][j] = true; steps[j][i] = true; }

	// calculate max edit step ladder
	cout << ladder() << endl;

  return 0;
}

/* functions */
//////////////////////////////////////////////////
/* weird error k getting to -INF !!!!!!!!!!!!!! */
//////////////////////////////////////////////////
bool step(int a, int b){

	// error counter initialized to difference of string size
	int k = abs(w[a].size() - w[b].size());

	// increases k for any different letter
	for(int i = 0; w[a][i] != '\0', w[b][i] != '\0'; ++i)
		if(w[a][i] != w[b][i]) ++k;

	return (k <= 1);
}

void init(){

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			steps[i][j] = false;

	return;
}

int ladder(){

	int cur; // temp depth
	int max; // max depth
	int depth[MAXW]; // max depth reachable from any word

	// every node counts as a single step
	for(int i = 0; i < n; ++i) depth[i] = 1;

	// check nodes from start to finish
	// against everyone that comes after
	// in case of adjacent steps, update
	// max depth
	for(int i = n; i > 0; --i)
		for(int j = i; j < n; ++j)
			if(steps[j][i])
				{ cur = depth[i] + 1; if(cur > depth[j]) depth[j] = cur; }

	// find max depth
	max = 0;
	for(int i = 0; i < n; ++i)
		if(depth[i] > max) max = depth[i];

	return max;
}
