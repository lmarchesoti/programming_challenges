#include <iostream>
#define WORD_S 1005
#define ALPH_S 'z'+1

using namespace std;

/* data structures */

/* global variables */

/* function prototypes */
// creates a count table for each character present in the string
void create_table(char*, int*);

/* debug */

int main(){

	char a[WORD_S], b[WORD_S]; // words
	int ta[ALPH_S], tb[ALPH_S]; // tables
	bool first = true;

	while(!cin.eof()){

		if(first) first = false; else cout << endl;

		// read words
		cin.getline(a, WORD_S);
		cin.getline(b, WORD_S);

		// create a letter table for each word
		create_table(a, ta);
		create_table(b, tb);
				
		// print them in alphabetical order
		for(char i = 'a'; i <= 'z'; ++i){

			if((ta[i] != 0) && (tb[i] != 0)){

				for(int j = 0; j < min(ta[i], tb[i]); ++j, cout << i);
			}

		}

	}

  return 0;
}

/* functions */
void create_table(char *s, int *table){

	for(char i = 'a'; i <= 'z'; ++i) table[i] = 0;
	for(int i = 0; s[i] != '\0'; ++i) ++table[s[i]];

	return;
}
