#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include "DataStructure.h"
using namespace std;
using namespace std::chrono;
int t;//no of machines
int deadlock_cnt;
int algo = 0;//1 = xy and 2 = dynamic
int m,n;//grid pattern
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
                                    //cout<<"match is "<<gt->g[j][k]<<" "<<n[m].graph->g[p][q]<<endl;
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
Node *read_Test_input(){
    //char *file_name = ("test%d_%d.txt",4,4);

    string file;
    char filePath[100];
    cout<<"Enter algo 1: XY || 2: DynaXY  >> ";
    cin>>algo;
    cout<<endl<<"Enter grid m,n : ";
    cin>>m>>n;
    file = (algo == 1 ? "TestMachines/testXY_" : "TestMachines/testDy_") + to_string(m) + "_" + to_string(n) + ".txt";

    //file = "XYTestMachines/testXY_"+to_string(4)+"_"+to_string(4)+".txt";
    cout<<file<<endl;
    for(int i=0;i<file.length();i++){
        filePath[i] = file[i];
    }
    freopen(filePath,"r",stdin);

    //freopen("XYTestMachines/testXY_9_9.txt","r",stdin);
    //freopen("DynamicXYTestMachines/testDy_5_5.txt","r",stdin);

    string line;
    string tok;
    int state_ind = 0;
    vector<string> r;
    getline(cin,line);
    t = stoi(line);// no of graphs
    //cout<<t<<endl;//************ added
    Node *n = (Node *) malloc(t * sizeof(Node));
    for(int i=0;i<t;i++){
        getline(cin,line);
        n[i].no_of_states = stoi(line);// no of graphs
        //cout<<n[i].no_of_states<<endl;//added...
        n[i].graph = (Graph *)malloc(sizeof(Graph));
        n[i].graph->no_of_states = n[i].no_of_states;
        //cout<<n[i].graph->no_of_states<<endl;
        //read machines as graph


        getline(cin,line);
        //cout<<"line is "<<line<<endl;

        state_ind = 0;
        stringstream ss(line);
        while(ss>>tok){
            //cout<<tok<<" ";
            n[i].graph->state_name[state_ind++] = tok;
        }
        //cout<<endl;
        for(int m=0;m<n[i].no_of_states;m++){
            r.clear();
            getline(cin,line);
            stringstream ss(line);
            while(ss>>tok){
                r.push_back(tok);
            }
            n[i].graph->g.push_back(r);
        }



    }
    return n;
}

bool operator <(const GlobalState &r,const GlobalState &l){
    return (l.invalid < r.invalid);
};


void init_globalstate(GlobalState *G, Node *n){
    vector<string> r;
    for(int i=0;i<t;i++){

        G->machine_states.push_back(n[i].graph->state_name[0]);
        G->machine_state_no.push_back(0);
        G->message_queue.push_back("");
        G->machine_iterator.push_back(0);
        //cout<<G->machine_states[i]<<endl;
    }
    G->is_next_state_present = 0;
    G->machine_no_to_explore = 0;
}


