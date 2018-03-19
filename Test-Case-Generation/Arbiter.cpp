#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    string node_name;
    string message;
}node;
//string local = "L";
static int no_of_machines = 0;

//Dynamic node creation:
node* getNode(string name, string message){
    node *n = new node();
    n->node_name = name;
    n->message = message;
    return n;
}

//It takes map and insertion order as Adjacency list input and generates adjc. matrix output
/*
    ________ 
    |   E   |
    |_______|---->[ w0 | N0 | S0 | L0 ]
    |   w0  |
    |_______|
    |   w1  |
    |_______|
    |   w2  |
    |       |
    |_______|
    

*********************************************************************************************
*/
void AdjacencyListTo_GraphGenerator(map<string,vector<node *> > mp, vector<string> &insertOrder){
    
    
    
    ++no_of_machines;
    cout<<insertOrder.size()<<endl;//No. of nodes in machine.
    for(int i=0;i<insertOrder.size();i++){
        cout<<insertOrder[i]<<" ";
    }
    cout<<endl;
    vector< vector <string> > G;
    vector<string> r;
    for(int i=0;i<insertOrder.size();i++){
        r.clear();
        for(int j=0;j<insertOrder.size();j++){
            r.push_back("-");
        }
        G.push_back(r);
    }


    for(int i=0;i<insertOrder.size();i++){
        for(int j=0;j<mp[insertOrder[i]].size();j++){
            for(int k=0;k<insertOrder.size();k++){
                if(mp[insertOrder[i]][j]->node_name == insertOrder[k]){
                    G[i][k] = mp[insertOrder[i]][j]->message;
                }
            }
        }
    }

    
    for(int i=0;i<insertOrder.size();i++){
        for(int j=0;j<insertOrder.size();j++){
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }

}


//for 4 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string fourth, string local, string port){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    //from east:
    //first :
    insertOrder.push_back(first);
    mp[first].push_back(getNode(second+"0","+0L"+port));
    mp[first].push_back(getNode(third+"0","+1L"+port));
    mp[first].push_back(getNode(fourth+"0","+2L"+port));
    mp[first].push_back(getNode(local+"0","+3L"+port));

    //***************************************************************************
    //second:
    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+port));

    //second 0:
    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00L"+port));

    //second 1:
    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+second+port));

    //***************************************************************************
    //third:
    insertOrder.push_back(third);
    mp[third].push_back(getNode(first,"+S"+third+first+port));

    //third 0:
    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-11L"+port));

    //third 1:
    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode(third,"-ret"+first+third+port));

    //***************************************************************************
    //fourth:
    insertOrder.push_back(fourth);
    mp[fourth].push_back(getNode(first,"+S"+fourth+first+port));

    //fourth 0:
    insertOrder.push_back(fourth+"0");
    mp[fourth+"0"].push_back(getNode(fourth+"1","-22L"+port));

    //fourth 1:
    insertOrder.push_back(fourth+"1");
    mp[fourth+"1"].push_back(getNode(fourth,"-ret"+first+fourth+port));

    //***************************************************************************
    //local:
    insertOrder.push_back(local);
    mp[local].push_back(getNode(first,"+S"+local+first+port));

    //fourth 0:
    insertOrder.push_back(local+"0");
    mp[local+"0"].push_back(getNode(local+"1","-33L"+port));

    //fourth 1:
    insertOrder.push_back(local+"1");
    mp[local+"1"].push_back(getNode(local,"-ret"+first+local+port));
    //***************************************************************************

    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

