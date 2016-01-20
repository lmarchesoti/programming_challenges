#include <iostream>
#include <queue>
#define NSUITS 4
#define NVALUES 13
#define MAXSTEPS 1000000

using namespace std;

/* data structures */
char values[] = "23456789TJQKA";
char suits[] = "cdhs";

/* global variables */
queue<int> p1, p2;		// players
queue<int> prize;			// prize vector for game
int steps;						// game duration

/* function prototypes */
// reads a given player's cards
void read(queue<int>*);

// simulates the game
// 0 - tie; 1 - p1 wins; 2 - p2 wins;
int war();

// ranks a card based on its suit and value
int rank_card(char, char);

// returns a card's suit
char suit(int);

// returns a card's value
char value(int);

// gives prize to the specified player
void claim_prize(queue<int>*);

// empties queue
void empty_queue(queue<int>*);

/* debug */
template class std::queue<int>;

int main(){

	while(!cin.eof()){

		read(&p1);
		read(&p2);

		switch(war()){

			case 0: cout << "Tie in " << steps << " steps." << endl; break;

			case 1: cout << "Player 1 wins in " << steps << " steps." << endl; break;

			case 2: cout << "Player 2 wins in " << steps << " steps." << endl; break;

			default: cout << "Error" << endl; break;

		}

		// cleanup
		empty_queue(&p1);
		empty_queue(&p2);
	}

  return 0;
}

/* functions */
void read(queue<int> *p){

	char s;	// suit
	char v;	// value

	for(int i = 0; i < 26; ++i)
		{ cin >> v >> s; p->push(rank_card(s, v)); }

	cin >> ws;

}

int war(){

	int x, y;	// p1 and p2's draw cards, respectively
	bool war = false;

	steps = 0;

	while(!p1.empty() && !p2.empty() && (steps < MAXSTEPS)){

		++steps;

		// get cards
		x = p1.front(); p1.pop();
		y = p2.front(); p2.pop();

		prize.push(x); prize.push(y);	// put them on prize stack

		if(war) { war = false; continue; } // skip round for extra card

		if(value(x) >  value(y)) claim_prize(&p1);

		if(value(x) <  value(y)) claim_prize(&p2);

		if(value(x) == value(y)) war = true;

	}

	// cleanup
	empty_queue(&prize);

	if(!p1.empty() && p2.empty()) return 1; // p1 wins

	if(p1.empty() && !p2.empty()) return 2; // p2 wins

	return 0; // tie
}

void claim_prize(queue<int> *p)
{ while(!prize.empty()){ p->push(prize.front()); prize.pop(); } }

// compares the given suit and value to the reference
// vectors and returns the rank in value-grouped form
int rank_card(char suit, char value){

	for(int s = 0; s < NSUITS; ++s) if(suits[s] == suit)
		for(int v = 0; v < NVALUES; ++v) if(values[v] == value)
			return v*NSUITS + s;

}

char suit(int card){ return suits[card%NSUITS]; }

char value(int card){ return values[card/NSUITS]; }

void empty_queue(queue<int> *q){ while(!q->empty()) q->pop(); }