void print_GlobalState(GlobalState *G){
    cout<<"*****************************************************************************"<<endl;
    for(int i=0;i<5;i++){//replace 5 with t for print all machines.

        cout<<"state of machine "<<i<<" is "<<G->machine_states[i]<<endl;
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


//explore global state function:
GlobalState * Explore_State(GlobalState *G, Node *n, Topo *topo){//explore global state

    int machine_no = G->machine_no_to_explore;
    int machine_with_generating_msg;
    string msg;
    int no_states_in_machine_to_explore;
    if(machine_no >= t){
        return NULL;//there is nothing to explore
    }
    while(machine_no < t){
        machine_with_generating_msg = 0;
        cout<<"Exploring machine no "<<machine_no<<endl;
        msg = "";
        no_states_in_machine_to_explore = n[machine_no].no_of_states;
        for(int i=0;i<no_states_in_machine_to_explore;i++){

            if(n[machine_no].graph->g[G->machine_state_no[machine_no]][i][0] == '-' && n[machine_no].graph->g[G->machine_state_no[machine_no]][i].length() > 1){
                msg = n[machine_no].graph->g[G->machine_state_no[machine_no]][i];
                n[machine_no].graph->g[G->machine_state_no[machine_no]][i] = "-";
                //cout<<n[machine_no].graph->g[G->machine_state_no[machine_no]][i];
                G->message_queue[machine_no] = msg;
                machine_with_generating_msg = 1;
                G->machine_states[machine_no] = n[machine_no].graph->state_name[i];
                //print_GlobalState(G);
                break;

            }
        }
        if(machine_with_generating_msg == 0){
            G->machine_no_to_explore = (G->machine_no_to_explore + 1);
            if(G->machine_no_to_explore == t){
                G->machine_no_to_explore = 0;
                G->prev_same = 1;
                return NULL;
            }
            machine_no = G->machine_no_to_explore;

        }else{
            //cout<<" generated msg -> "<<msg<<endl;
            break;
        }
    }

    if(machine_no>=t){
        return NULL;
    }
    //create new global state
    GlobalState *GT = new GlobalState(*G);
    //find consuming msg state;
    msg = "+"+msg.substr(1,msg.length());
    int is_msg_matched = 0;
    int target_machine_no = 999;
    for(int i=0;i<t;i++){
        if(topo->t[machine_no][i] == 1){

            target_machine_no = i;
            //cout<<"target machine is "<<target_machine_no<<endl;
            break;
        }
    }
    for(target_machine_no = 0;target_machine_no<t;target_machine_no++){
        for(int i=0;i<n[target_machine_no].no_of_states;i++){

            for(int j=0;j<n[target_machine_no].no_of_states;j++){
                if(n[target_machine_no].graph->g[i][j] == msg){
                    is_msg_matched = 1;
                    G->is_next_state_present = 1;
                    GT->machine_states[target_machine_no] = n[target_machine_no].graph->state_name[j];
                    GT->machine_state_no[target_machine_no] = j;
                    GT->message_queue[machine_no] = "";
                    GT->machine_no_to_explore = target_machine_no;
                    //n[target_machine_no].graph->g[i][j] = "-";
                    //cout<<"mathced with "<<msg<<endl;
                    //print_GlobalState(GT);
                    break;

                }
            }
            if(is_msg_matched == 1){
                break;
            }
        }
        if(is_msg_matched){
            break;
        }
    }

    if(is_msg_matched == 1){
        cout<<"Newly formed global state is returned..."<<endl;
        return GT;
    }
    else{
        G->prev_same = 1;
        G->deadlock = 1;
        return G;
    }

}

//explore global state function:
GlobalState * Explore_GlobalState(GlobalState *G, Node *n, Topo *topo){

  int is_msg_generated = 0;
  int whilecnt = 0;
  int machine_no;
  int curr_machine_state;
  int no_of_states_in_curr_machine;
  string msg;
  while(1){
    whilecnt++;
    machine_no = G->machine_no_to_explore;
    curr_machine_state = G->machine_state_no[machine_no];
    //get -ve message:
    is_msg_generated = 0;
    msg = "";
    no_of_states_in_curr_machine = n[machine_no].no_of_states;
    for(int i=0;i<no_of_states_in_curr_machine;i++){
      if(n[machine_no].graph->g[curr_machine_state][i][0] == '-' && n[machine_no].graph->g[curr_machine_state][i].length() > 1){
        msg = n[machine_no].graph->g[curr_machine_state][i];
        //n[machine_no].graph->g[curr_machine_state][i] = "-";//msg updated;**************************
        cout<<"msg is "<<msg<<endl;
        G->message_queue[machine_no] = msg;
        G->machine_states[machine_no] = n[machine_no].graph->state_name[i];
        G->machine_state_no[machine_no] = i;
        is_msg_generated = 1;
        cout<<msg<<" is generated by m/c no "<<machine_no<<endl;
        break;
      }
    }
    if(is_msg_generated || whilecnt >= t-1){
      break;
    }
    else{
      G->machine_no_to_explore = (G->machine_no_to_explore+1) % t;
    }
  }
  int is_msg_found = 0;
  if(is_msg_generated){
    //find match for gemerated message:
    msg = "+"+msg.substr(1,msg.length());
    for(int i=0;i<t;i++){
      int j = G->machine_state_no[i];
      for(int k = 0;k<n[i].no_of_states;k++){
        if(n[i].graph->g[j][k] == msg){
          //msg matched:
          //n[i].graph->g[j][k] = "-";//msg updated;*******************************
          is_msg_found = 1;
          G->is_next_state_present = 1;
          G->machine_no_to_explore = i;
          G->message_queue[machine_no] = "";
          GlobalState *GT = new GlobalState(*G);
          GT->is_next_state_present = 0;
          GT->machine_state_no[i] = k;
          GT->machine_states[i] = n[i].graph->state_name[k];
          cout<<msg<<" is consumed by m/c no "<<i<<endl;
          return GT;
        }
      }
    }
    return G;
  }else{
    return NULL;
  }

}

int max(int a,int b){
  return a>=b?a:b;
}

static int cnt = 0;
int main()
{
    //Node *n = read_Input_Machines();
    auto start = high_resolution_clock::now();

    Node *n = read_Test_input();
    freopen("output.txt","w",stdout);
    Topo *topo = create_Topologica_graph(n);//topo logiocal graph generattion
    GlobalState *G = new GlobalState();
    init_globalstate(G,n);//initialization of global state.
    int deadlock_Cnt = 0;
    int maxStack_size = 0;
    int whilecnt = 0;
    int bound  = 10;
    bound = static_cast<int>(algo == 1 ? m + 2 : m * 1.7 + 3);
    //print_GlobalState(G);
    stack<GlobalState *> GStack;//stack of global states.
    //map<GlobalState, bool> mp;
    GStack.push(G);
    //mp[*G] = true;

    while(!GStack.empty()){
      whilecnt++;
      cout<<"size of stack is "<<GStack.size()<<endl;
      maxStack_size = max(maxStack_size,GStack.size());
      GlobalState *temp = GStack.top();
      GlobalState *temp1 = Explore_GlobalState(temp,n,topo);
      if(temp1){
        //if(mp.find(*temp1) != mp.end()){
          cout<<"pushed onto stack"<<endl;
          GStack.push(temp1);
        //  mp[*temp1] = true;
        //}
      }else{
        if(temp->is_next_state_present == 0){
          cout<<"deadlock is found"<<endl;
          deadlock_cnt++;
          //break;
        }
        GStack.pop();

      }
      if(whilecnt>1<<bound){
          break;
      }



    }
    cout<<endl;
    cout<<"*********** Results *******************************"<<endl;
    cout<<"total deadlocks : "<<deadlock_cnt<<endl;
    cout<<"Max stack size is : "<<maxStack_size<<endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function : "<< duration.count()/1000 << " mseconds" << endl;
    cout<<"****************************************************"<<endl;
    return 0;
}
