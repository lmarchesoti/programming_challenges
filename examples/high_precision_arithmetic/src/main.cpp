#include <iostream>
#define MAXD	100	// maximum number of digits
#define PLUS	 1
#define MINUS -1

/* This program uses Big Endian representation */

using namespace std;

/* data structures */
typedef struct {

	char d[MAXD]; // digits vector
	int size, sign;
} big_int;

/* global variables */
big_int ac; // accumulator
big_int op; // operand

/* function prototypes */
/* apply signal rules and call underlying */
/* unsigned routines											*/
/* always store result on first argument	*/
void sum(big_int&, big_int&);
void diff(big_int&, big_int&);
void prod(big_int&, const big_int&); 
void quot(big_int&, big_int&); 
/* end																		*/

/* unsigned routines	*/
void add(const big_int&, const big_int&, big_int&); 
void sub(big_int&, const big_int&); 
void mul(const big_int&, const big_int&, big_int&); 
void div(const big_int&, const big_int&, big_int&); 
/* end								*/

// borrows in current position of a given integer
// leaves the number in a valid state
void borrow(big_int&, int);

// multiplies by 10 a big integer
void shift(big_int&);

// compares two big integers on their magnitudes
bool m_comp(const big_int&, const big_int&);

// prints the accumulator
void print_ac();

// initializes a new big integer
void init_big_int(big_int&);

// reads operand
void read_op();

// trim leading zeros
// and fixes -0
void trim(big_int&);

/* debug */

int main(){

	int opr; // operator

	init_big_int(ac);

	while(cin >> opr, opr != 0){

		switch(opr){

			case 1: read_op(); sum(ac, op); break;

			case 2: read_op(); diff(ac, op); break;

			case 3: read_op(); prod(ac, op); break;

			case 4: read_op(); quot(ac, op); break;

			default: break;

		}

		print_ac();

	}

  return 0;
}

/* functions */
// (+a) + (+b) = (+a) + (+b)
// (-a) + (-b) = -(a + b)
// (+a) + (-b) = (+a) - (+b)
// (-a) + (+b) = (+b) - (+a)
void sum(big_int &a, big_int &b){

	big_int r; init_big_int(r); // result

	if(a.sign == b.sign)
		{ add(a, b, r); r.sign = a.sign; a = r; }
	else {

		if(a.sign == PLUS) { b.sign = PLUS; diff(a, b); b.sign = MINUS; }
		else							 { diff(b, a); a = b; } 
	}

	trim(a); return;
}

// (+a) - (+b) = (+a) - (+b)
// (-a) - (-b) = (+b) - (+a)
// (+a) - (-b) = (+a) + (+b)
// (-a) - (+b) = (-a) + (-b)
void diff(big_int &a, big_int &b){

	// sum numbers of different sign
	// and keep magnitude of higher
	if(a.sign != b.sign) sum(a, b);
	else{ // subtract with higher magnitude on top
				// invert sign when b > a

		if(m_comp(a, b)) sub(a, b);
		else { sub(b, a); a = b; a.sign *= MINUS; } 
	}

	trim(a); return;
}

/* invokes the multiplication procedure */
/* and calculates the sign							*/
void prod(big_int &a, const big_int &b){

	big_int r; init_big_int(r); // result

	mul(a, b, r); 
	r.sign = a.sign * b.sign; 
	a = r;

	return;
}

/* divides a by b if a > b. otherwise returns 0 */
void quot(big_int &a, big_int &b){

	big_int r; init_big_int(r); // result

	if(m_comp(a, b)) div(a, b, r);

	r.sign = a.sign * b.sign;
	a = r;

	trim(a);

	return;
}

/* adds each digit and keeps track of carry */
void add(const big_int &a, const big_int &b, big_int &r){

	int t; // temporary sum value
	int carry;

	r.size = max(a.size, b.size) + 1;

	carry = 0;
	for(int i = 0; i < r.size; ++i)
		{ t = carry + a.d[i] + b.d[i]; r.d[i] = t%10; carry = t/10; }

	return;
}

// subtract each place, borrowing when necessary
void sub(big_int &a, const big_int &b){

	for(int i = 0; i < b.size; ++i)
		{ if(a.d[i] < b.d[i]) borrow(a, i); a.d[i] -= b.d[i]; }

	return;
}

// make a borrow operation (+10 current number, -1 next)
// until the number ends or borrowing doesn't make a digit
// go below 0
void borrow(big_int &a, int i){

	do { a.d[i] += 10; a.d[i+1] -= 1; }
	while(++i, (i < a.size) && (a.d[i] < 0));

	return;
}

/* uses the row by row method (shifting the answer */
/* with repeated addition													 */
void mul(const big_int &a, const big_int &b, big_int &r){

	big_int t; // temporary value
	bool first = true;

	for(int i = b.size - 1; i >= 0; --i){

		init_big_int(t);
		
		if(first) first = false; else shift(r);

		for(int j = 0; j < b.d[i]; ++j)
			{ add(r, a, t); trim(t); r = t; } 
	}

	return;
}

/* uses the method of repeated addition to extract factors */
void div(const big_int &a, const big_int &b, big_int &r){

	big_int t; init_big_int(t); // temp

	r.size = a.size;

	for(int i = a.size - 1; i >= 0; --i){

		trim(t); shift(t); t.d[0] = a.d[i];

		while(!m_comp(b, t)) { ++r.d[i]; sub(t, b); } 
	}

	return;
}

/* compares the size, then each most significant digit */
/* on draw returns false to signal that a is not > b   */
bool m_comp(const big_int &a, const big_int &b){

	if(a.size > b.size) return true;
	if(a.size < b.size) return false;

	for(int i = a.size - 1; i >=0; --i){

		if(a.d[i] > b.d[i]) return true;
		if(a.d[i] < b.d[i]) return false; 
	}

	return false;
}

/* prints digit by digit. notice the cast conversion */
/* zero-sized values are printed as 0								 */
void print_ac(){

	if(ac.sign == MINUS) cout << "-";
	if(ac.size == 0) cout << 0;

	for(int i = ac.size - 1; i >= 0; --i)
		cout << (char) (ac.d[i] + '0');

	cout << endl;

	return;
}

/* sets size = 0, sign = plus, and initializes	 */
/* every digit to 0															 */
void init_big_int(big_int &a){

	a.size = 0; a.sign = PLUS;
	for(int i = 0; i < MAXD; ++i) a.d[i] = 0;

	return;
}

/* re-initializes op, reads new value as integer */
/* choose sign and convert digit by digit by		 */
/* repeated rem and div													 */
void read_op(){

	int t;	// temporary operand

	init_big_int(op);

	cin >> t; // pick sign
	if(t > 0) op.sign = PLUS;
	else			op.sign = MINUS;

	t = abs(t);
	// repeatedly extract least significant digit
	while(t > 0) { op.d[op.size] = t%10; t /= 10; ++op.size; }

	return;
}

/* trims most significant zeroes and changes sign of -0	 */
void trim(big_int	&a){

	for(int i = a.size-1; (i >= 0) && (a.d[i] == '\0'); --i, --a.size);

	// avoid -0
	if((a.size == 0) && (a.d[0] == 0)) a.sign = PLUS;

	return;
}

/* increases number size, copies each digit to the right */
/* and initializes least significant one to 0						 */
void shift(big_int &a){

	++a.size;
	for(int i = a.size; i > 0; --i) a.d[i] = a.d[i-1];

	a.d[0] = 0;

	return;
}
