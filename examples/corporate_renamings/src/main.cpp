#include <iostream>
#define MAXCHANGES 100
#define MAXLEN 1001 // extra character for null terminator
#define W 0
#define M 1

using namespace std;

/* data structures */

/* global variables */
string dictionary[MAXCHANGES][2]; // word/match array
string line;
int n;	// number of changes

/* function prototypes */
// reads the next change and stores it in the dictionary
void read_changes();

// replaces in the current line any full matches of
// words in the dictionary in alphabetical order
void process_line();

// finds the first match of the given word in the current line
int find_first_match(string&);

// substitute a word by its match in the given position
void substitute(int, string&, string&);

// returns true if the given word matches at the
// given position in the line
bool position_match(int, string&);

// shifts string to the right starting at the specified position
void rshift(int, int);

// shifts string to the left starting at the specified position
void lshift(int, int);

/* debug */

int main(){

	int t; // number of lines

	cin >> n;
	read_changes();

	cin >> t; cin.get(); // process lines
	for(int i = 0; i < t; ++i){

		// take line in and process
		getline(cin, line); process_line();

		// output correct line
		cout << line << endl;
	}

  return 0;
}

/* functions */
void read_changes(){

	for(int i = 0; i < n; ++i){

		cin.ignore(1, '"'); // ignore first quote

		// read word
		getline(cin, dictionary[i][W], '"');

		// ignore fill
		cin.ignore(1, '"'); cin.ignore(5, '"');

		// read match
		getline(cin, dictionary[i][M], '"');
	}

	return;
}

void process_line(){

	int p; // position of match

	// for each word in dictionary
	// replace matches while they can be found
	for(int i = 0; i < n; ++i)
		while(p = find_first_match(dictionary[i][W]), p != -1)
			substitute(p, dictionary[i][W], dictionary[i][M]);

	return;
}

int find_first_match(string &word){

	for(int p = 0; p < (line.length() - word.length()); ++p)
		if(position_match(p, word)) return p;

	return -1;
}

void substitute(int p, string &word, string &match){

	int d; // length difference between word and match

	// accomodate space
	d = match.length() - word.length();
	if(d > 0) rshift(p,	 d);
	if(d < 0) lshift(p, -d);

	// copy match over line
	for(int i = 0; i < match.size(); ++i) line[p+i] = match[i];

	return;
}

bool position_match(int p, string &word){

	for(int i = 0; i < word.length(); ++i)
		if(word[i] != line[p+i]) return false;

	return true;
}

void rshift(int p, int diff){

	line.resize(line.length()+diff);

	// copy line diff places to the right, starting at p
	for(int i = line.length(); i > (p+diff); --i)
		line[i] = line[i-diff];

	return;
}

void lshift(int p, int diff){

	// copy line diff places to the left, starting at p
	for(int i = p+diff; i < line.length(); ++i)
		line[i-diff] = line[i];

	line.resize(line.length()-diff);

	return;
}
