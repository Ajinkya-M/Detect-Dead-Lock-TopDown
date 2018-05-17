//
// Created by ajinkya on 15/5/18.
//
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

//*****************************************************************************************************
//buffer generator genaric:
void Buffer(int no, string first, int router,int n){
    map<string, vector< node *> > mp;
    vector<string> insertOrder;
    if(first == "L"){
        insertOrder.push_back("0");
        mp["0"].push_back(getNode("1","-BT"+first+to_string(router)));

        insertOrder.push_back("1");
        mp["1"].push_back(getNode("0","+ret"+first+to_string(router)));

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
        return;
    }else{
        insertOrder.push_back("0");
        mp["0"].push_back(getNode("00","-B"+first+to_string(router)));

        int adjRouter;
        string adjPort;
        if(first == "E"){
            adjRouter = router + 1;
            adjPort = "W";
        }
        if(first == "W"){
            adjRouter = router - 1;
            adjPort = "E";
        }
        if(first == "N"){
            adjRouter = router - n;
            adjPort = "S";
        }
        if(first == "S"){
            adjRouter = router + n;
            adjPort = "N";
        }


        insertOrder.push_back("00");
        mp["00"].push_back(getNode("1","+A"+adjPort+to_string(adjRouter)));

        insertOrder.push_back("1");
        mp["1"].push_back(getNode("SW"+to_string(router),"-BT"+first+to_string(router)));

        insertOrder.push_back("SW"+to_string(router));
        mp["SW"+to_string(router)].push_back(getNode("0","+ret"+first+to_string(router)));

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
        return;
    }

}
//*********************************************************************************************





//for 4 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string fourth, string fifth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    int adjRouter;

    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+routerNo));

    insertOrder.push_back(third);
    mp[third].push_back(getNode(first,"+S"+third+first+routerNo));

    insertOrder.push_back(fourth);
    mp[fourth].push_back(getNode(first,"+S"+fourth+first+routerNo));

    insertOrder.push_back(fifth);
    mp[fifth].push_back(getNode(first,"+S"+fifth+first+routerNo));

    if(first == "L"){
        insertOrder.push_back(first);
        mp[first].push_back(getNode(second+"0","+0"+first+routerNo));
        mp[first].push_back(getNode(third+"0","+1"+first+routerNo));
        mp[first].push_back(getNode(fourth+"0","+2"+first+routerNo));
        mp[first].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }else{

        if(first == "E"){
            adjPort = "W";
            adjRouter = router + 1;
        }
        if(first == "W"){
            adjPort = "E";
            adjRouter = router - 1;
        }
        if(first == "N"){
            adjPort = "S";
            adjRouter = router - n;
        }
        if(first == "S"){
            adjPort = "N";
            adjRouter = router + n;
        }
        insertOrder.push_back(first);
        mp[first].push_back(getNode("Tr","+B"+adjPort+to_string(adjRouter)));


        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("ret","-A"+first+routerNo));

        insertOrder.push_back("ret");
        mp["ret"].push_back(getNode(second+"0","+0"+first+routerNo));
        mp["ret"].push_back(getNode(third+"0","+1"+first+routerNo));
        mp["ret"].push_back(getNode(fourth+"0","+2"+first+routerNo));
        mp["ret"].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }

    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00"+first+routerNo));
    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-11"+first+routerNo));
    insertOrder.push_back(fourth+"0");
    mp[fourth+"0"].push_back(getNode(fourth+"1","-22"+first+routerNo));
    insertOrder.push_back(fifth+"0");
    mp[fifth+"0"].push_back(getNode(fifth+"1","-33"+first+routerNo));

    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+fifth+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode(third,"-ret"+first+second+routerNo));

    insertOrder.push_back(fourth+"1");
    mp[fourth+"1"].push_back(getNode(fourth,"-ret"+first+third+routerNo));

    insertOrder.push_back(fifth+"1");
    mp[fifth+"1"].push_back(getNode(fifth,"-ret"+first+fourth+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

//for 3 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string fourth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    int adjRouter;

    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+routerNo));

    insertOrder.push_back(third);
    mp[third].push_back(getNode(first,"+S"+third+first+routerNo));

    insertOrder.push_back(fourth);
    mp[fourth].push_back(getNode(first,"+S"+fourth+first+routerNo));

    //insertOrder.push_back(fifth);
    //mp[fifth].push_back(getNode(first,"+S"+fifth+first+routerNo));

    if(first == "L"){
        insertOrder.push_back(first);
        mp[first].push_back(getNode(second+"0","+0"+first+routerNo));
        mp[first].push_back(getNode(third+"0","+1"+first+routerNo));
        mp[first].push_back(getNode(fourth+"0","+2"+first+routerNo));
        //mp[first].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }else{

        if(first == "E"){
            adjPort = "W";
            adjRouter = router + 1;
        }
        if(first == "W"){
            adjPort = "E";
            adjRouter = router - 1;
        }
        if(first == "N"){
            adjPort = "S";
            adjRouter = router - n;
        }
        if(first == "S"){
            adjPort = "N";
            adjRouter = router + n;
        }
        insertOrder.push_back(first);
        mp[first].push_back(getNode("Tr","+B"+adjPort+to_string(adjRouter)));


        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("ret","-A"+first+routerNo));

        insertOrder.push_back("ret");
        mp["ret"].push_back(getNode(second+"0","+0"+first+routerNo));
        mp["ret"].push_back(getNode(third+"0","+1"+first+routerNo));
        mp["ret"].push_back(getNode(fourth+"0","+2"+first+routerNo));
        //mp["ret"].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }

    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00"+first+routerNo));
    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-11"+first+routerNo));
    insertOrder.push_back(fourth+"0");
    mp[fourth+"0"].push_back(getNode(fourth+"1","-22"+first+routerNo));
    //insertOrder.push_back(fifth+"0");
    //mp[fifth+"0"].push_back(getNode(fifth+"1","-33"+first+routerNo));

    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+fourth+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode(third,"-ret"+first+second+routerNo));

    insertOrder.push_back(fourth+"1");
    mp[fourth+"1"].push_back(getNode(fourth,"-ret"+first+third+routerNo));

    //insertOrder.push_back(fifth+"1");
    //mp[fifth+"1"].push_back(getNode(fifth,"-ret"+first+fourth+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);

}

