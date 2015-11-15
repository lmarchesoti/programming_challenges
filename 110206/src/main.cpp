#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

/* data structures */
typedef struct auth_s {

	int id;
	string name;
	int n; // erdos number
} AUTHOR;

/* global variables */

/* function prototypes */

/* debug */

int main(){

	int t; // number of test cases
	int p; // number of papers in the current database
	int n; // number of authors to track
	vector<char*> database;
	vector<vector<string>> articles;
	vector<AUTHOR> mathematicians;
	AUTHOR m; // temporary mathematician
	AUTHOR a; // temporary author
	char *name, *sname; // name placeholders

	scanf("%d", &t);

	for(int i = 1; i <= t; ++i){

		// init
		scanf("%d %d", &p, &n);
		//database.resize(p);
		mathematicians.resize(n);

		// read articles as string
		for(int j = 0; j < p; ++j){ gets(name); database.push_back(name); }

		// read author names to track and attribute an id to each
		for(int j = 0; j < n; ++j){

			gets(name);
			//if(!strcmp(name, "Erdos, P.")) m = {j, name, 0};
			//else 
			m = {j, name, -1};
			mathematicians.push_back(m);
		}

		// convert articles to database of name lists
		for(int j = 0; j < p; ++j){

			// read first authors
			while(sscanf(database.back(), "%s,%s,", &name, &sname)){

				articles[j].push_back(string(name) + "," + string(sname));

			}

			// read last author
			sscanf(database.back(), "%s,%s:", &name, &sname);
			articles[j].push_back(string(name) + "," + string(sname));

		}

		// for each mathematician in the ranked list

			// go through the database

				// for each author in a paper that includes the current mathematician

					// attribute to him erdos number = author.n + 1

					// add author to ranked list

				// remove article from the database

	}

  return 0;
}

/* functions */
