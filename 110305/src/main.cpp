#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* data structures */

/* global variables */
int n, m; // buffer size for answers and submissions
vector<string> answers;
vector<string> submissions;

/* function prototypes */
// extracts digits from input into digits variable
void extract_digits(const string, string*);

// returns true if content is exactly equal
bool accepted();

// returns true if numerical content is equal
bool perror();

/* debug */

int main(){

	int t = 0; // test case count
	string line; // buffer string

	istream::sync_with_stdio(false);

	while(cin >> n, cin.ignore(), ++t, n){

			answers.clear(); submissions.clear(); // init

		for(int i = 0; i < n; ++i)
			{ getline(cin, line); answers.push_back(line); }

		cin >> m; cin.ignore();
		for(int i = 0; i < m; ++i)
			{ getline(cin, line); submissions.push_back(line); }

		// compare strings and output result
		cout << "Run #" << t << ": ";
		if(accepted()) cout << "Accepted" << endl;
		else if(perror()) cout << "Presentation Error" << endl;
		else cout << "Wrong Answer" << endl;

	}

  return 0;
}

/* functions */
void extract_digits(const string s, string *digits){

	for(int i = 0; s[i] != '\0'; ++i)
		if(isdigit(s[i])) (*digits) += s[i];

	return;
}

bool accepted(){

	if(n != m) return false;

	for(int i = 0; i < n; ++i) // check correct answers
		if(submissions[i] != answers[i]) return false;

	return true;
}

bool perror(){

	string ansx, subx; // digit-only strings

	for(int i = 0; i < n; ++i) extract_digits(answers[i].c_str(), &ansx);
	for(int i = 0; i < m; ++i) extract_digits(submissions[i].c_str(), &subx);

	return (ansx == subx);
}