//for 2 wire connection router:
void ArbiterBuilder(int no, string first, string second, string third, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    int adjRouter;

    insertOrder.push_back(second);
    mp[second].push_back(getNode(first,"+S"+second+first+routerNo));

    insertOrder.push_back(third);
    mp[third].push_back(getNode(first,"+S"+third+first+routerNo));

    //insertOrder.push_back(fourth);
    //mp[fourth].push_back(getNode(first,"+S"+fourth+first+routerNo));

    //insertOrder.push_back(fifth);
    //mp[fifth].push_back(getNode(first,"+S"+fifth+first+routerNo));

    if(first == "L"){
        insertOrder.push_back(first);
        mp[first].push_back(getNode(second+"0","+0"+first+routerNo));
        mp[first].push_back(getNode(third+"0","+1"+first+routerNo));
        //mp[first].push_back(getNode(fourth+"0","+2"+first+routerNo));
        //mp[first].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }else{

        if(first == "E"){
            adjPort = "W";
            adjRouter = router + 1;
        }
        if(first == "W"){
            adjPort = "E";
            adjRouter = router - 1;
        }
        if(first == "N"){
            adjPort = "S";
            adjRouter = router - n;
        }
        if(first == "S"){
            adjPort = "N";
            adjRouter = router + n;
        }
        insertOrder.push_back(first);
        mp[first].push_back(getNode("Tr","+B"+adjPort+to_string(adjRouter)));


        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("ret","-A"+first+routerNo));

        insertOrder.push_back("ret");
        mp["ret"].push_back(getNode(second+"0","+0"+first+routerNo));
        mp["ret"].push_back(getNode(third+"0","+1"+first+routerNo));
        //mp["ret"].push_back(getNode(fourth+"0","+2"+first+routerNo));
        //mp["ret"].push_back(getNode(fifth+"0","+3"+first+routerNo));
    }

    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-00"+first+routerNo));
    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-11"+first+routerNo));
    //insertOrder.push_back(fourth+"0");
    //mp[fourth+"0"].push_back(getNode(fourth+"1","-22"+first+routerNo));
    //insertOrder.push_back(fifth+"0");
    //mp[fifth+"0"].push_back(getNode(fifth+"1","-33"+first+routerNo));

    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode(second,"-ret"+first+third+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode(third,"-ret"+first+second+routerNo));

    //insertOrder.push_back(fourth+"1");
    //mp[fourth+"1"].push_back(getNode(fourth,"-ret"+first+third+routerNo));

    //insertOrder.push_back(fifth+"1");
    //mp[fifth+"1"].push_back(getNode(fifth,"-ret"+first+fourth+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);
}

