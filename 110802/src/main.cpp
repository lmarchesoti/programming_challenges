#include <iostream>
#define PSIZE 4
#define ALPHA 'Z' + 1
#define MAX_MOVES 50
#define BEG 0
#define END 3

using namespace std;

/* data structures */

/* global variables */
int puzzle[PSIZE][PSIZE];
int moves[MAX_MOVES + 1];
int sol[PSIZE][PSIZE];	// solution model
int ssize;							// size of solution
int row, col;						// position of blank
int rev[ALPHA];					// reverse move dictionary

/* function prototypes */
// finds solution to the puzzle as long as there is one
bool backtrack(const char);

// checks if current puzzle state is a solution
bool solution();

// initializes global structures
void init();

// applies move to puzzle
void move(const int, const char);

// starts backtracking without a previous move
bool invoke_bt();

// prints solution vector
void print_solution();

/* debug */

int main(){

	int t;

	init();

	cin >> t;

	while(t--){

		// read puzzle
		for(int i = BEG; i < PSIZE; ++i)
			for(int j = BEG; j < PSIZE; ++j)
				cin >> puzzle[i][j];

		// find solution
		if(invoke_bt()) print_solution();
		else cout << "This puzzle is not solvable." << endl;

	}

  return 0;
}

/* functions */
bool backtrack(const int k, const char m){

	move(m);

	if(solution()) { ssize = k; return true; }

	if(k > MAX_MOVES) return false;

	// try each allowed possibility
	if((row != BEG) && (rev[moves[k-1]] != 'U')) if(backtrack(k+1, 'U')) return true; 
	if((row != END) && (rev[moves[k-1]] != 'D')) if(backtrack(k+1, 'D')) return true; 
	if((col != BEG) && (rev[moves[k-1]] != 'L')) if(backtrack(k+1, 'L')) return true; 
	if((col != END) && (rev[moves[k-1]] != 'R')) if(backtrack(k+1, 'R')) return true; 

	move(k, rev[m]); // undo current move before returning

	return false;
}

bool solution(){

	for(int i = BEG; i < PSIZE; ++i)
		for(int j = BEG; j < PSIZE ; ++j)
			if(puzzle[i][j] != sol[i][j]) return false;

	return true;
}

void init(){

	rev['U'] = 'D';
	rev['D'] = 'U';
	rev['L'] = 'R';
	rev['R'] = 'L';

	for(int i = BEG; i < PSIZE; ++i)
		for(int j = BEG; j < PSIZE ; ++j)
			sol[i][j] = PSIZE*i + j;

	sol[END][END] = 0;

/*
	sol = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}};
*/

	return;
}

void move(const int k, const char m){

	moves[k] = m;

	switch(m){

		case 'L': puzzle[row][col] = puzzle[row][col-1]; col = col-1;
							puzzle[row][col] = 0;
							break;

		case 'R': puzzle[row][col] = puzzle[row][col+1]; col = col+1;
							puzzle[row][col] = 0;
							break;

		case 'U': puzzle[row][col] = puzzle[row-1][col]; row = row - 1;
							puzzle[row][col] = 0;
							break;

		case 'D': puzzle[row][col] = puzzle[row][col-1]; row = row + 1;
							puzzle[row][col] = 0;
							break;

		default: return;

	}

	return;
}

bool invoke_bt(){

	int k = 0;

	if(solution()) { ssize = k; return true; }

	// init row/col
	for(int i = BEG; i < PSIZE; ++i)
		for(int j = BEG; j < PSIZE; ++j)
			if(puzzle[i][j] == 0) row = i, col = j;

	// try each allowed possibility
	if(row != BEG) if(backtrack(k+1, 'U')) return true; 
	if(row != END) if(backtrack(k+1, 'D')) return true; 
	if(col != BEG) if(backtrack(k+1, 'L')) return true; 
	if(col != END) if(backtrack(k+1, 'R')) return true; 

	return false;
}

void print_solution()
	{ for(int i = 1; i <= ssize; ++i) cout << moves[i]; cout << endl; }
