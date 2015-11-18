#include <iostream>

using namespace std;

/* data structures */

/* global variables */
char table[256];

/* function prototypes */
void init_table();

/* debug */

int main(){

	string s;

	init_table();

	while(!cin.eof()){

		getline(cin, s);

		// substitute each letter in the string
		for(int i = 0; i < s.size(); ++i) s[i] = table[s[i]];

		cout << s << endl;

	}

  return 0;
}

/* functions */
void init_table(){

	/* table fill */
	table[' '] = ' ';
	table['1'] = '`';
	table['2'] = '1';
	table['3'] = '2';
	table['4'] = '3';
	table['5'] = '4';
	table['6'] = '5';
	table['7'] = '6';
	table['8'] = '7';
	table['9'] = '8';
	table['0'] = '9';
	table['-'] = '0';
	table['='] = '-';
	table['W'] = 'Q';
	table['E'] = 'W';
	table['R'] = 'E';
	table['T'] = 'R';
	table['Y'] = 'T';
	table['U'] = 'Y';
	table['I'] = 'U';
	table['O'] = 'I';
	table['P'] = 'O';
	table['['] = 'P';
	table[']'] = '[';
	table['\\'] = ']';
	table['S'] = 'A';
	table['D'] = 'S';
	table['F'] = 'D';
	table['G'] = 'F';
	table['H'] = 'G';
	table['J'] = 'H';
	table['K'] = 'J';
	table['L'] = 'K';
	table[';'] = 'L';
	table['\''] = ';';
	table['X'] = 'Z';
	table['C'] = 'X';
	table['V'] = 'C';
	table['B'] = 'V';
	table['N'] = 'B';
	table['M'] = 'N';
	table[','] = 'M';
	table['.'] = ',';
	table['/'] = '.';
	table['w'] = 'w';
	table['e'] = 'e';
	table['r'] = 'r';
	table['t'] = 't';
	table['y'] = 'y';
	table['u'] = 'u';
	table['i'] = 'i';
	table['o'] = 'o';
	table['p'] = 'p';
	table['s'] = 's';
	table['d'] = 'd';
	table['f'] = 'f';
	table['g'] = 'g';
	table['h'] = 'h';
	table['j'] = 'j';
	table['k'] = 'k';
	table['l'] = 'l';
	table['x'] = 'x';
	table['c'] = 'c';
	table['v'] = 'v';
	table['b'] = 'b';
	table['n'] = 'n';
	table['m'] = 'm';
	/* end table fill */

	return;
}
