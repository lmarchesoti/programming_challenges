#include <iostream>
#include <queue>
#define MAXN 200

using namespace std;

/* data structures */

/* global variables */
/* graph */
bool adj[MAXN][MAXN]; // adjacency matrix
int n, m; // number of nodes and edges
/* end graph */

bool processed[MAXN];
bool discovered[MAXN];
int parent[MAXN];
int color[MAXN];

/* function prototypes */
// creates an empty graph
// inits parent, processed and discovered control
void init();

// reads graph
void read();

// inserts edge in graph
void insert_edge(int, int);

// implements bfs
bool bfs();

// sets the color of the vertex according to its parent
void process_vertex(int);

/* debug */

int main(){

	while(cin >> n, n){

		init();

		read();

		if(bfs()) cout << "BICOLORABLE."		 << endl;
		else			cout << "NOT BICOLORABLE." << endl;
	}

  return 0;
}

/* functions */
void init(){

	// graph
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			adj[i][j] = false;

	for(int i = 0; i < n; ++i) color[i] = 0;

	// bfs structures
	for(int i = 0; i < n; ++i)
		{ parent[i] = -1; discovered[i] = false; processed[i] = false; }

}

void read(){

	int a, b; // temp edges

	cin >> m; // read # of edges

	for(int i = 0; i < m; ++i) { cin >> a >> b; insert_edge(a, b); }

	return;
}

void insert_edge(int a, int b){ adj[a][b] = true; adj[b][a] = true; return; }

bool bfs(){

	queue<int> q; // queue of nodes to visit
	int v;	 // current vertex

	q.push(0);	// start at node 0
	discovered[0] = true;
	parent[0] = 0;

	while(!q.empty()){

		// get vertex and process it
		v = q.front(); q.pop();
		process_vertex(v);
		processed[v] = true;

		// process every edge from v
		for(int i = 0; i < n; ++i){

			if(adj[v][i]){

				// can't have adjacent nodes of equal color
				if(color[i] == color[v]) return false;

				if(!discovered[i]) // enqueue
					{ q.push(i); discovered[i] = true; parent[i] = v; }
			}
		}
	}

	return true;
}

void process_vertex(int v){ color[v] = color[parent[v]]%2 + 1; return; }
