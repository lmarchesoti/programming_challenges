#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

/* structures */
/* end structures */

// global variables
int total_travelers;
vector<int> expenses;

/* function prototypes */

// formats and prints the final value
void pretty_print(int);

/* end function prototypes */

// debug

int main(){

  int exchange;
  char dot = '.'; // fill character in input to skip
  int tm, tc; // temporary money and temporary cents
  int total_expenses;
  int mean, rem;

  for(cin >> total_travelers; total_travelers != 0; expenses.clear(), cin >> total_travelers){

    // init values for this case
    total_expenses = 0;
    exchange = 0;

    // read expenses as integers to avoid rounding
    for(int i = 0; i < total_travelers; ++i){

      cin >> tm >> dot >> tc;
      tm = (tm * 100) + tc;
      expenses.push_back(tm);
      total_expenses += tm;
    }

    // sorting to keep track of who had more money in the beginning
    sort(expenses.begin(), expenses.end());

    // calculate mean of traveler expenses rounded down and the remainder
    mean = total_expenses / total_travelers;
    rem  = total_expenses % total_travelers;

    // find how much money should be moved by each traveler
    // to his desired final value. The extra eventual penny is due to
    // giving more money to those who have more already
    for(int i = total_travelers-1; i >= 0; --i, rem = rem ? --rem : 0)
      exchange += abs(expenses[i] - (mean + (rem ? 1 : 0)));

    exchange /= 2; // take receivers out

    pretty_print(exchange);
  }

  return 0;

}

/* functions */
void pretty_print(int value){

  int units = value / 100;
  int cents = (value - units*100);

  cout << "$" << units << "." << setfill('0') << setw(2) << cents << endl;

  return;

}
