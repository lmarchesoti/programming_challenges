#include <string>
#include <iostream>
#define DECKSIZE 53

using namespace std;

/* data structures */

/* global variables */
int shuffles[101][DECKSIZE];
int decks[2][DECKSIZE];

/* function prototypes */

// shuffles base deck onto target deck using the transformation in the transform array
void shuffle_deck(int*, int*, int*);

// prints the formatted deck
void print_deck(int*);

// returns the string value of a given card code
string value(int);

// returns the suit of a given card code
string suit(int);

/* debug */

int main(){

	int t; // number of test cases
	int n; // number of known shuffles
	int shuffle; // current shuffle to apply
	int deck; // currently used deck
	bool first = true; // first testcase flag

	cin >> t; // read number of test cases

	// for each test case
	for(; t > 0; --t){

		if(first) first = false;
		else cout << endl;

		// init decks
		deck = 0; // currently used deck
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < DECKSIZE; ++j) decks[i][j] = j;

		cin >> n; // read number of shuffles

		// read shuffles in
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < DECKSIZE; ++j)
				cin >> shuffles[i][j];

		cin >> ws; // remove trailing whitespaces

		// apply shuffles until next case
		while((cin.peek() != '\n') && !cin.eof()){

			cin >> shuffle; cin.get();
			shuffle_deck(decks[deck], decks[(deck+1)%2], shuffles[shuffle]);

			deck = (deck+1)%2; // cyclic update current deck

		}

		print_deck(decks[deck]);
	}

  return 0;
}

/* functions */
void shuffle_deck(int *base, int *target, int *transform){

	for(int i = 1; i < DECKSIZE; ++i)
		target[i] = base[transform[i]];

	return;
}

void print_deck(int *base){

	for(int i = 1; i < DECKSIZE; ++i)
		cout << value(base[i]) << " of " << suit(base[i]) << endl;

	return;
}

string value(int val){

	switch(val%13){

		case 0: return "Ace"; break;
		case 1: return "2"; break;
		case 2: return "3"; break;
		case 3: return "4"; break;
		case 4: return "5"; break;
		case 5: return "6"; break;
		case 6: return "7"; break;
		case 7: return "8"; break;
		case 8: return "9"; break;
		case 9: return "10"; break;
		case 10: return "Jack"; break;
		case 11: return "Queen"; break;
		case 12: return "King"; break;
		default: break;
		
	}

	return "Error";
}

string suit(int val){

	--val;
	switch(val/13){

		case 0: return "Clubs"; break;
		case 1: return "Diamonds"; break;
		case 2: return "Hearts"; break;
		case 3: return "Spades"; break;
		default: break;

	}

	return "Error";
}
