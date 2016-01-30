#include <iostream>
#include <cmath>

using namespace std;

/* data structures */

/* global variables */
long long n1, n2; // numbers
long long d1, d2; // digits
long long count, carry;
long long sum; // local sum

/* function prototypes */

/* debug */

int main(){

	bool first = true;

	while(cin >> n1 >> n2, (n1 != 0) || (n2 != 0)){

		// init
		count = 0;
		carry = 0;

		n1 = abs(n1);
		n2 = abs(n2);

		while((n1 > 0) || (n2 > 0)){

			carry = (n1%10 + n2%10 + carry)/10;

			n1 /= 10; n2 /= 10; // shift digits

			if(carry) ++count;

		}

		switch(count){ 
			case 0: cout << "No carry operation." << endl; break;
			case 1: cout << "1 carry operation." << endl; break;
			default: cout << count << " carry operations." << endl; 
		}

	}

  return 0;
}

/* functions */
