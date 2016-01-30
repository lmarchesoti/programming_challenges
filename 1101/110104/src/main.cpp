#include <iostream>

using namespace std;

typedef char DFORMAT[5][3]; // format matrix for each number

// specifies the 5x3 model to be followed when drawing each digit
DFORMAT dformat[10] = {
{{' ', '-', ' '} // zero
,{'|', ' ', '|'}
,{' ', ' ', ' '}
,{'|', ' ', '|'}
,{' ', '-', ' '}},
{{' ', ' ', ' '} // one
,{' ', ' ', '|'}
,{' ', ' ', ' '}
,{' ', ' ', '|'}
,{' ', ' ', ' '}},
{{' ', '-', ' '} // two
,{' ', ' ', '|'}
,{' ', '-', ' '}
,{'|', ' ', ' '}
,{' ', '-', ' '}},
{{' ', '-', ' '} // three
,{' ', ' ', '|'}
,{' ', '-', ' '}
,{' ', ' ', '|'}
,{' ', '-', ' '}},
{{' ', ' ', ' '} // four
,{'|', ' ', '|'}
,{' ', '-', ' '}
,{' ', ' ', '|'}
,{' ', ' ', ' '}},
{{' ', '-', ' '} // five
,{'|', ' ', ' '}
,{' ', '-', ' '}
,{' ', ' ', '|'}
,{' ', '-', ' '}},
{{' ', '-', ' '} // six
,{'|', ' ', ' '}
,{' ', '-', ' '}
,{'|', ' ', '|'}
,{' ', '-', ' '}},
{{' ', '-', ' '} // seven
,{' ', ' ', '|'}
,{' ', ' ', ' '}
,{' ', ' ', '|'}
,{' ', ' ', ' '}},
{{' ', '-', ' '} // eight
,{'|', ' ', '|'}
,{' ', '-', ' '}
,{'|', ' ', '|'}
,{' ', '-', ' '}},
{{' ', '-', ' '} // nine
,{'|', ' ', '|'}
,{' ', '-', ' '}
,{' ', ' ', '|'}
,{' ', '-', ' '}}};

// prints n with s as a base size
void print_by_row(string n, int s);

// prints the specified row following the model for each digit
void print_row(string n, int row, int s);

int main(){

  int s; // size to display the number
  string n; // number to be displayed

  // for each test case
  for(cin >> s >> n; (s != 0) || (n.compare("0") != 0); cin >> s >> n){

    // print the number in the required format
    print_by_row(n, s);

    // print an extra newline
    cout << endl;

  }

  return 0;
}

void print_by_row(string n, int s){

  print_row(n, 0, s);	  // print first - row
  for(int i = 0; i < s; ++i)
    print_row(n, 1, s); // print s | rows
  print_row(n, 2, s);	  // print second - row
  for(int i = 0; i < s; ++i)
    print_row(n, 3, s); // print s | rows
  print_row(n, 4, s);	  // print last - row

  return;
}

void print_row(string n, int row, int s){

  // print all characters for all digits to be displayed
  for(int i = 0; i < n.length(); ++i){

    cout << dformat[n[i] - 48][row][0]; // print leftmost character
    // print scalable middle character
    for(int j = 0; j < s; ++j) cout << dformat[n[i] - 48][row][1];
    cout << dformat[n[i] - 48][row][2]; // print rightmost character

    if (i != (n.length() - 1)) cout << " "; // new digit unless last character
  }

  cout << endl; // start new line
  return;
}
