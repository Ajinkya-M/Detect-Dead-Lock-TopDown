#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "DataStructure.h"
using namespace std;
int t;//no of machines 

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
    //int t;
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
            n[l].graph->state_name[state_ind++] = tok;
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

void init_globalstate(GlobalState *G, Node *n){
    vector<string> r;
    for(int i=0;i<t;i++){

        G->machine_states.push_back(n[i].graph->state_name[0]);
        G->machine_state_no.push_back(0);
        G->message_queue.push_back("");
        G->machine_iterator.push_back(0);
        cout<<G->machine_states[i]<<endl;
    }
    G->is_next_state_present = 0;
    G->machine_no_to_explore = 0;
}


void print_GlobalState(GlobalState *G){
    cout<<"*****************************************************************************"<<endl;
    for(int i=0;i<t;i++){

        cout<<"state of machine "<<i<<" is "<<G->machine_states[i]<<"  message queue has ["<<G->message_queue[i]<<"]"<<endl;
    }
    cout<<"*****************************************************************************"<<endl;
}

void GlobalState_copy(GlobalState *GT, GlobalState *G){
    for(int i=0;i<t;i++){

        GT->machine_states[i] = G->machine_states[i];
        GT->message_queue[i] = G->message_queue[i];
        GT->is_next_state_present = G->is_next_state_present;
        GT->machine_iterator[i] = G->machine_iterator[i];
        GT->machine_no_to_explore = G->machine_no_to_explore;
        GT->machine_state_no[i] = G->machine_state_no[i];
    }
}

GlobalState * Explore_State(GlobalState *G, Node *n, Topo *topo){//explore global state

    int machine_no = G->machine_no_to_explore;
    if(machine_no >= t){
        return NULL;//there is nothing to explore
    }
    int machine_with_generating_msg = 0;
    cout<<"Exploring machine no "<<machine_no<<endl;
    string msg = "";
    int no_states_in_machine_to_explore = n[machine_no].no_of_states;
    for(int i=0;i<no_states_in_machine_to_explore;i++){

        if(n[machine_no].graph->g[G->machine_state_no[machine_no]][i][0] == '-' && n[machine_no].graph->g[G->machine_state_no[machine_no]][i].length() > 1){
            msg = n[machine_no].graph->g[G->machine_state_no[machine_no]][i];
            n[machine_no].graph->g[G->machine_state_no[machine_no]][i] = "-";
            //cout<<n[machine_no].graph->g[G->machine_state_no[machine_no]][i];
            G->message_queue[machine_no] = msg;
            machine_with_generating_msg = 1;
            G->machine_states[machine_no] = n[machine_no].graph->state_name[i];
            print_GlobalState(G);
            break;

        }
    }
    if(machine_with_generating_msg == 0){
        G->machine_no_to_explore++;
        return Explore_State(G,n,topo);

    }


    //create new global state
    GlobalState *GT = new GlobalState(*G);
    //GlobalState_copy(GT,G);

    //find consuming msg state;
    msg = "+"+msg.substr(1,msg.length());
    int is_msg_matched = 0;
    int target_machine_no = 999;
    for(int i=0;i<t;i++){
        if(topo->t[machine_no][i] == 1){

            target_machine_no = i;
            cout<<"target machine is "<<target_machine_no<<endl;
            break;
        }
    }
    if(target_machine_no == 999) return NULL;
    for(int i=0;i<n[target_machine_no].no_of_states;i++){

        for(int j=0;j<n[target_machine_no].no_of_states;j++){
            if(n[target_machine_no].graph->g[i][j] == msg){
                is_msg_matched = 1;
                G->is_next_state_present = 1;
                GT->machine_states[target_machine_no] = n[target_machine_no].graph->state_name[j];
                GT->machine_state_no[target_machine_no] = j;
                GT->message_queue[machine_no] = "";
                GT->machine_no_to_explore = target_machine_no;
                print_GlobalState(GT);
                break;

            }
        }
        if(is_msg_matched == 1){
            break;
        }
    }
    if(is_msg_matched == 1)
        return GT;
    else return NULL;

}

int main()
{

    Node *n = read_Input_Machines();

    Topo *topo = create_Topologica_graph(n);//topo logiocal graph generattion
    //print topo graph:
    cout<<"Topological graph is :"<<endl;
    for(int i=0;i<topo->no_of_nodes;i++){
        for(int j=0;j<topo->no_of_nodes;j++){
            cout<<topo->t[i][j]<<" ";
        }
        cout<<endl;
    }

    GlobalState *G = new GlobalState();
    init_globalstate(G,n);//initialization of global state.
    print_GlobalState(G);
    stack<GlobalState *> GStack;//stack of global states.
    GStack.push(G);

    //map<GlobalState, bool> GMap;
    //GMap[*G] = true;
    while(!GStack.empty()){

        GlobalState *temp1 = GStack.top();
        GlobalState *temp = Explore_State(temp1,n,topo);
        if(temp){
            //if(GMap.find(*temp) == GMap.end()){
                GStack.push(temp);
                //GMap[*temp] = true;
                continue;

            //}

        }else{
            if(temp1->is_next_state_present == 0){
                cout<<"Deadlock State is found!"<<endl;
                break;

            }
            GStack.pop();

        }
        //GStack.pop();

    }



    return 0;
}



















