//priority machine builder:
void PriorityBuilder(int no, string first, int router){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    for(int i=0;i<no-1;i++){
        insertOrder.push_back(to_string(i));
        mp[to_string(i)].push_back(getNode(to_string(i)+to_string(i), "-"+to_string((i+1)%(no-1))+first+routerNo));
        insertOrder.push_back(to_string(i)+to_string(i));
        mp[(to_string(i)+to_string(i))].push_back(getNode(to_string((i+1)%(no-1)),"+"+to_string((i+1)%(no-1))+to_string((i+1)%(no-1))+first+routerNo));
    }
    AdjacencyListTo_GraphGenerator(mp,insertOrder);
}


//*********************************************************************


//************ Switch Generation **************************************
//for 4 wire connectin router:
void SwitchBuilder(int no, string first, string second, string third, string fourth, string fifth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    insertOrder.push_back("wt");
    mp["wt"].push_back(getNode("st","+BT"+first+routerNo));

    insertOrder.push_back("st");
    mp["st"].push_back(getNode("Comp","-Comp"+first+routerNo));

    insertOrder.push_back("Comp");
    mp["Comp"].push_back(getNode(second+"0","+C"+second+first+routerNo));
    mp["Comp"].push_back(getNode(third+"0","+C"+third+first+routerNo));
    mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+routerNo));
    mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+routerNo));


    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-S"+first+second+routerNo));

    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-S"+first+third+routerNo));

    insertOrder.push_back(fourth+"0");
    mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+fourth+routerNo));

    insertOrder.push_back(fifth+"0");
    mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+fifth+routerNo));


    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode("rets","+ret"+second+first+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode("rets","+ret"+third+first+routerNo));

    insertOrder.push_back(fourth+"1");
    mp[fourth+"1"].push_back(getNode("rets","+ret"+fourth+first+routerNo));

    insertOrder.push_back(fifth+"1");
    mp[fifth+"1"].push_back(getNode("rets","+ret"+fifth+first+routerNo));

    insertOrder.push_back("rets");
    mp["rets"].push_back(getNode("retb","-ret"+first+routerNo));

    insertOrder.push_back("retb");
    mp["retb"].push_back(getNode("wt","-retComp"+first+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

//for 3 wire connectin router:
void SwitchBuilder(int no, string first, string second, string third, string fourth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    insertOrder.push_back("wt");
    mp["wt"].push_back(getNode("st","+BT"+first+routerNo));

    insertOrder.push_back("st");
    mp["st"].push_back(getNode("Comp","-Comp"+first+routerNo));

    insertOrder.push_back("Comp");
    mp["Comp"].push_back(getNode(second+"0","+C"+second+first+routerNo));
    mp["Comp"].push_back(getNode(third+"0","+C"+third+first+routerNo));
    mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+routerNo));
    //mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+routerNo));


    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-S"+first+second+routerNo));

    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-S"+first+third+routerNo));

    insertOrder.push_back(fourth+"0");
    mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+fourth+routerNo));

    //insertOrder.push_back(fifth+"0");
    //mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+fifth+routerNo));


    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode("rets","+ret"+second+first+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode("rets","+ret"+third+first+routerNo));

    insertOrder.push_back(fourth+"1");
    mp[fourth+"1"].push_back(getNode("rets","+ret"+fourth+first+routerNo));

    //insertOrder.push_back(fifth+"1");
    //mp[fifth+"1"].push_back(getNode("rets","+ret"+fifth+first+routerNo));

    insertOrder.push_back("rets");
    mp["rets"].push_back(getNode("retb","-ret"+first+routerNo));

    insertOrder.push_back("retb");
    mp["retb"].push_back(getNode("wt","-retComp"+first+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

//for 2 wire connection router:
void SwitchBuilder(int no, string first, string second, string third, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    insertOrder.push_back("wt");
    mp["wt"].push_back(getNode("st","+BT"+first+routerNo));

    insertOrder.push_back("st");
    mp["st"].push_back(getNode("Comp","-Comp"+first+routerNo));

    insertOrder.push_back("Comp");
    mp["Comp"].push_back(getNode(second+"0","+C"+second+first+routerNo));
    mp["Comp"].push_back(getNode(third+"0","+C"+third+first+routerNo));
    //mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+routerNo));
    //mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+routerNo));


    insertOrder.push_back(second+"0");
    mp[second+"0"].push_back(getNode(second+"1","-S"+first+second+routerNo));

    insertOrder.push_back(third+"0");
    mp[third+"0"].push_back(getNode(third+"1","-S"+first+third+routerNo));

    //insertOrder.push_back(fourth+"0");
    //mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+fourth+routerNo));

    //insertOrder.push_back(fifth+"0");
    //mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+fifth+routerNo));


    insertOrder.push_back(second+"1");
    mp[second+"1"].push_back(getNode("rets","+ret"+second+first+routerNo));

    insertOrder.push_back(third+"1");
    mp[third+"1"].push_back(getNode("rets","+ret"+third+first+routerNo));

    //insertOrder.push_back(fourth+"1");
    //mp[fourth+"1"].push_back(getNode("rets","+ret"+fourth+first+routerNo));

    //insertOrder.push_back(fifth+"1");
    //mp[fifth+"1"].push_back(getNode("rets","+ret"+fifth+first+routerNo));

    insertOrder.push_back("rets");
    mp["rets"].push_back(getNode("retb","-ret"+first+routerNo));

    insertOrder.push_back("retb");
    mp["retb"].push_back(getNode("wt","-retComp"+first+routerNo));



    AdjacencyListTo_GraphGenerator(mp,insertOrder);

}

//************************* Compute Machine *************************************
void Compute(int no, string first, string second, string third, string fourth, string fifth, int router){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    if(first != "N" && first != "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));
        mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));
        mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));
        mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

        insertOrder.push_back(second);
        mp[second].push_back(getNode("st","+retComp"+first+routerNo));

        insertOrder.push_back(third);
        mp[third].push_back(getNode( "st","+retComp"+first+routerNo));

        insertOrder.push_back(fourth);
        mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));

        insertOrder.push_back(fifth);
        mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
    }else if(first == "N"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "S" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "S" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fourth == "S" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fifth == "S" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }
    }else if(first == "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "N" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "N" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fourth == "N" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fifth == "N" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }

    }


    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

