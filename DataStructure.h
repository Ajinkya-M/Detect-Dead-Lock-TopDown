#include<bits/stdc++.h>
using namespace std;

typedef struct Graph{
    int no_of_states;
    string state_name[10];
    vector< vector<string> > g;
}Graph;

typedef struct Node{
    int no_of_states;
    Graph *graph;
}Node;

typedef struct Topo_graph{
  int no_of_nodes;
  vector< vector <int> > t;
}Topo;

class GlobalState{

    public:
    vector<string> machine_states;
	vector<int> machine_state_no;
    vector<string> message_queue;
    vector<int> machine_iterator;
    int is_next_state_present;
	int machine_no_to_explore;

};
