#include <iostream>
#include <iomanip>
#include <cmath>
#define MAXN 100
#define MAXINT 2147483647

using namespace std;

/* data structures */
typedef struct { float x, y; } node;

/* global variables */
int n; // number of nodes
float g[MAXN][MAXN]; // adjacency matrix

/* function prototypes */
// calculate euclidean distance between two points
float distance(const node, const node);

// runs prim's algorithm and returns minimum spanning tree cost
float prim(const int);

/* debug */

int main(){

	int t; // test cases
	float d; // temporary distance between two nodes
	node nodes[MAXN];
	float x, y; // temp

	cin >> t;
	cout << std::setprecision(2) << std::fixed;

	while(t--){

		cin >> n;

		// read nodes
		for(int i = 0; i < n; ++i){

			cin >> x >> y;
			nodes[i].x = x;
			nodes[i].y = y;
		}

		// calculate connectivity matrix
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j){

				d = distance(nodes[i], nodes[j]);
				g[i][j] = d;
				g[j][i] = d;
			}

		// run prim's algorithm and print cost
		cout << prim(0) << endl;
	}

  return 0;
}

/* functions */
float distance(const node n1, const node n2){

	float dx = abs(n1.x - n2.x); // distance along x axis
	float dy = abs(n1.y - n2.y); // distance along y axis

	dx *= dx; dy *= dy; // pow2

	return sqrt(dx + dy);
}

float prim(const int start){

	int v;								// current node
	float dist;						// temporary distance
	bool intree[MAXN];		// control of included nodes
	float distance[MAXN];
	float cost = 0;
	
	// init nodes
	for(int i = 0; i < n; ++i) { intree[i] = false; distance[i] = MAXINT; }

	// include all nodes one at a time through the
	// lowest cost edge that connects the graph
	// keep track of the shortest path available
	// to each node by updating the incorporated
	// node's edges

	distance[start] = 0;
	v = start;

	while(!intree[v]){

		intree[v] = true;

		// update edges
		for(int i = 0; i < n; ++i)
			if((distance[i] > g[v][i]) && !intree[i])
				distance[i] = g[v][i];

		// select next node based on cheapest edge
		v = -1;
		dist = MAXINT;
		for(int i = 0; i < n; ++i)
			if(!intree[i] && (dist > distance[i]))
				{ dist = distance[i]; v = i; }

		if(v != -1) cost += dist; // account for included edge
	}

	return cost;
}
