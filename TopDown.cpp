#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "DataStructure.h"
using namespace std;
int t;

/*
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

*/

Topo * create_Topologica_graph(Node *n){
    Topo *topo;
    topo = new Topo();
    topo->no_of_nodes = t;
    vector<int> r;
    for(int i=0;i<topo->no_of_nodes;i++){
        r.clear();
        for(int j=0;j<topo->no_of_nodes;j++){
            r.push_back(0);
        }
        topo->t.push_back(r);
    }
    Graph *gt;
    for(int i=0;i<t;i++){
        gt = n[i].graph;
        for(int j=0;j<gt->no_of_states;j++){
            for(int k=0;k<gt->no_of_states;k++){
                if(gt->g[j][k][0] == '-' && gt->g[j][k].length() > 1){
                    //cout<<gt->g[j][k]<<endl;
                    for(int m=0;m<t;m++){
                        if(m == i){
                            continue;
                        }
                        int flag = 0;
                        for(int p=0;p<n[m].graph->no_of_states;p++){
                            for(int q=0;q<n[m].graph->no_of_states;q++){
                                if(n[m].graph->g[p][q][0] == '+' && n[m].graph->g[p][q].substr(1,n[m].graph->g[p][q].length()-1) ==  gt->g[j][k].substr(1,gt->g[j][k].length()-1)){
                                    cout<<"match is "<<gt->g[j][k]<<" "<<n[m].graph->g[p][q]<<endl;
                                    topo->t[i][m] = 1;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    return topo;

}

Node * read_Input_Machines(){// read input machines here.
    freopen("input_32mc.txt","r",stdin);
    ///int t;
    string dummy,line;
    getline(cin,line);
    t = stoi(line);// no of graphs
    getline(cin,line);
    Node *n = (Node *) malloc(t*sizeof(Node));
    //read no of states in machines
    for(int i=0;i<t;i++){
        getline(cin,line);

        n[i].no_of_states = stoi(line);
        n[i].graph = (Graph *)malloc(sizeof(Graph));
        n[i].graph->no_of_states = n[i].no_of_states;
    }
    //read machines as graph
    for(int l=0;l<t;l++){
        getline(cin,line);
        getline(cin,line);
        string tok;
        int state_ind = 0;
        stringstream ss(line);
        while(ss>>tok){
            n[l].graph->state_name[state_ind++];
        }

        for(int m=0;m<n[l].no_of_states;m++){
            vector<string> r;
            getline(cin,line);
            stringstream ss(line);
            while(ss>>tok){
                r.push_back(tok);
            }
            n[l].graph->g.push_back(r);
        }

    }

    return n;

}


int main()
{

    /*
    freopen("input_32mc.txt","r",stdin);
    int t;
    string dummy,line;
    getline(cin,line);
    t = stoi(line);// no of graphs
    getline(cin,line);
    Node *n = (Node *) malloc(t*sizeof(Node));
    //read no of states in machines
    for(int i=0;i<t;i++){
        getline(cin,line);

        n[i].no_of_states = stoi(line);
        n[i].graph = (Graph *)malloc(sizeof(Graph));
        n[i].graph->no_of_states = n[i].no_of_states;
    }
    //read machines as graph
    for(int l=0;l<t;l++){
        getline(cin,line);
        getline(cin,line);
        string tok;
        int state_ind = 0;
        stringstream ss(line);
        while(ss>>tok){
            n[l].graph->state_name[state_ind++];
        }

        for(int m=0;m<n[l].no_of_states;m++){
            vector<string> r;
            getline(cin,line);
            stringstream ss(line);
            while(ss>>tok){
                r.push_back(tok);
            }
            n[l].graph->g.push_back(r);
        }

    }
    */

    Node *n = read_Input_Machines();


//Topologhical graph generation **************************************

    /*
    Topo *topo;
    topo = new Topo();
    topo->no_of_nodes = t;
    vector<int> r;
    for(int i=0;i<topo->no_of_nodes;i++){
        r.clear();
        for(int j=0;j<topo->no_of_nodes;j++){
            r.push_back(0);
        }
        topo->t.push_back(r);
    }
    Graph *gt;
    for(int i=0;i<t;i++){
        gt = n[i].graph;
        for(int j=0;j<gt->no_of_states;j++){
            for(int k=0;k<gt->no_of_states;k++){
                if(gt->g[j][k][0] == '-' && gt->g[j][k].length() > 1){
                    //cout<<gt->g[j][k]<<endl;
                    for(int m=0;m<t;m++){
                        if(m == i){
                            continue;
                        }
                        int flag = 0;
                        for(int p=0;p<n[m].graph->no_of_states;p++){
                            for(int q=0;q<n[m].graph->no_of_states;q++){
                                if(n[m].graph->g[p][q][0] == '+' && n[m].graph->g[p][q].substr(1,n[m].graph->g[p][q].length()-1) ==  gt->g[j][k].substr(1,gt->g[j][k].length()-1)){
                                    cout<<"match is "<<gt->g[j][k]<<" "<<n[m].graph->g[p][q]<<endl;
                                    topo->t[i][m] = 1;
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    */
    Topo *topo = create_Topologica_graph(n);
    //print topo graph:
    cout<<"Topological graph is :"<<endl;
    for(int i=0;i<topo->no_of_nodes;i++){
        for(int j=0;j<topo->no_of_nodes;j++){
            cout<<topo->t[i][j]<<"  ";
        }
        cout<<endl;
    }




//Topologhical graph generation end **************************************

// print graph**************************************************
    /*
    for(int i=0;i<t;i++){
        cout<<endl<<"****************************"<<endl;
        cout<<n[i].no_of_states<<endl;
        cout<<n[i].graph->no_of_states<<endl<<endl;
        for(int j=0;j<n[i].no_of_states;j++){
            cout<<endl;
            for(int k=0;k<n[i].no_of_states;k++){
                cout<<n[i].graph->g[j][k]<<" ";
            }
        }


    }
    */
// print graph end **************************************************

    return 0;
}
