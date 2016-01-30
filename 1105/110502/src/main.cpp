#include <iostream>

using namespace std;

/* data structures */

/* global variables */
unsigned int p, revp;

/* function prototypes */
// reverses p into revp
unsigned int reverse(unsigned int);

// checks if p and revp form a palindrome
bool palindrome();

/* debug */

int main(){

	int n, i;

	cin >> n;

	while(n--){

		cin >> p; revp = reverse(p);

		for(i = 0; !palindrome(); ++i) p = p + revp, revp = reverse(p);

		cout << i << " " << p << endl;

	}

  return 0;
}

/* functions */
unsigned int reverse(unsigned int n){

	unsigned int rev = 0;

	// iteratively get the next digit from n and
	// reformat rev to accomodate it
	while(n != 0) rev *= 10, rev += n%10, n /= 10;

	return rev;
}

bool palindrome(){ if (p == revp) return true; return false; }
