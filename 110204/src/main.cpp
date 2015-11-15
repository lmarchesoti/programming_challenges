#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define TABLE_START 97 // 'a' code
#define TABLE_SIZE (TABLE_START + 25) // 25 letters

using namespace std;

/* data structures */

/* global variables */
int n; // number of words in the dictionary
vector<string> originals; // dictionary
vector<string> codes; // words in phrase
vector<int> ass; // assignment vector
char s_table[TABLE_SIZE]; // symbol table

/* function prototypes */

// create assignment vector incrementally and test for each possibility
bool increment_and_test(int, int);

// test if current assignment of words create a valid symbol table
bool test_table(int);

/* debug */
template class std::vector<string>;

int main(){

	string phrase;
	string s; // temporary string
	stringstream ss; // temporary stringstream

	cin >> n;

	// read dictionary in
	for(int i = 0; i < n; ++i){ cin >> s; originals.push_back(s); }
	cin >> ws; // remove blanks until next line

	// for every test case
	while((cin.peek() != '\n') && !cin.eof()){

		ass.clear();
		ass.resize(n);

		// read next input phrase and tokenize into codes vector
		while((cin.peek() != '\n') && !cin.eof()){

			cin >> s;
			codes.push_back(s);
			ss << " " << s;
		}

		phrase = ss.str();

		// create symbol table if possible
		if(!increment_and_test(0, n))
			for(int i = TABLE_START; i < TABLE_SIZE; ++i) s_table[i] = '*';

		// print output

	}

  return 0;
}

/* functions */
bool increment_and_test(int cur, int size){

	bool valid;

	for(int i = 0; i < size; ++i){

		ass[cur] = i;
		valid = (cur == size) ? test_table(size) : increment_and_test(cur+1, size);
		if(valid) return true;

	}

	return false;
}

bool test_table(int size){

	// check words lengths
	for(int i = 0; i < size; ++i)
		if(originals[i].size() != codes[ass[i]].size()) return false;

	// attempt to create table

	return true;
}
