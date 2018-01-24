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