//for 3 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string local, string port){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    //from east:
    //first :
    insertOrder.push_back(first);
    mp[first].push_back(getNode(second+"0","+0L"+port));
    mp[first].push_back(getNode(third+"0","+1L"+port));
    mp[first].push_back(getNode(local+"0","+3L"+port));

    //***************************************************************************
    //second:
    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+port));

    //second 0:
    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00L"+port));

    //second 1:
    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+second+port));

    //***************************************************************************
    //third:
    insertOrder.push_back(third);
    mp[third].push_back(getNode(first,"+S"+third+first+port));

    //third 0:
    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-11L"+port));

    //third 1:
    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode(third,"-ret"+first+third+port));

    //***************************************************************************
    //local:
    insertOrder.push_back(local);
    mp[local].push_back(getNode(first,"+S"+local+first+port));

    //fourth 0:
    insertOrder.push_back(local+"0");
    mp[local+"0"].push_back(getNode(local+"1","-33L"+port));

    //fourth 1:
    insertOrder.push_back(local+"1");
    mp[local+"1"].push_back(getNode(local,"-ret"+first+local+port));
    //***************************************************************************

    AdjacencyListTo_GraphGenerator(mp,insertOrder);

}

//for 2 wire connection router:
void ArbiterBuilder(int no, string first, string second, string local, string port){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    //from east:
    //first :
    insertOrder.push_back(first);
    mp[first].push_back(getNode(second+"0","+0L"+port));
    mp[first].push_back(getNode(local+"0","+3L"+port));

    //***************************************************************************
    //second:
    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+port));

    //second 0:
    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00L"+port));

    //second 1:
    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+second+port));

    //***************************************************************************
    //local:
    insertOrder.push_back(local);
    mp[local].push_back(getNode(first,"+S"+local+first+port));

    //fourth 0:
    insertOrder.push_back(local+"0");
    mp[local+"0"].push_back(getNode(local+"1","-33L"+port));

    //fourth 1:
    insertOrder.push_back(local+"1");
    mp[local+"1"].push_back(getNode(local,"-ret"+first+local+port));
    //***************************************************************************

    AdjacencyListTo_GraphGenerator(mp,insertOrder);
}

//priority machine builder:
void PriorityBuilder(int no, string port){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    for(int i=0;i<no-1;i++){
        insertOrder.push_back(to_string(i));
        mp[to_string(i)].push_back(getNode(to_string(i)+to_string(i), "-"+to_string((i+1)%(no-1))+"L"+port));
        insertOrder.push_back(to_string(i)+to_string(i));
        mp[(to_string(i)+to_string(i))].push_back(getNode(to_string((i+1)%(no-1)),"+"+to_string((i+1)%(no-1))+to_string((i+1)%(no-1))+"L"+port));
    }
    AdjacencyListTo_GraphGenerator(mp,insertOrder);
}


//Arbiter builder utility which calls arbiterbuilder with custom parameters:
void ArbiterBuilderUtility(int no, string wires){
    string temp = wires;
    for(int i=0;i<no;i++){
        string ch = temp.substr(i,1);
        temp.erase(temp.begin() + i);
        ch += temp;
        vector<string> params;
        stringstream ss;
        string charString;
        char char_to_procs;
        for(int k=0;k<ch.length();k++){
            char_to_procs =  ch[k];
            ss.str("");
            ss.clear();
            ss<<char_to_procs;
            ss>>charString;
            params.push_back(charString);
            
        }
        if(no == 3){
            ArbiterBuilder(no,params[0],params[1],params[2],to_string(i));
        }
        else if(no == 4){
            ArbiterBuilder(no,params[0],params[1],params[2],params[3],to_string(i));
        }
        else if(no == 5){
            ArbiterBuilder(no,params[0],params[1],params[2],params[3],params[4],to_string(i));
        }
        PriorityBuilder(no,to_string(i));//priority machine builder called;
        temp = wires;
        params.clear();

    }
}






int main(){
    int m,n;
    cin>>m>>n;
    //freopen("test3_3.txt", "w+", stdout);
    string wires = "";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            wires.clear();

            if(j<n-1){
                wires += "E";
            }
            if(j>=1){
                wires += "W";
            }
            if(i>=1){
                wires += "N";
            }
            if(i<m-1){
                wires += "S";
            }
            wires += "L";
            //cout<<wires<<" ";
            ArbiterBuilderUtility(wires.length(),wires);

        }
        //cout<<endl;
    }
    cout<<no_of_machines;
    fclose(stdout);
    
    

}
