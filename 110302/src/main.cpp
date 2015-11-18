#include <iostream>
#include <cctype>
#define S_GRID 51

using namespace std;

/* data structures */

/* global variables */
char grid[S_GRID][S_GRID];
int m, n; // current grid size

/* function prototypes */
// finds the indicated string in the grid starting at position x, y
// and going forward in xshift, yshift steps until it finds or
// reaches a border. returns true in case the word matches
bool find(char*, int p, int x, int y, int xshift, int yshift);

/* debug */

int main(){

	int t; // # of test cases
	int k; // # of words to search for
	char words[S_GRID][S_GRID];
	bool match; // flag to store matches
	bool first = true;

	cin >> t;

	for(; t > 0; --t){

		if(first) first = false; else cout << endl;

		cin >> m >> n >> ws;

		// read grid in lowercase
		for(int i = 1; i <= m; ++i) cin.getline(grid[i]+1, S_GRID);
		for(int i = 1; i <= m; ++i) for(int j = 1; j <=n; ++j)
			grid[i][j] = tolower(grid[i][j]);

		// read words in lowercase
		cin >> k >> ws;
		for(int i = 0; i <= k; ++i) cin.getline(words[i], S_GRID);
		for(int i = 0; i <= k; ++i)
			for(int j = 0; (j < S_GRID) && (words[i][j] != '\0'); ++j)
				words[i][j] = tolower(words[i][j]);

		// search for each word and print position
		// only look at the grid until first match
		for(int w = 0; w < k; ++w){

			match = false; // traverse grid
			for(int i = 1; (i <= m) && !match; ++i)
				for(int j = 1; (j <= n) && !match; ++j){

					// try all directions(modifier combinations) excluding 0, 0
					for(int g = -1; g <= 1; ++g) for(int h = -1; h <= 1; ++h)
						if((h != 0) || (g != 0))
							match = match || find(words[w], 0, i, j, g, h);

					// print where the word can be found
					if(match) cout << i << " " << j << endl;
				}
		}

	}

	return 0;
}

/* functions */
bool find(char *s, int p, int x, int y, int xshift, int yshift){

	if(s[p] == '\0') return true; // found whole word
	if((x < 1) || (x > m) || (y < 1) || (y > n)) return false; // hit border
	if(s[p] != grid[x][y]) return false; // word doesn't match

	x += xshift;
	y += yshift;

	return find(s, ++p, x, y, xshift, yshift);
}