void Compute(int no, string first, string second, string third, string fourth, int router){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    if(first != "N" && first != "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));
        mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));
        mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));
        //mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

        insertOrder.push_back(second);
        mp[second].push_back(getNode("st","+retComp"+first+routerNo));

        insertOrder.push_back(third);
        mp[third].push_back(getNode( "st","+retComp"+first+routerNo));

        insertOrder.push_back(fourth);
        mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));

        //insertOrder.push_back(fifth);
        //mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
    }else if(first == "N"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "S" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "S" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fourth == "S" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        /*
        if(fifth == "S" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        */
    }else if(first == "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "N" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "N" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fourth == "N" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        /*
        if(fifth == "N" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        */
    }


    AdjacencyListTo_GraphGenerator(mp,insertOrder);

}

void Compute(int no, string first, string second, string third, int router){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);

    if(first != "N" && first != "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));
        mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));
        //mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));
        //mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

        insertOrder.push_back(second);
        mp[second].push_back(getNode("st","+retComp"+first+routerNo));

        insertOrder.push_back(third);
        mp[third].push_back(getNode( "st","+retComp"+first+routerNo));

        //insertOrder.push_back(fourth);
        //mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));

        //insertOrder.push_back(fifth);
        //mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
    }else if(first == "N"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "S" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "S" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }
        /*
        if(fourth == "S" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fifth == "S" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        */
    }else if(first == "S"){
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+routerNo));

        insertOrder.push_back("Comp");
        if(second == "N" || second == "L"){
            mp["Comp"].push_back(getNode(second,"-C"+second+first+routerNo));

            insertOrder.push_back(second);
            mp[second].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(third == "N" || third == "L"){
            mp["Comp"].push_back(getNode(third,"-C"+third+first+routerNo));

            insertOrder.push_back(third);
            mp[third].push_back(getNode("st","+retComp"+first+routerNo));
        }
        /*
        if(fourth == "N" || fourth == "L"){
            mp["Comp"].push_back(getNode(fourth,"-C"+fourth+first+routerNo));

            insertOrder.push_back(fourth);
            mp[fourth].push_back(getNode("st","+retComp"+first+routerNo));
        }

        if(fifth == "N" || fifth == "L"){
            mp["Comp"].push_back(getNode(fifth,"-C"+fifth+first+routerNo));

            insertOrder.push_back(fifth);
            mp[fifth].push_back(getNode("st","+retComp"+first+routerNo));
        }
        */
    }


    AdjacencyListTo_GraphGenerator(mp,insertOrder);


}

