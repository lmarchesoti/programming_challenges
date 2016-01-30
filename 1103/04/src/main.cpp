#include <iostream>
#include <cstring>
#define PHRASE_S 81
#define BUF_S 100
#define ALPH_S 'z'+1

using namespace std;

/* data structures */

/* global variables */
char table[ALPH_S];

/* function prototypes */
// matches buffered phrase to template and create symbol table if possible
bool match_template(const char*);

// prints decoded message line by line
void print_decoded(const char*);

/* debug */

int main(){

	int t; // test cases
	int l; // line count
	char buffer[BUF_S][PHRASE_S];
	bool match;
	bool first = true;

	cin >> t >> ws;

	for(; t > 0; --t){

		if(first) first = false; else cout << endl;

		// read lines into buffer
		for(l = 0; (cin.peek() != '\n') && (!cin.eof()); ++l)
			cin.getline(buffer[l], BUF_S);
		cin >> ws;

		match = false;// try matching a line to template
		for(int i = 0; (i < l) && !match; ++i)
			match = match_template(buffer[i]);

		// output solution
		if(match) for(int i = 0; i < l; ++i) print_decoded(buffer[i]);
		else cout << "No solution." << endl;
	}

  return 0;
}

/* functions */

bool match_template(const char *line){

	const char *templ = "the quick brown fox jumps over the lazy dog";
	int templength = 43;
	int assign_c[ALPH_S]; // assignment count of each letter in table
	bool valid = true;

	// if phrase matches length, assign letters to table sequentially
	if(strlen(line) == templength){

		for(int i = 0; i < templength; ++i) table[line[i]] = templ[i];

		// check if each character is unique
		for(char i = 'a'; i < ALPH_S; ++i) assign_c[i] = 0;
		for(char i = 'a'; i < ALPH_S; ++i) ++assign_c[table[i]];
		for(char i = 'a'; i < ALPH_S; ++i) if(assign_c[i] != 1) valid = false;
	} else valid = false;

	return valid;
}

void print_decoded(const char *line){

	for(int i = 0; i < strlen(line); ++i) cout << table[line[i]];
	cout << endl;

	return;
}
