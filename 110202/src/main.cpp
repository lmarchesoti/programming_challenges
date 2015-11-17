#include <iostream>
#include <algorithm>
#include <vector>
#define NUM_CARDS 13
#define HAND_SIZE 5

using namespace std;

/* data structures */
typedef struct s_player{

	int cards[HAND_SIZE];
	bool flush;
	bool straight;
	int freq[NUM_CARDS]; // records frequency of each card
	int same_val[HAND_SIZE]; // records number of same-valued cards
	int type; // type of hand
	vector<int> score; // scoring priority for comparison
} PLAYER;

/* global variables */
PLAYER black, white;

/* function prototypes */
// fills target vector by reverse frequencies and values of cards found in hand
void fill_by_rev_freq(int[NUM_CARDS], vector<int>*);

// reads hand and initializes scoring structures of player
void init_player(PLAYER*);

// returns suit-agnostic value of a card
int value(char card);

// rank_hands the player
void rank_hand(PLAYER*);

// extracts scoring patterns from the player's hand
void extract_patterns(PLAYER *p);

// compares the two players related to their scores
int compare(PLAYER *b, PLAYER *w);

/* debug */
template class std::vector<int>;

int main(){

	int cmp; // temp comparison variable
	int t = 0;

	while((cin.peek() != '\n') && !cin.eof()){
		++t;

		// read and convert hands
		init_player(&black);
		init_player(&white);

		// rank each hand
		rank_hand(&black);
		rank_hand(&white);

		// compare and print results
		cmp = compare(&black, &white);
		if(cmp == 1)  cout << "Black wins.\n";
		if(cmp == -1) cout << "White wins.\n";
		if(cmp == 0)  cout << "Tie.\n";

	}

  return 0;
}

/* functions */
void init_player(PLAYER *p){

		char v1, v2, v3, v4, v5; // temp card values
		char s1, s2, s3, s4, s5; // temp card suits

		cin >> v1 >> s1 >> v2 >> s2 >> v3 >> s3 >> v4 >> s4 >> v5 >> s5 >> ws;

		p->flush = false;
		// mark if all have the same suit
		if((s1 == s2) && (s2 == s3) && (s3 == s4) && (s4 == s5)) p->flush = true;

		// keep only card values
		p->cards[0] = value(v1);
		p->cards[1] = value(v2);
		p->cards[2] = value(v3);
		p->cards[3] = value(v4);
		p->cards[4] = value(v5);

		// init scoring structures
		for(int i = 0; i < NUM_CARDS; ++i) p->freq[i] = 0;
		for(int i = 0; i < HAND_SIZE; ++i) p->same_val[i] = 0;
		p->straight = true;
		p->score.clear();

	return;
}

int value(char card){

	int v; // return value

	switch(card){

		case 'T': v = 8; break;
		case 'J': v = 9; break;
		case 'Q': v = 10; break;
		case 'K': v = 11; break;
		case 'A': v = 12; break;
		
		default: v = (card - 50) % 13;

	}

	return v;

}

void rank_hand(PLAYER* p){

	bool straight;

	// sort hand
	sort(p->cards, p->cards + HAND_SIZE);

	// extract patterns
	extract_patterns(p);

	// match patterns to types
	p->type = 0;
	if(p->same_val[2]) p->type = 1;
	if(p->same_val[2] == 2) p->type = 2;
	if(p->same_val[3]) p->type = 3;
	if(p->straight) p->type = 4;
	if(p->flush) p->type = 5;
	if(p->same_val[3] && p->same_val[2]) p->type = 6;
	if(p->same_val[4]) p->type = 7;
	if((p->straight) && (p->flush)) p->type = 8;

	// fill score priorities
	switch(p->type){

		case 0: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 1: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 2: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 3: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 4: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 5: // doesn't take frequency into account
			for(int i = 0; i < NUM_CARDS; ++i)
				p->score.push_back(p->cards[i]);
			break;

		case 6: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 7: fill_by_rev_freq(p->freq, &(p->score)); break;

		case 8: fill_by_rev_freq(p->freq, &(p->score)); break;

		default: break;

	}

	return;
}

void extract_patterns(PLAYER *p){

	// track straight
	for(int i = 0; i < (HAND_SIZE - 1); ++i)
		if((p->cards[i+1] - p->cards[i]) != 1) p->straight = false;

	// fill frequency
	for(int i = 0; i < HAND_SIZE; ++i) ++p->freq[p->cards[i]];

	// extract final frequencies
	for(int i = 0; i < NUM_CARDS; ++i) ++p->same_val[p->freq[i]];

	return;
}

int compare(PLAYER *b, PLAYER *w){

	if(b->type > w->type) return 1;
	if(b->type < w->type) return -1;
	
	for(; (b->score.size() > 0) && (w->score.size() > 0); b->score.pop_back(), w->score.pop_back()){

		if(b->score.back() > w->score.back()) return 1;
		if(b->score.back() < w->score.back()) return -1;

	}

	return 0;
}

void fill_by_rev_freq(int freq[NUM_CARDS], vector<int> *score){

	for(int j = 1; j <= HAND_SIZE; ++j) // frequency
		for(int k = 0; k < NUM_CARDS; ++k) // freq vector
			if(freq[k] == j) score->push_back(k);
	// more robust way that *currently* fails tests
	//while(freq[k]) { score->push_back(k); --freq[k]; }
	return;
}