//********************************************************************


//********************************************************************



//Arbiter builder utility which calls arbiterbuilder with custom parameters:
void ArbiterBuilderUtility(int no, string wires, int router,int n){
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
            Buffer(no,params[0],router,n);
            SwitchBuilder(no,params[0],params[1],params[2],router,n);//switch generator called
            Compute(no,params[0],params[1],params[2],router);//compute m/c generator called
            ArbiterBuilder(no,params[0],params[1],params[2],router,n);//Arbiter generator called
            PriorityBuilder(no,params[0],router);//priority machine builder called;

        }
        else if(no == 4){
            Buffer(no,params[0],router,n);
            SwitchBuilder(no,params[0],params[1],params[2],params[3],router,n);//switch generator called
            Compute(no,params[0],params[1],params[2],params[3],router);//compute m/c generator called
            ArbiterBuilder(no,params[0],params[1],params[2],params[3],router, n);//Arbiter generator called
            PriorityBuilder(no,params[0],router);//priority machine builder called;

        }
        else if(no == 5){
            Buffer(no,params[0],router,n);
            SwitchBuilder(no,params[0],params[1],params[2],params[3],params[4],router,n);//switch generator called
            Compute(no,params[0],params[1],params[2],params[3],params[4],router);//compute m/c generator called
            ArbiterBuilder(no,params[0],params[1],params[2],params[3],params[4],router,n);//Arbiter generator called
            PriorityBuilder(no,params[0],router);//priority machine builder called;

        }
        temp = wires;
        params.clear();

    }
}






int main(){
    int m,n;
    cout<<"Enter dimensions of mesh >> m n : ";
    cin>>m>>n;
    freopen("XYTestMachines/testXY_10_10.txt", "w+", stdout);
    string wires = "";
    int router = 0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            router++;
            wires.clear();
            wires += "L";
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
            //cout<<wires<<" ";
            ArbiterBuilderUtility(wires.length(),wires,router,n);

        }
        //cout<<endl;
    }
    cout<<no_of_machines;
    fclose(stdout);



}
