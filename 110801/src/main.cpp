#include <iostream>
#include <vector>
#define MAXN 8
#define MAXK 17

using namespace std;

/* data structures */
typedef struct pos { int x, y; } POSITION;

/* global variables */
vector<POSITION> p;
int s[MAXK];
int k; // number of bishops to include
int n; // board size

/* function prototypes */
// returns true if recursion depth limit reached
bool solution(int);

// stores count of generated solutions on a given level
void process_solution(int);

// construct candidate expansions for a given solution
// and returns its count
void construct_candidates(vector<POSITION>*);

// counts the total number of solutions for the
// same-colored bishops problem through backtracking
void backtrack(int);

// fills a given board with the attacked positions
// of the current solutions
// T = available position | F = attacked position
void fill_board(bool[MAXN][MAXN]);

// returns the number of candidates for the given board
// also fills a parameter candidate vector with these
void fill_solutions(vector<POSITION>*, bool[MAXN][MAXN]);

// initializes values of s and p
void init();

// combines solutions to a single count when the sum
// of two solutions' sizes equals the total
// in other words, combines two same-color bishop
// problems into the full bishop problem
int comb_solutions(int);

/* debug */

int main(){

	while(cin >> n >> k, n || k){

		init();

		backtrack(0);

		cout << comb_solutions(k) << endl;

	}

  return 0;
}

/* functions */
bool solution(int d){ return (d == k); }

void process_solution(int d) { ++s[d]; return; }

// construct candidate expansions for a given solution
// and returns its count
void construct_candidates(vector<POSITION> *cand){

	bool board[MAXN][MAXN];

	// fill board with attacked positions from current solution
	fill_board(board);

	// fill candidate vector with available positions
	// and track the generated amount
	fill_solutions(cand, board);

	return;
}

// counts the total number of solutions for the
// same-colored bishops problem through backtracking
void backtrack(int d){

	bool board[MAXN][MAXN];

	vector<POSITION> cand; // candidates vector

	if(d) process_solution(d);

	if(solution(d)) return; // return at recursion depth limit

	//construct_candidates(&cand); <- BUG!?!?!?

	// fill board with attacked positions from current solution
	fill_board(board);

	// fill candidate vector with available positions
	// and track the generated amount
	fill_solutions(&cand, board);

	// try increasing solution for every candidate
	for(int i = 0; i < cand.size(); ++i)
		{ p.push_back(cand.at(i)); backtrack(d+1); p.pop_back(); }

	return;
}

void fill_board(bool board[MAXN][MAXN]){

	POSITION c; // current piece

	// init
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			board[i][j] = true;

	// run TOP LEFT
	for(int i = 0; i < p.size(); ++i){

		c = p.at(i);

		// run TOP LEFT
		for(int j = 0; j <= min(		c.x,		 c.y); ++j) board[c.x-j][c.y-j] = false;

		// run TOP RIGHT
		for(int j = 0; j <= min(		c.x, n - c.y); ++j) board[c.x-j][c.y+j] = false;

		// run BOTTOM LEFT
		for(int j = 0; j <= min(n - c.x,		 c.y); ++j) board[c.x+j][c.y-j] = false;

		// run BOTTOM RIGHT
		for(int j = 0; j <= min(n - c.x, n - c.y); ++j) board[c.x+j][c.y+j] = false;
	}

	return;
}

void fill_solutions(vector<POSITION> *cand, bool board[MAXN][MAXN]){

	for(int i = 0; i < (n - 1); i += 2)
		for(int j = 0; j < (n - 1); j += 2)
			if(board[i][j]){ cand->push_back({i, j}); }

	return;
}

void init(){

	for(int i = 0; i < MAXK; ++i) s[i] = 0;

	p.clear();

}

int comb_solutions(int total){

	int sum;

	for(int i = 0; i <= total; ++i)
		for(int j = 0; j <= total; ++j)
			if((i + j) == total) sum += s[i] * s[j];

	return sum;
}
