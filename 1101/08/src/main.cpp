#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define NAME_LENGTH 80
#define MAX_CANDIDATES 21

using namespace std;

/* structures */
typedef struct v {
  queue<int> votes; // a list of his votes in order
} VOTER;

typedef struct c {
  char name[NAME_LENGTH];
  vector<struct v> voters;
  bool valid;
} CANDIDATE;

/* end structures */

// global variables
int total_candidates;
int total_voters;
CANDIDATE candidates[MAX_CANDIDATES];
vector<VOTER> unassigned;
vector<CANDIDATE*> c_ref;

/* function prototypes */

// returns true if the first candidate has more votes than the second
bool compare_candidates(CANDIDATE*, CANDIDATE*);

// reads candidates into the candidates vector
// and initializes their respective references in c_ref
void read_candidates();

// reads all voters into the unassigned vector
void read_votes();

// assigns votes to candidates in order or preference
// and sorts the candidates vector according to their total votes
void assign_votes();

// eliminates all tied candidates with the least votes
void eliminate();

// returns true if there is a winner or set of, false otherwise
bool finished_voting();

// debug
template class std::queue<CANDIDATE*>;
template class std::vector<CANDIDATE>;
template class std::vector<CANDIDATE*>;
template class std::vector<VOTER>;

/* end function prototypes */
int main(){

  int test_cases;
  int highest_score; // temporary highest score to print winners
  bool first = true; // flag to check if first case to print newline
  
  cin >> test_cases;
  for(int t = 0; t < test_cases; ++t){

    if(first) first = false;
    else cout << endl;

    cin >> total_candidates; cin.get(); // trim empty newline
    read_candidates();
    read_votes();
    for(assign_votes(); !finished_voting(); assign_votes())
      eliminate();

    // print winners(every valid candidate with votes equal to the highest)
    highest_score = (*c_ref.front()).voters.size();
    for(int i = 0; i < total_candidates; ++i)
      if(candidates[i].valid && (candidates[i].voters.size() == highest_score))
	cout << candidates[i].name << endl;

    // clear up for next round
    unassigned.clear();
    for(int i = 0; i < total_candidates; ++i) candidates[i].voters.clear();
    c_ref.clear();

  }

  return 0;
}

bool compare_candidates(CANDIDATE *first, CANDIDATE *second){

  return (*first).voters.size() > (*second).voters.size();
}

void read_candidates(){

  for(int i = 0; i < total_candidates; ++i){

    cin.getline(candidates[i].name, NAME_LENGTH);
    candidates[i].valid = true;
    c_ref.push_back(&(candidates[i]));
  }

  return;
}

void read_votes(){

  int vote;
  VOTER temp;

  // read each vote of each voter at a time
  while((cin.peek() != '\n') && !cin.eof()){ // while there are still voters

    for(int i = 0; i < total_candidates; ++i){

      cin >> vote; // 1-based
      temp.votes.push(--vote); // candidates is 0-based
    }

    unassigned.push_back(temp); // put the new voter in unassigned limbo
    cin.get(); // trim newline at end of vote
    //temp.votes.clear();
    while(temp.votes.size() > 0) temp.votes.pop();
  }

  total_voters = unassigned.size();

  return;
}

// send every voter in unassigned to their next valid candidates
void assign_votes(){

  int next_valid; // index of next valid candidate of a given voter

  for(VOTER v; unassigned.size() > 0; unassigned.pop_back()){

    v = unassigned.back();

    // find next valid candidate for v
    next_valid = v.votes.front();
    v.votes.pop();

    while(candidates[next_valid].valid == false){

      next_valid = v.votes.front();
      v.votes.pop();
    }

    // send this vote to the new candidate
    candidates[next_valid].voters.push_back(v);

  }

  // sort candidates in order of voters supporting them
  sort(c_ref.begin(), c_ref.end(), compare_candidates);

  return;
}

void eliminate(){

  int lowest_score = (*c_ref.back()).voters.size();

  // eliminate everyone from the back of valid candidates until theres a higher score
  for(CANDIDATE* last_valid = c_ref.back();
    (last_valid != c_ref.front()) && ((*last_valid).voters.size() == lowest_score);
    c_ref.pop_back(), last_valid = c_ref.back()){

    (*c_ref.back()).valid = false;

    // transfer all voters of this guy to the unassigned limbo
    while((*last_valid).voters.size() > 0){

      unassigned.push_back((*last_valid).voters.back());
      (*last_valid).voters.pop_back();
    }
  }

  return;
}

bool finished_voting(){

  // finish if either a candidate has > 50% votes or every valid candidate is tied
  if(((*c_ref.front()).voters.size() > (total_voters/2)) ||
     ((*c_ref.front()).voters.size() == (*c_ref.back()).voters.size()))
    return true;

  return false;
}
