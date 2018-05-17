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
    string routerNo = to_string(router);
    if(first == "L"){
        insertOrder.push_back("0");
        mp["0"].push_back(getNode("00","-BT"+first+routerNo));

        insertOrder.push_back("00");
        mp["00"].push_back(getNode("0","+ret"+first+routerNo));

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
        return;
    }
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";

    }

    insertOrder.push_back("0");
    mp["0"].push_back(getNode("00","-B"+first+turn1+routerNo));

    insertOrder.push_back("00");
    mp["00"].push_back(getNode("1","+A"+adjRouter+turn1+nextRouter));

    insertOrder.push_back("1");
    mp["1"].push_back(getNode(adjRouter+first+turn1+routerNo,"-BT"+first+turn1+routerNo));

    insertOrder.push_back(adjRouter+first+turn1+routerNo);
    mp[adjRouter+first+turn1+routerNo].push_back(getNode("0","-ret"+first+turn1+routerNo));

    AdjacencyListTo_GraphGenerator(mp,insertOrder);


    mp.clear();
    insertOrder.clear();
    insertOrder.push_back("0");
    mp["0"].push_back(getNode("00","-B"+first+turn2+routerNo));

    insertOrder.push_back("00");
    mp["00"].push_back(getNode("1","+A"+adjRouter+turn2+nextRouter));

    insertOrder.push_back("1");
    mp["1"].push_back(getNode(adjRouter+first+turn2+routerNo,"-BT"+first+turn2+routerNo));

    insertOrder.push_back(adjRouter+first+turn2+routerNo);
    mp[adjRouter+first+turn2+routerNo].push_back(getNode("0","-ret"+first+turn2+routerNo));

    AdjacencyListTo_GraphGenerator(mp,insertOrder);


    mp.clear();
    insertOrder.clear();

    insertOrder.push_back("0");
    mp["0"].push_back(getNode("00","-B"+first+turn3+routerNo));

    insertOrder.push_back("00");
    mp["00"].push_back(getNode("1","+A"+adjRouter+turn3+nextRouter));

    insertOrder.push_back("1");
    mp["1"].push_back(getNode(adjRouter+first+turn3+routerNo,"-BT"+first+turn3+routerNo));

    insertOrder.push_back(adjRouter+first+turn3+routerNo);
    mp[adjRouter+first+turn3+routerNo].push_back(getNode("0","-ret"+first+turn3+routerNo));

    AdjacencyListTo_GraphGenerator(mp,insertOrder);



}
//*********************************************************************************************





//for 4 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string fourth, string fifth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string eturn1 = "se";
    string eturn2 = "e";
    string eturn3 = "ne";
    string wturn1 = "sw";
    string wturn2 = "w";
    string wturn3 = "nw";
    string nturn1 = "en";
    string nturn2 = "n";
    string nturn3 = "wn";
    string sturn1 = "es";
    string sturn2 = "s";
    string sturn3 = "ws";



    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "E";

    }
    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "W";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "N";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "S";

    }

    if(first == "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("L");

        insertOrder.push_back(second+eturn1);
        mp[second+eturn1].push_back(getNode("L","+S"+second+eturn1+"L"));
        mp["L"].push_back(getNode(second+eturn1+"0","+0"+first+routerNo));
        insertOrder.push_back(second+eturn1+"0");
        mp[second+eturn1+"0"].push_back(getNode(second+eturn1+"1", "-00"+first+routerNo));
        insertOrder.push_back(second+eturn1+"1");
        mp[second+eturn1+"1"].push_back(getNode(second+eturn1, "-ret"+fifth+sturn3));

        insertOrder.push_back(second+eturn2);
        mp[second+eturn2].push_back(getNode("L","+S"+second+eturn2+"L"));
        mp["L"].push_back(getNode(second+eturn2+"0","+1"+first+routerNo));
        insertOrder.push_back(second+eturn2+"0");
        mp[second+eturn2+"0"].push_back(getNode(second+eturn2+"1", "-11"+first+routerNo));
        insertOrder.push_back(second+eturn2+"1");
        mp[second+eturn2+"1"].push_back(getNode(second+eturn2, "-ret"+second+eturn1));

        insertOrder.push_back(second+eturn3);
        mp[second+eturn3].push_back(getNode("L","+S"+second+eturn3+"L"));
        mp["L"].push_back(getNode(second+eturn3+"0","+2"+first+routerNo));
        insertOrder.push_back(second+eturn3+"0");
        mp[second+eturn3+"0"].push_back(getNode(second+eturn3+"1", "-22"+first+routerNo));
        insertOrder.push_back(second+eturn3+"1");
        mp[second+eturn3+"1"].push_back(getNode(second+eturn3, "-ret"+second+eturn2));

        insertOrder.push_back(third+wturn1);
        mp[third+wturn1].push_back(getNode("L","+S"+third+wturn1+"L"));
        mp["L"].push_back(getNode(third+wturn1+"0","+3"+first+routerNo));
        insertOrder.push_back(third+wturn1+"0");
        mp[third+wturn1+"0"].push_back(getNode(third+wturn1+"1", "-33"+first+routerNo));
        insertOrder.push_back(third+wturn1+"1");
        mp[third+wturn1+"1"].push_back(getNode(third+wturn1, "-ret"+second+eturn3));

        insertOrder.push_back(third+wturn2);
        mp[third+wturn2].push_back(getNode("L","+S"+third+wturn2+"L"));
        mp["L"].push_back(getNode(third+wturn2+"0","+4"+first+routerNo));
        insertOrder.push_back(third+wturn2+"0");
        mp[third+wturn2+"0"].push_back(getNode(third+wturn2+"1", "-44"+first+routerNo));
        insertOrder.push_back(second+eturn1+"1");
        mp[third+wturn2+"1"].push_back(getNode(third+wturn2, "-ret"+third+wturn1));

        insertOrder.push_back(third+wturn3);
        mp[third+wturn3].push_back(getNode("L","+S"+third+wturn3+"L"));
        mp["L"].push_back(getNode(third+wturn3+"0","+5"+first+routerNo));
        insertOrder.push_back(third+wturn3+"0");
        mp[third+wturn3+"0"].push_back(getNode(third+wturn3+"1", "-55"+first+routerNo));
        insertOrder.push_back(third+wturn3+"1");
        mp[third+wturn3+"1"].push_back(getNode(third+wturn3, "-ret"+third+wturn2));

        insertOrder.push_back(fourth+nturn1);
        mp[fourth+nturn1].push_back(getNode("L","+S"+fourth+nturn1+"L"));
        mp["L"].push_back(getNode(fourth+nturn1+"0","+6"+first+routerNo));
        insertOrder.push_back(fourth+nturn1+"0");
        mp[fourth+nturn1+"0"].push_back(getNode(fourth+nturn1+"1", "-66"+first+routerNo));
        insertOrder.push_back(fourth+nturn1+"1");
        mp[fourth+nturn1+"1"].push_back(getNode(fourth+nturn1, "-ret"+third+wturn3));

        insertOrder.push_back(fourth+nturn2);
        mp[fourth+nturn2].push_back(getNode("L","+S"+fourth+nturn2+"L"));
        mp["L"].push_back(getNode(fourth+nturn2+"0","+7"+first+routerNo));
        insertOrder.push_back(fourth+nturn2+"0");
        mp[fourth+nturn2+"0"].push_back(getNode(fourth+nturn2+"1", "-77"+first+routerNo));
        insertOrder.push_back(fourth+nturn2+"1");
        mp[fourth+nturn2+"1"].push_back(getNode(fourth+nturn2, "-ret"+fourth+nturn1));

        insertOrder.push_back(fourth+nturn3);
        mp[fourth+nturn3].push_back(getNode("L","+S"+fourth+nturn3+"L"));
        mp["L"].push_back(getNode(fourth+nturn3+"0","+8"+first+routerNo));
        insertOrder.push_back(fourth+nturn3+"0");
        mp[fourth+nturn3+"0"].push_back(getNode(fourth+nturn3+"1", "-88"+first+routerNo));
        insertOrder.push_back(fourth+nturn3+"1");
        mp[fourth+nturn3+"1"].push_back(getNode(fourth+nturn3, "-ret"+fourth+nturn2));

        insertOrder.push_back(fifth+sturn1);
        mp[fifth+sturn1].push_back(getNode("L","+S"+fifth+sturn1+"L"));
        mp["L"].push_back(getNode(fifth+sturn1+"0","+9"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"0");
        mp[fifth+sturn1+"0"].push_back(getNode(fifth+sturn1+"1", "-99"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"1");
        mp[fifth+sturn1+"1"].push_back(getNode(fifth+sturn1, "-ret"+fourth+nturn3));

        insertOrder.push_back(fifth+sturn2);
        mp[fifth+sturn2].push_back(getNode("L","+S"+fifth+sturn2+"L"));
        mp["L"].push_back(getNode(fifth+sturn2+"0","+10"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"0");
        mp[fifth+sturn2+"0"].push_back(getNode(fifth+sturn2+"1", "-1010"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"1");
        mp[fifth+sturn2+"1"].push_back(getNode(fifth+sturn2, "-ret"+fifth+sturn1));

        insertOrder.push_back(fifth+sturn3);
        mp[fifth+sturn3].push_back(getNode("L","+S"+fifth+sturn3+"L"));
        mp["L"].push_back(getNode(fifth+sturn3+"0","+8"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"0");
        mp[fifth+sturn3+"0"].push_back(getNode(fifth+sturn3+"1", "-88"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"1");
        mp[fifth+sturn3+"1"].push_back(getNode(fifth+sturn3, "-ret"+fifth+sturn2));

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    else{

        string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
        if(first == "E"){
            dir1 = "Ns";
            dir2 = "Nws";
            dir3 = "Wse";
            dir4 = "We";
            dir5 = "Wne";
            dir6 = "Sen";
            dir7 = "Sn";
        }
        if(first == "W"){
            dir1 = "Esw";
            dir2 = "Ns";
            dir3 = "Nws";
            dir4 = "Ew";
            dir5 = "Enw";
            dir6 = "Sn";
            dir7 = "Swn";
        }
        if(first == "N"){
            dir1 = "We";
            dir2 = "Wne";
            dir3 = "Sen";
            dir4 = "Sn";
            dir5 = "Ew";
            dir6 = "Enw";
            dir7 = "Swn";
        }
        if(first == "S"){
            dir1 = "Nes";
            dir2 = "Wse";
            dir3 = "We";
            dir4 = "Ns";
            dir5 = "Esw";
            dir6 = "Ew";
            dir7 = "Nws";
        }

        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir1);
        mp[dir1].push_back(getNode(first+turn1,"+S"+dir1+first+turn1+routerNo));

        insertOrder.push_back(first+turn1);
        mp[first+turn1].push_back(getNode("Tr","+B"+adjRouter+turn1+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn1));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"0");
        mp[dir1+"0"].push_back(getNode(dir1+"1","-00"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"1");
        mp[dir1+"1"].push_back(getNode(dir1,"-ret"+first+turn1+dir3+routerNo));


        mp["Ret"].push_back(getNode(dir2+"0","+1"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"0");
        mp[dir2+"0"].push_back(getNode(dir2+"1","-11"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"1");
        mp[dir2+"1"].push_back(getNode(dir2,"-ret"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2);
        mp[dir2].push_back(getNode(first+turn1,"+S"+dir2+first+turn1+routerNo));



        mp["Ret"].push_back(getNode(dir3+"0","+2"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"0");
        mp[dir3+"0"].push_back(getNode(dir3+"1","-22"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"1");
        mp[dir3+"1"].push_back(getNode(dir3,"-ret"+first+turn1+dir2+routerNo));

        insertOrder.push_back(dir3);
        mp[dir3].push_back(getNode(first+turn1,"+S"+dir3+first+turn1+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);


        {
            mp.clear();
            insertOrder.clear();


            insertOrder.push_back("L");
            mp["L"].push_back(getNode(first+turn2,"+SL"+first+turn2+routerNo));

            insertOrder.push_back(first+turn2);
            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            insertOrder.push_back("Tr");
            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            insertOrder.push_back("Ret");
            mp["Ret"].push_back(getNode("L0","+0"+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-00"+first+turn2+routerNo));

            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("L","-ret"+first+turn2+"L"+routerNo));




            insertOrder.push_back(dir4);
            mp[dir4].push_back(getNode(first+turn2,"+S"+dir4+first+turn2+routerNo));

            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            mp["Ret"].push_back(getNode(dir4+"0","+0"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"0");
            mp[dir4+"0"].push_back(getNode(dir4+"1","-00"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"1");
            mp[dir4+"1"].push_back(getNode(dir4,"-ret"+first+turn2+"L"+routerNo));





            AdjacencyListTo_GraphGenerator(mp,insertOrder);
        }


        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir5);
        mp[dir5].push_back(getNode(first+turn1,"+S"+dir5+first+turn3+routerNo));

        insertOrder.push_back(first+turn3);
        mp[first+turn3].push_back(getNode("Tr","+B"+adjRouter+turn3+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn3));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"0");
        mp[dir5+"0"].push_back(getNode(dir5+"1","-00"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"1");
        mp[dir5+"1"].push_back(getNode(dir5,"-ret"+first+turn3+dir7+routerNo));


        mp["Ret"].push_back(getNode(dir6+"0","+1"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"0");
        mp[dir6+"0"].push_back(getNode(dir6+"1","-11"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"1");
        mp[dir6+"1"].push_back(getNode(dir6,"-ret"+first+turn3+dir5+routerNo));

        insertOrder.push_back(dir6);
        mp[dir6].push_back(getNode(first+turn3,"+S"+dir6+first+turn3+routerNo));



        mp["Ret"].push_back(getNode(dir7+"0","+2"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"0");
        mp[dir7+"0"].push_back(getNode(dir7+"1","-22"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"1");
        mp[dir7+"1"].push_back(getNode(dir7,"-ret"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7);
        mp[dir7].push_back(getNode(first+turn3,"+S"+dir7+first+turn3+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);



    }





}

//for 3 wire connectin router:
void ArbiterBuilder(int no, string first, string second, string third, string fourth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string eturn1 = "se";
    string eturn2 = "e";
    string eturn3 = "ne";
    string wturn1 = "sw";
    string wturn2 = "w";
    string wturn3 = "nw";
    string nturn1 = "en";
    string nturn2 = "n";
    string nturn3 = "wn";
    string sturn1 = "es";
    string sturn2 = "s";
    string sturn3 = "ws";


    map<char,int> dirGuid;
    dirGuid['E'] = 0, dirGuid['W'] = 0,dirGuid['N'] = 0, dirGuid['S'] = 0;
    if(first == "E" || second == "E" || third == "E" || fourth == "E" ){
        dirGuid['E'] = 1;
    }

    if(first == "W" || second == "W" || third == "W" || fourth == "W" ){
        dirGuid['W'] = 1;
    }

    if(first == "N" || second == "N" || third == "N" || fourth == "N" ){
        dirGuid['N'] = 1;
    }

    if(first == "S" || second == "S" || third == "S" || fourth == "S" ){
        dirGuid['S'] = 1;
    }

    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "E";

    }
    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "W";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "N";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "S";

    }

    if(first == "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("L");
        if(dirGuid[second[0]] == 1){
            insertOrder.push_back(second+eturn1);
            mp[second+eturn1].push_back(getNode("L","+S"+second+eturn1+"L"));
            mp["L"].push_back(getNode(second+eturn1+"0","+0"+first+routerNo));
            insertOrder.push_back(second+eturn1+"0");
            mp[second+eturn1+"0"].push_back(getNode(second+eturn1+"1", "-00"+first+routerNo));
            /*
            insertOrder.push_back(second+eturn1+"1");
            mp[second+eturn1+"1"].push_back(getNode(second+eturn1, "-ret"+fifth+sturn3));
            */
            insertOrder.push_back(second+eturn2);
            mp[second+eturn2].push_back(getNode("L","+S"+second+eturn2+"L"));
            mp["L"].push_back(getNode(second+eturn2+"0","+1"+first+routerNo));
            insertOrder.push_back(second+eturn2+"0");
            mp[second+eturn2+"0"].push_back(getNode(second+eturn2+"1", "-11"+first+routerNo));
            insertOrder.push_back(second+eturn2+"1");
            mp[second+eturn2+"1"].push_back(getNode(second+eturn2, "-ret"+second+eturn1));

            insertOrder.push_back(second+eturn3);
            mp[second+eturn3].push_back(getNode("L","+S"+second+eturn3+"L"));
            mp["L"].push_back(getNode(second+eturn3+"0","+2"+first+routerNo));
            insertOrder.push_back(second+eturn3+"0");
            mp[second+eturn3+"0"].push_back(getNode(second+eturn3+"1", "-22"+first+routerNo));
            insertOrder.push_back(second+eturn3+"1");
            mp[second+eturn3+"1"].push_back(getNode(second+eturn3, "-ret"+second+eturn2));
        }


        if(dirGuid[third[0]] == 1){
            insertOrder.push_back(third+wturn1);
            mp[third+wturn1].push_back(getNode("L","+S"+third+wturn1+"L"));
            mp["L"].push_back(getNode(third+wturn1+"0","+3"+first+routerNo));
            insertOrder.push_back(third+wturn1+"0");
            mp[third+wturn1+"0"].push_back(getNode(third+wturn1+"1", "-33"+first+routerNo));
            insertOrder.push_back(third+wturn1+"1");
            mp[third+wturn1+"1"].push_back(getNode(third+wturn1, "-ret"+second+eturn3));

            insertOrder.push_back(third+wturn2);
            mp[third+wturn2].push_back(getNode("L","+S"+third+wturn2+"L"));
            mp["L"].push_back(getNode(third+wturn2+"0","+4"+first+routerNo));
            insertOrder.push_back(third+wturn2+"0");
            mp[third+wturn2+"0"].push_back(getNode(third+wturn2+"1", "-44"+first+routerNo));
            insertOrder.push_back(second+eturn1+"1");
            mp[third+wturn2+"1"].push_back(getNode(third+wturn2, "-ret"+third+wturn1));

            insertOrder.push_back(third+wturn3);
            mp[third+wturn3].push_back(getNode("L","+S"+third+wturn3+"L"));
            mp["L"].push_back(getNode(third+wturn3+"0","+5"+first+routerNo));
            insertOrder.push_back(third+wturn3+"0");
            mp[third+wturn3+"0"].push_back(getNode(third+wturn3+"1", "-55"+first+routerNo));
            insertOrder.push_back(third+wturn3+"1");
            mp[third+wturn3+"1"].push_back(getNode(third+wturn3, "-ret"+third+wturn2));
        }

        if(dirGuid[fourth[0]] == 1){
            insertOrder.push_back(fourth+nturn1);
            mp[fourth+nturn1].push_back(getNode("L","+S"+fourth+nturn1+"L"));
            mp["L"].push_back(getNode(fourth+nturn1+"0","+6"+first+routerNo));
            insertOrder.push_back(fourth+nturn1+"0");
            mp[fourth+nturn1+"0"].push_back(getNode(fourth+nturn1+"1", "-66"+first+routerNo));
            insertOrder.push_back(fourth+nturn1+"1");
            mp[fourth+nturn1+"1"].push_back(getNode(fourth+nturn1, "-ret"+third+wturn3));

            insertOrder.push_back(fourth+nturn2);
            mp[fourth+nturn2].push_back(getNode("L","+S"+fourth+nturn2+"L"));
            mp["L"].push_back(getNode(fourth+nturn2+"0","+7"+first+routerNo));
            insertOrder.push_back(fourth+nturn2+"0");
            mp[fourth+nturn2+"0"].push_back(getNode(fourth+nturn2+"1", "-77"+first+routerNo));
            insertOrder.push_back(fourth+nturn2+"1");
            mp[fourth+nturn2+"1"].push_back(getNode(fourth+nturn2, "-ret"+fourth+nturn1));

            insertOrder.push_back(fourth+nturn3);
            mp[fourth+nturn3].push_back(getNode("L","+S"+fourth+nturn3+"L"));
            mp["L"].push_back(getNode(fourth+nturn3+"0","+8"+first+routerNo));
            insertOrder.push_back(fourth+nturn3+"0");
            mp[fourth+nturn3+"0"].push_back(getNode(fourth+nturn3+"1", "-88"+first+routerNo));
            insertOrder.push_back(fourth+nturn3+"1");
            mp[fourth+nturn3+"1"].push_back(getNode(fourth+nturn3, "-ret"+fourth+nturn2));
        }

        /*
        insertOrder.push_back(fifth+sturn1);
        mp[fifth+sturn1].push_back(getNode("L","+S"+fifth+sturn1+"L"));
        mp["L"].push_back(getNode(fifth+sturn1+"0","+9"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"0");
        mp[fifth+sturn1+"0"].push_back(getNode(fifth+sturn1+"1", "-99"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"1");
        mp[fifth+sturn1+"1"].push_back(getNode(fifth+sturn1, "-ret"+fourth+nturn3));

        insertOrder.push_back(fifth+sturn2);
        mp[fifth+sturn2].push_back(getNode("L","+S"+fifth+sturn2+"L"));
        mp["L"].push_back(getNode(fifth+sturn2+"0","+10"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"0");
        mp[fifth+sturn2+"0"].push_back(getNode(fifth+sturn2+"1", "-1010"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"1");
        mp[fifth+sturn2+"1"].push_back(getNode(fifth+sturn2, "-ret"+fifth+sturn1));

        insertOrder.push_back(fifth+sturn3);
        mp[fifth+sturn3].push_back(getNode("L","+S"+fifth+sturn3+"L"));
        mp["L"].push_back(getNode(fifth+sturn3+"0","+8"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"0");
        mp[fifth+sturn3+"0"].push_back(getNode(fifth+sturn3+"1", "-88"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"1");
        mp[fifth+sturn3+"1"].push_back(getNode(fifth+sturn3, "-ret"+fifth+sturn2));
        */

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    else{

        string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
        if(first == "E"){
            dir1 = "Ns";
            dir2 = "Nws";
            dir3 = "Wse";
            dir4 = "We";
            dir5 = "Wne";
            dir6 = "Sen";
            dir7 = "Sn";
        }
        if(first == "W"){
            dir1 = "Esw";
            dir2 = "Ns";
            dir3 = "Nws";
            dir4 = "Ew";
            dir5 = "Enw";
            dir6 = "Sn";
            dir7 = "Swn";
        }
        if(first == "N"){
            dir1 = "We";
            dir2 = "Wne";
            dir3 = "Sen";
            dir4 = "Sn";
            dir5 = "Ew";
            dir6 = "Enw";
            dir7 = "Swn";
        }
        if(first == "S"){
            dir1 = "Nes";
            dir2 = "Wse";
            dir3 = "We";
            dir4 = "Ns";
            dir5 = "Esw";
            dir6 = "Ew";
            dir7 = "Nws";
        }

        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir1);
        mp[dir1].push_back(getNode(first+turn1,"+S"+dir1+first+turn1+routerNo));

        insertOrder.push_back(first+turn1);
        mp[first+turn1].push_back(getNode("Tr","+B"+adjRouter+turn1+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn1));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"0");
        mp[dir1+"0"].push_back(getNode(dir1+"1","-00"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"1");
        mp[dir1+"1"].push_back(getNode(dir1,"-ret"+first+turn1+dir3+routerNo));


        mp["Ret"].push_back(getNode(dir2+"0","+1"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"0");
        mp[dir2+"0"].push_back(getNode(dir2+"1","-11"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"1");
        mp[dir2+"1"].push_back(getNode(dir2,"-ret"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2);
        mp[dir2].push_back(getNode(first+turn1,"+S"+dir2+first+turn1+routerNo));



        mp["Ret"].push_back(getNode(dir3+"0","+2"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"0");
        mp[dir3+"0"].push_back(getNode(dir3+"1","-22"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"1");
        mp[dir3+"1"].push_back(getNode(dir3,"-ret"+first+turn1+dir2+routerNo));

        insertOrder.push_back(dir3);
        mp[dir3].push_back(getNode(first+turn1,"+S"+dir3+first+turn1+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);


        {
            mp.clear();
            insertOrder.clear();


            insertOrder.push_back("L");
            mp["L"].push_back(getNode(first+turn2,"+SL"+first+turn2+routerNo));

            insertOrder.push_back(first+turn2);
            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            insertOrder.push_back("Tr");
            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            insertOrder.push_back("Ret");
            mp["Ret"].push_back(getNode("L0","+0"+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-00"+first+turn2+routerNo));

            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("L","-ret"+first+turn2+"L"+routerNo));




            insertOrder.push_back(dir4);
            mp[dir4].push_back(getNode(first+turn2,"+S"+dir4+first+turn2+routerNo));

            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            mp["Ret"].push_back(getNode(dir4+"0","+0"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"0");
            mp[dir4+"0"].push_back(getNode(dir4+"1","-00"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"1");
            mp[dir4+"1"].push_back(getNode(dir4,"-ret"+first+turn2+"L"+routerNo));





            AdjacencyListTo_GraphGenerator(mp,insertOrder);
        }


        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir5);
        mp[dir5].push_back(getNode(first+turn1,"+S"+dir5+first+turn3+routerNo));

        insertOrder.push_back(first+turn3);
        mp[first+turn3].push_back(getNode("Tr","+B"+adjRouter+turn3+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn3));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"0");
        mp[dir5+"0"].push_back(getNode(dir5+"1","-00"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"1");
        mp[dir5+"1"].push_back(getNode(dir5,"-ret"+first+turn3+dir7+routerNo));


        mp["Ret"].push_back(getNode(dir6+"0","+1"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"0");
        mp[dir6+"0"].push_back(getNode(dir6+"1","-11"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"1");
        mp[dir6+"1"].push_back(getNode(dir6,"-ret"+first+turn3+dir5+routerNo));

        insertOrder.push_back(dir6);
        mp[dir6].push_back(getNode(first+turn3,"+S"+dir6+first+turn3+routerNo));



        mp["Ret"].push_back(getNode(dir7+"0","+2"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"0");
        mp[dir7+"0"].push_back(getNode(dir7+"1","-22"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"1");
        mp[dir7+"1"].push_back(getNode(dir7,"-ret"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7);
        mp[dir7].push_back(getNode(first+turn3,"+S"+dir7+first+turn3+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);



    }





}

//for 2 wire connection router:
void ArbiterBuilder(int no, string first, string second, string third, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string adjPort;
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string eturn1 = "se";
    string eturn2 = "e";
    string eturn3 = "ne";
    string wturn1 = "sw";
    string wturn2 = "w";
    string wturn3 = "nw";
    string nturn1 = "en";
    string nturn2 = "n";
    string nturn3 = "wn";
    string sturn1 = "es";
    string sturn2 = "s";
    string sturn3 = "ws";


    map<char,int> dirGuid;
    dirGuid['E'] = 0, dirGuid['W'] = 0,dirGuid['N'] = 0, dirGuid['S'] = 0;
    if(first == "E" || second == "E" || third == "E"  ){
        dirGuid['E'] = 1;
    }

    if(first == "W" || second == "W" || third == "W" ){
        dirGuid['W'] = 1;
    }

    if(first == "N" || second == "N" || third == "N" ){
        dirGuid['N'] = 1;
    }

    if(first == "S" || second == "S" || third == "S" ){
        dirGuid['S'] = 1;
    }

    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "E";

    }
    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "W";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "N";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "S";

    }

    if(first == "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("L");
        if(dirGuid[second[0]] == 1){
            insertOrder.push_back(second+eturn1);
            mp[second+eturn1].push_back(getNode("L","+S"+second+eturn1+"L"));
            mp["L"].push_back(getNode(second+eturn1+"0","+0"+first+routerNo));
            insertOrder.push_back(second+eturn1+"0");
            mp[second+eturn1+"0"].push_back(getNode(second+eturn1+"1", "-00"+first+routerNo));
            /*
            insertOrder.push_back(second+eturn1+"1");
            mp[second+eturn1+"1"].push_back(getNode(second+eturn1, "-ret"+fifth+sturn3));
            */
            insertOrder.push_back(second+eturn2);
            mp[second+eturn2].push_back(getNode("L","+S"+second+eturn2+"L"));
            mp["L"].push_back(getNode(second+eturn2+"0","+1"+first+routerNo));
            insertOrder.push_back(second+eturn2+"0");
            mp[second+eturn2+"0"].push_back(getNode(second+eturn2+"1", "-11"+first+routerNo));
            insertOrder.push_back(second+eturn2+"1");
            mp[second+eturn2+"1"].push_back(getNode(second+eturn2, "-ret"+second+eturn1));

            insertOrder.push_back(second+eturn3);
            mp[second+eturn3].push_back(getNode("L","+S"+second+eturn3+"L"));
            mp["L"].push_back(getNode(second+eturn3+"0","+2"+first+routerNo));
            insertOrder.push_back(second+eturn3+"0");
            mp[second+eturn3+"0"].push_back(getNode(second+eturn3+"1", "-22"+first+routerNo));
            insertOrder.push_back(second+eturn3+"1");
            mp[second+eturn3+"1"].push_back(getNode(second+eturn3, "-ret"+second+eturn2));
        }


        if(dirGuid[third[0]] == 1){
            insertOrder.push_back(third+wturn1);
            mp[third+wturn1].push_back(getNode("L","+S"+third+wturn1+"L"));
            mp["L"].push_back(getNode(third+wturn1+"0","+3"+first+routerNo));
            insertOrder.push_back(third+wturn1+"0");
            mp[third+wturn1+"0"].push_back(getNode(third+wturn1+"1", "-33"+first+routerNo));
            insertOrder.push_back(third+wturn1+"1");
            mp[third+wturn1+"1"].push_back(getNode(third+wturn1, "-ret"+second+eturn3));

            insertOrder.push_back(third+wturn2);
            mp[third+wturn2].push_back(getNode("L","+S"+third+wturn2+"L"));
            mp["L"].push_back(getNode(third+wturn2+"0","+4"+first+routerNo));
            insertOrder.push_back(third+wturn2+"0");
            mp[third+wturn2+"0"].push_back(getNode(third+wturn2+"1", "-44"+first+routerNo));
            insertOrder.push_back(second+eturn1+"1");
            mp[third+wturn2+"1"].push_back(getNode(third+wturn2, "-ret"+third+wturn1));

            insertOrder.push_back(third+wturn3);
            mp[third+wturn3].push_back(getNode("L","+S"+third+wturn3+"L"));
            mp["L"].push_back(getNode(third+wturn3+"0","+5"+first+routerNo));
            insertOrder.push_back(third+wturn3+"0");
            mp[third+wturn3+"0"].push_back(getNode(third+wturn3+"1", "-55"+first+routerNo));
            insertOrder.push_back(third+wturn3+"1");
            mp[third+wturn3+"1"].push_back(getNode(third+wturn3, "-ret"+third+wturn2));
        }
        /*
        if(dirGuid[fourth[0]] == 1){
            insertOrder.push_back(fourth+nturn1);
            mp[fourth+nturn1].push_back(getNode("L","+S"+fourth+nturn1+"L"));
            mp["L"].push_back(getNode(fourth+nturn1+"0","+6"+first+routerNo));
            insertOrder.push_back(fourth+nturn1+"0");
            mp[fourth+nturn1+"0"].push_back(getNode(fourth+nturn1+"1", "-66"+first+routerNo));
            insertOrder.push_back(fourth+nturn1+"1");
            mp[fourth+nturn1+"1"].push_back(getNode(fourth+nturn1, "-ret"+third+wturn3));

            insertOrder.push_back(fourth+nturn2);
            mp[fourth+nturn2].push_back(getNode("L","+S"+fourth+nturn2+"L"));
            mp["L"].push_back(getNode(fourth+nturn2+"0","+7"+first+routerNo));
            insertOrder.push_back(fourth+nturn2+"0");
            mp[fourth+nturn2+"0"].push_back(getNode(fourth+nturn2+"1", "-77"+first+routerNo));
            insertOrder.push_back(fourth+nturn2+"1");
            mp[fourth+nturn2+"1"].push_back(getNode(fourth+nturn2, "-ret"+fourth+nturn1));

            insertOrder.push_back(fourth+nturn3);
            mp[fourth+nturn3].push_back(getNode("L","+S"+fourth+nturn3+"L"));
            mp["L"].push_back(getNode(fourth+nturn3+"0","+8"+first+routerNo));
            insertOrder.push_back(fourth+nturn3+"0");
            mp[fourth+nturn3+"0"].push_back(getNode(fourth+nturn3+"1", "-88"+first+routerNo));
            insertOrder.push_back(fourth+nturn3+"1");
            mp[fourth+nturn3+"1"].push_back(getNode(fourth+nturn3, "-ret"+fourth+nturn2));
        }


        insertOrder.push_back(fifth+sturn1);
        mp[fifth+sturn1].push_back(getNode("L","+S"+fifth+sturn1+"L"));
        mp["L"].push_back(getNode(fifth+sturn1+"0","+9"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"0");
        mp[fifth+sturn1+"0"].push_back(getNode(fifth+sturn1+"1", "-99"+first+routerNo));
        insertOrder.push_back(fifth+sturn1+"1");
        mp[fifth+sturn1+"1"].push_back(getNode(fifth+sturn1, "-ret"+fourth+nturn3));

        insertOrder.push_back(fifth+sturn2);
        mp[fifth+sturn2].push_back(getNode("L","+S"+fifth+sturn2+"L"));
        mp["L"].push_back(getNode(fifth+sturn2+"0","+10"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"0");
        mp[fifth+sturn2+"0"].push_back(getNode(fifth+sturn2+"1", "-1010"+first+routerNo));
        insertOrder.push_back(fifth+sturn2+"1");
        mp[fifth+sturn2+"1"].push_back(getNode(fifth+sturn2, "-ret"+fifth+sturn1));

        insertOrder.push_back(fifth+sturn3);
        mp[fifth+sturn3].push_back(getNode("L","+S"+fifth+sturn3+"L"));
        mp["L"].push_back(getNode(fifth+sturn3+"0","+8"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"0");
        mp[fifth+sturn3+"0"].push_back(getNode(fifth+sturn3+"1", "-88"+first+routerNo));
        insertOrder.push_back(fifth+sturn3+"1");
        mp[fifth+sturn3+"1"].push_back(getNode(fifth+sturn3, "-ret"+fifth+sturn2));
        */

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    else{

        string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
        if(first == "E"){
            dir1 = "Ns";
            dir2 = "Nws";
            dir3 = "Wse";
            dir4 = "We";
            dir5 = "Wne";
            dir6 = "Sen";
            dir7 = "Sn";
        }
        if(first == "W"){
            dir1 = "Esw";
            dir2 = "Ns";
            dir3 = "Nws";
            dir4 = "Ew";
            dir5 = "Enw";
            dir6 = "Sn";
            dir7 = "Swn";
        }
        if(first == "N"){
            dir1 = "We";
            dir2 = "Wne";
            dir3 = "Sen";
            dir4 = "Sn";
            dir5 = "Ew";
            dir6 = "Enw";
            dir7 = "Swn";
        }
        if(first == "S"){
            dir1 = "Nes";
            dir2 = "Wse";
            dir3 = "We";
            dir4 = "Ns";
            dir5 = "Esw";
            dir6 = "Ew";
            dir7 = "Nws";
        }

        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir1);
        mp[dir1].push_back(getNode(first+turn1,"+S"+dir1+first+turn1+routerNo));

        insertOrder.push_back(first+turn1);
        mp[first+turn1].push_back(getNode("Tr","+B"+adjRouter+turn1+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn1));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"0");
        mp[dir1+"0"].push_back(getNode(dir1+"1","-00"+first+turn1+routerNo));

        insertOrder.push_back(dir1+"1");
        mp[dir1+"1"].push_back(getNode(dir1,"-ret"+first+turn1+dir3+routerNo));


        mp["Ret"].push_back(getNode(dir2+"0","+1"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"0");
        mp[dir2+"0"].push_back(getNode(dir2+"1","-11"+first+turn1+routerNo));

        insertOrder.push_back(dir2+"1");
        mp[dir2+"1"].push_back(getNode(dir2,"-ret"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2);
        mp[dir2].push_back(getNode(first+turn1,"+S"+dir2+first+turn1+routerNo));



        mp["Ret"].push_back(getNode(dir3+"0","+2"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"0");
        mp[dir3+"0"].push_back(getNode(dir3+"1","-22"+first+turn1+routerNo));

        insertOrder.push_back(dir3+"1");
        mp[dir3+"1"].push_back(getNode(dir3,"-ret"+first+turn1+dir2+routerNo));

        insertOrder.push_back(dir3);
        mp[dir3].push_back(getNode(first+turn1,"+S"+dir3+first+turn1+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);


        {
            mp.clear();
            insertOrder.clear();


            insertOrder.push_back("L");
            mp["L"].push_back(getNode(first+turn2,"+SL"+first+turn2+routerNo));

            insertOrder.push_back(first+turn2);
            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            insertOrder.push_back("Tr");
            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            insertOrder.push_back("Ret");
            mp["Ret"].push_back(getNode("L0","+0"+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-00"+first+turn2+routerNo));

            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("L","-ret"+first+turn2+"L"+routerNo));




            insertOrder.push_back(dir4);
            mp[dir4].push_back(getNode(first+turn2,"+S"+dir4+first+turn2+routerNo));

            mp[first+turn2].push_back(getNode("Tr","+B"+adjRouter+turn2+nextRouter));

            mp["Tr"].push_back(getNode("Ret","-A"+first+turn2));

            mp["Ret"].push_back(getNode(dir4+"0","+0"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"0");
            mp[dir4+"0"].push_back(getNode(dir4+"1","-00"+first+turn2+routerNo));

            insertOrder.push_back(dir4+"1");
            mp[dir4+"1"].push_back(getNode(dir4,"-ret"+first+turn2+"L"+routerNo));





            AdjacencyListTo_GraphGenerator(mp,insertOrder);
        }


        mp.clear();
        insertOrder.clear();

        insertOrder.push_back(dir5);
        mp[dir5].push_back(getNode(first+turn1,"+S"+dir5+first+turn3+routerNo));

        insertOrder.push_back(first+turn3);
        mp[first+turn3].push_back(getNode("Tr","+B"+adjRouter+turn3+nextRouter));

        insertOrder.push_back("Tr");
        mp["Tr"].push_back(getNode("Ret","-A"+first+turn3));

        insertOrder.push_back("Ret");
        mp["Ret"].push_back(getNode(dir1+"0","+0"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"0");
        mp[dir5+"0"].push_back(getNode(dir5+"1","-00"+first+turn3+routerNo));

        insertOrder.push_back(dir5+"1");
        mp[dir5+"1"].push_back(getNode(dir5,"-ret"+first+turn3+dir7+routerNo));


        mp["Ret"].push_back(getNode(dir6+"0","+1"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"0");
        mp[dir6+"0"].push_back(getNode(dir6+"1","-11"+first+turn3+routerNo));

        insertOrder.push_back(dir6+"1");
        mp[dir6+"1"].push_back(getNode(dir6,"-ret"+first+turn3+dir5+routerNo));

        insertOrder.push_back(dir6);
        mp[dir6].push_back(getNode(first+turn3,"+S"+dir6+first+turn3+routerNo));



        mp["Ret"].push_back(getNode(dir7+"0","+2"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"0");
        mp[dir7+"0"].push_back(getNode(dir7+"1","-22"+first+turn3+routerNo));

        insertOrder.push_back(dir7+"1");
        mp[dir7+"1"].push_back(getNode(dir7,"-ret"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7);
        mp[dir7].push_back(getNode(first+turn3,"+S"+dir7+first+turn3+routerNo));


        AdjacencyListTo_GraphGenerator(mp,insertOrder);



    }



}

//priority machine builder:
void PriorityBuilder(int no, string first, int router){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    if(first != "L"){
        for(int i=0;i<(no-1)*3;i++){
            insertOrder.push_back(to_string(i));
            mp[to_string(i)].push_back(getNode(to_string(i)+to_string(i), "-"+to_string((i+1)%((no-1)*3))+first+routerNo));
            insertOrder.push_back(to_string(i)+to_string(i));
            mp[(to_string(i)+to_string(i))].push_back(getNode(to_string((i+1)%((no-1)*3)),"+"+to_string((i+1)%((no-1)*3))+to_string((i+1)%((no-1)*3))+first+routerNo));
        }
        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();
        for(int i=0;i<(no-1)*3;i++){
            insertOrder.push_back(to_string(i));
            mp[to_string(i)].push_back(getNode(to_string(i)+to_string(i), "-"+to_string((i+1)%((no-1)*3))+first+routerNo));
            insertOrder.push_back(to_string(i)+to_string(i));
            mp[(to_string(i)+to_string(i))].push_back(getNode(to_string((i+1)%((no-1)*3)),"+"+to_string((i+1)%((no-1)*3))+to_string((i+1)%((no-1)*3))+first+routerNo));
        }
        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        for(int i=0;i<(no-1)*3;i++){
            insertOrder.push_back(to_string(i));
            mp[to_string(i)].push_back(getNode(to_string(i)+to_string(i), "-"+to_string((i+1)%((no-1)*3))+first+routerNo));
            insertOrder.push_back(to_string(i)+to_string(i));
            mp[(to_string(i)+to_string(i))].push_back(getNode(to_string((i+1)%((no-1)*3)),"+"+to_string((i+1)%((no-1)*3))+to_string((i+1)%((no-1)*3))+first+routerNo));
        }
        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }

}


//*********************************************************************


//************ Switch Generation **************************************
//for 4 wire connectin router:
void SwitchBuilder(int no, string first, string second, string third, string fourth, string fifth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn1+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn1+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir1.substr(0,1)+"0","+C"+dir1.substr(0,1)+first+turn1+routerNo));
        mp["Comp"].push_back(getNode(dir2.substr(0,1)+"0","+C"+dir2.substr(0,1)+first+turn1+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn1+"L"+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"0");
        mp[dir1.substr(0,1)+"0"].push_back(getNode(dir1.substr(0,1)+"1","-S"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"0");//
        mp[dir2.substr(0,1)+"0"].push_back(getNode(dir2.substr(0,1)+"1","-S"+first+turn1+dir2+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn1+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"1");
        mp[dir1.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir1+first+turn1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"1");
        mp[dir2.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir2+first+turn1+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn1+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn1+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn2+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");
        if(first != "L"){
            mp["Comp"].push_back(getNode("L0","+CL"+first+turn2+routerNo));//local is always present
            mp["Comp"].push_back(getNode(dir3.substr(0,1)+"0","+C"+dir3.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir4.substr(0,1)+"0","+C"+dir4.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir5.substr(0,1)+"0","+C"+dir5.substr(0,1)+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-S"+first+turn2+"L"+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"0");
            mp[dir3.substr(0,1)+"0"].push_back(getNode(dir3.substr(0,1)+"1","-S"+first+turn2+dir3+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"0");//
            mp[dir4.substr(0,1)+"0"].push_back(getNode(dir4.substr(0,1)+"1","-S"+first+turn2+dir4+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"0");//
            mp[dir5.substr(0,1)+"0"].push_back(getNode(dir5.substr(0,1)+"1","-S"+first+turn2+dir5+routerNo));



            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("rets","+retL"+first+turn2+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"1");
            mp[dir3.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"1");
            mp[dir4.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"1");
            mp[dir5.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir5+first+turn2+routerNo));



        }else{
            mp["Comp"].push_back(getNode(second+"0","+C"+second+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(third+"0","+C"+third+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+turn2+routerNo));

            insertOrder.push_back(second+"0");
            mp[second+"0"].push_back(getNode(second+"1","-S"+first+turn2+dir1+routerNo));

            insertOrder.push_back(third+"0");
            mp[third+"0"].push_back(getNode(third+"1","-S"+first+turn2+dir2+routerNo));

            insertOrder.push_back(fourth+"0");//
            mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+turn2+dir3+routerNo));

            insertOrder.push_back(fifth+"0");//
            mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+turn2+dir4+routerNo));



            insertOrder.push_back(second+"1");
            mp[second+"1"].push_back(getNode("rets","+ret"+dir1+first+routerNo));

            insertOrder.push_back(third+"1");
            mp[third+"1"].push_back(getNode("rets","+ret"+dir2+first+turn2+routerNo));

            insertOrder.push_back(fourth+"1");
            mp[fourth+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            insertOrder.push_back(fifth+"1");
            mp[fifth+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));
        }







        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn2+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn2+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn3+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn3+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir6.substr(0,1)+"0","+C"+dir6.substr(0,1)+first+turn3+routerNo));
        mp["Comp"].push_back(getNode(dir7.substr(0,1)+"0","+C"+dir7.substr(0,1)+first+turn3+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn3+"L"+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"0");
        mp[dir6.substr(0,1)+"0"].push_back(getNode(dir6.substr(0,1)+"1","-S"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"0");//
        mp[dir7.substr(0,1)+"0"].push_back(getNode(dir7.substr(0,1)+"1","-S"+first+turn3+dir7+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn3+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"1");
        mp[dir6.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir6+first+turn3+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"1");
        mp[dir7.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir7+first+turn3+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn3+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn3+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }





}

//for 3 wire connectin router:
void SwitchBuilder(int no, string first, string second, string third, string fourth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn1+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn1+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir1.substr(0,1)+"0","+C"+dir1.substr(0,1)+first+turn1+routerNo));
        mp["Comp"].push_back(getNode(dir2.substr(0,1)+"0","+C"+dir2.substr(0,1)+first+turn1+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn1+"L"+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"0");
        mp[dir1.substr(0,1)+"0"].push_back(getNode(dir1.substr(0,1)+"1","-S"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"0");//
        mp[dir2.substr(0,1)+"0"].push_back(getNode(dir2.substr(0,1)+"1","-S"+first+turn1+dir2+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn1+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"1");
        mp[dir1.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir1+first+turn1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"1");
        mp[dir2.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir2+first+turn1+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn1+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn1+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn2+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");
        if(first != "L"){
            mp["Comp"].push_back(getNode("L0","+CL"+first+turn2+routerNo));//local is always present
            mp["Comp"].push_back(getNode(dir3.substr(0,1)+"0","+C"+dir3.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir4.substr(0,1)+"0","+C"+dir4.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir5.substr(0,1)+"0","+C"+dir5.substr(0,1)+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-S"+first+turn2+"L"+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"0");
            mp[dir3.substr(0,1)+"0"].push_back(getNode(dir3.substr(0,1)+"1","-S"+first+turn2+dir3+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"0");//
            mp[dir4.substr(0,1)+"0"].push_back(getNode(dir4.substr(0,1)+"1","-S"+first+turn2+dir4+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"0");//
            mp[dir5.substr(0,1)+"0"].push_back(getNode(dir5.substr(0,1)+"1","-S"+first+turn2+dir5+routerNo));



            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("rets","+retL"+first+turn2+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"1");
            mp[dir3.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"1");
            mp[dir4.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"1");
            mp[dir5.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir5+first+turn2+routerNo));



        }else{
            mp["Comp"].push_back(getNode(second+"0","+C"+second+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(third+"0","+C"+third+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+turn2+routerNo));
            //mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+turn2+routerNo));

            insertOrder.push_back(second+"0");
            mp[second+"0"].push_back(getNode(second+"1","-S"+first+turn2+dir1+routerNo));

            insertOrder.push_back(third+"0");
            mp[third+"0"].push_back(getNode(third+"1","-S"+first+turn2+dir2+routerNo));

            insertOrder.push_back(fourth+"0");//
            mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+turn2+dir3+routerNo));

            //insertOrder.push_back(fifth+"0");//
            //mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+turn2+dir4+routerNo));



            insertOrder.push_back(second+"1");
            mp[second+"1"].push_back(getNode("rets","+ret"+dir1+first+routerNo));

            insertOrder.push_back(third+"1");
            mp[third+"1"].push_back(getNode("rets","+ret"+dir2+first+turn2+routerNo));

            insertOrder.push_back(fourth+"1");
            mp[fourth+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            //insertOrder.push_back(fifth+"1");
            //mp[fifth+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));
        }







        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn2+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn2+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn3+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn3+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir6.substr(0,1)+"0","+C"+dir6.substr(0,1)+first+turn3+routerNo));
        mp["Comp"].push_back(getNode(dir7.substr(0,1)+"0","+C"+dir7.substr(0,1)+first+turn3+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn3+"L"+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"0");
        mp[dir6.substr(0,1)+"0"].push_back(getNode(dir6.substr(0,1)+"1","-S"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"0");//
        mp[dir7.substr(0,1)+"0"].push_back(getNode(dir7.substr(0,1)+"1","-S"+first+turn3+dir7+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn3+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"1");
        mp[dir6.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir6+first+turn3+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"1");
        mp[dir7.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir7+first+turn3+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn3+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn3+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }





}

//for 2 wire connection router:
void SwitchBuilder(int no, string first, string second, string third, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn1+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn1+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir1.substr(0,1)+"0","+C"+dir1.substr(0,1)+first+turn1+routerNo));
        mp["Comp"].push_back(getNode(dir2.substr(0,1)+"0","+C"+dir2.substr(0,1)+first+turn1+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn1+"L"+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"0");
        mp[dir1.substr(0,1)+"0"].push_back(getNode(dir1.substr(0,1)+"1","-S"+first+turn1+dir1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"0");//
        mp[dir2.substr(0,1)+"0"].push_back(getNode(dir2.substr(0,1)+"1","-S"+first+turn1+dir2+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn1+routerNo));

        insertOrder.push_back(dir1.substr(0,1)+"1");
        mp[dir1.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir1+first+turn1+routerNo));

        insertOrder.push_back(dir2.substr(0,1)+"1");
        mp[dir2.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir2+first+turn1+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn1+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn1+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn2+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");
        if(first != "L"){
            mp["Comp"].push_back(getNode("L0","+CL"+first+turn2+routerNo));//local is always present
            mp["Comp"].push_back(getNode(dir3.substr(0,1)+"0","+C"+dir3.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir4.substr(0,1)+"0","+C"+dir4.substr(0,1)+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(dir5.substr(0,1)+"0","+C"+dir5.substr(0,1)+first+turn2+routerNo));

            insertOrder.push_back("L0");
            mp["L0"].push_back(getNode("L1","-S"+first+turn2+"L"+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"0");
            mp[dir3.substr(0,1)+"0"].push_back(getNode(dir3.substr(0,1)+"1","-S"+first+turn2+dir3+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"0");//
            mp[dir4.substr(0,1)+"0"].push_back(getNode(dir4.substr(0,1)+"1","-S"+first+turn2+dir4+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"0");//
            mp[dir5.substr(0,1)+"0"].push_back(getNode(dir5.substr(0,1)+"1","-S"+first+turn2+dir5+routerNo));



            insertOrder.push_back("L1");
            mp["L1"].push_back(getNode("rets","+retL"+first+turn2+routerNo));

            insertOrder.push_back(dir3.substr(0,1)+"1");
            mp[dir3.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            insertOrder.push_back(dir4.substr(0,1)+"1");
            mp[dir4.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));

            insertOrder.push_back(dir5.substr(0,1)+"1");
            mp[dir5.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir5+first+turn2+routerNo));



        }else{
            mp["Comp"].push_back(getNode(second+"0","+C"+second+first+turn2+routerNo));
            mp["Comp"].push_back(getNode(third+"0","+C"+third+first+turn2+routerNo));
            //mp["Comp"].push_back(getNode(fourth+"0","+C"+fourth+first+turn2+routerNo));
            //mp["Comp"].push_back(getNode(fifth+"0","+C"+fifth+first+turn2+routerNo));

            insertOrder.push_back(second+"0");
            mp[second+"0"].push_back(getNode(second+"1","-S"+first+turn2+dir1+routerNo));

            insertOrder.push_back(third+"0");
            mp[third+"0"].push_back(getNode(third+"1","-S"+first+turn2+dir2+routerNo));
            /*
            insertOrder.push_back(fourth+"0");//
            mp[fourth+"0"].push_back(getNode(fourth+"1","-S"+first+turn2+dir3+routerNo));

            insertOrder.push_back(fifth+"0");//
            mp[fifth+"0"].push_back(getNode(fifth+"1","-S"+first+turn2+dir4+routerNo));
            */


            insertOrder.push_back(second+"1");
            mp[second+"1"].push_back(getNode("rets","+ret"+dir1+first+routerNo));

            insertOrder.push_back(third+"1");
            mp[third+"1"].push_back(getNode("rets","+ret"+dir2+first+turn2+routerNo));

            /*
            insertOrder.push_back(fourth+"1");
            mp[fourth+"1"].push_back(getNode("rets","+ret"+dir3+first+turn2+routerNo));

            insertOrder.push_back(fifth+"1");
            mp[fifth+"1"].push_back(getNode("rets","+ret"+dir4+first+turn2+routerNo));
            */
        }







        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn2+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn2+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("wt");
        mp["wt"].push_back(getNode("st","+BT"+first+turn3+routerNo));

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","-Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","+CL"+first+turn3+routerNo));//local is always present
        mp["Comp"].push_back(getNode(dir6.substr(0,1)+"0","+C"+dir6.substr(0,1)+first+turn3+routerNo));
        mp["Comp"].push_back(getNode(dir7.substr(0,1)+"0","+C"+dir7.substr(0,1)+first+turn3+routerNo));


        insertOrder.push_back("L0");
        mp["L0"].push_back(getNode("L1","-S"+first+turn3+"L"+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"0");
        mp[dir6.substr(0,1)+"0"].push_back(getNode(dir6.substr(0,1)+"1","-S"+first+turn3+dir6+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"0");//
        mp[dir7.substr(0,1)+"0"].push_back(getNode(dir7.substr(0,1)+"1","-S"+first+turn3+dir7+routerNo));



        insertOrder.push_back("L1");
        mp["L1"].push_back(getNode("rets","+retL"+first+turn3+routerNo));

        insertOrder.push_back(dir6.substr(0,1)+"1");
        mp[dir6.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir6+first+turn3+routerNo));

        insertOrder.push_back(dir7.substr(0,1)+"1");
        mp[dir7.substr(0,1)+"1"].push_back(getNode("rets","+ret"+dir7+first+turn3+routerNo));


        insertOrder.push_back("rets");
        mp["rets"].push_back(getNode("retb","-ret"+first+turn3+routerNo));

        insertOrder.push_back("retb");
        mp["retb"].push_back(getNode("wt","-retComp"+first+turn3+routerNo));



        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }


}

//************************* Compute Machine *************************************
void Compute(int no, string first, string second, string third, string fourth, string fifth, int router,int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    map<char,int> dirGuid;
    dirGuid['E'] = 0, dirGuid['W'] = 0,dirGuid['N'] = 0, dirGuid['S'] = 0;
    if(first == "E" || second == "E" || third == "E" || fourth == "E" || fifth == "E"){
        dirGuid['E'] = 1;
    }

    if(first == "W" || second == "W" || third == "W" || fourth == "W" || fifth == "W"){
        dirGuid['W'] = 1;
    }

    if(first == "N" || second == "N" || third == "N" || fourth == "N" || fifth == "N"){
        dirGuid['N'] = 1;
    }

    if(first == "S" || second == "S" || third == "S" || fourth == "S" || fifth == "S"){
        dirGuid['S'] = 1;
    }

    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn1+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        if(dirGuid[dir1[0]] == 1){
            mp["Comp"].push_back(getNode(dir1.substr(0,1),"+C"+dir1.substr(0,1)+first+turn1+routerNo));
            mp[dir1.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));

        }
        if(dirGuid[dir2[0]] == 1){
            mp["Comp"].push_back(getNode(dir2.substr(0,1),"+C"+dir2.substr(0,1)+first+turn1+routerNo));
            mp[dir2.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");

        if(first != "L"){
            mp["Comp"].push_back(getNode("L","-CL"+first+turn2+routerNo));//local is always present
            insertOrder.push_back("L");
            mp["L"].push_back(getNode("st","+retComp"+first+turn2+routerNo));

            if(dirGuid[dir3[0]] == 1){
                mp["Comp"].push_back(getNode(dir3.substr(0,1),"-C"+dir3.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir3.substr(0,1));
                mp[dir3.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir4[0]] == 1){
                mp["Comp"].push_back(getNode(dir4.substr(0,1),"-C"+dir4.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir4.substr(0,1));
                mp[dir4.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir5[0]] == 1){
                mp["Comp"].push_back(getNode(dir5.substr(0,1),"-C"+dir5.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir5.substr(0,1));
                mp[dir5.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }


        }else{

            if(dirGuid['E'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+second+first+turn2+routerNo));
                insertOrder.push_back(second);
                mp[second].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid['W'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+third+first+turn2+routerNo));
                insertOrder.push_back(third);
                mp[third].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid['N'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fourth+first+turn2+routerNo));
                insertOrder.push_back(fourth);
                mp[fourth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid['S'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fifth+first+turn2+routerNo));
                insertOrder.push_back(fifth);
                mp[fifth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }



        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn3+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        if(dirGuid[dir6[0]] == 1){
            mp["Comp"].push_back(getNode(dir6.substr(0,1),"+C"+dir6.substr(0,1)+first+turn3+routerNo));
            mp[dir6.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));

        }
        if(dirGuid[dir7[0]] == 1){
            mp["Comp"].push_back(getNode(dir7.substr(0,1),"+C"+dir7.substr(0,1)+first+turn3+routerNo));
            mp[dir7.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }




}

void Compute(int no, string first, string second, string third, string fourth, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    map<char,int> dirGuid;
    dirGuid['E'] = 0, dirGuid['W'] = 0,dirGuid['N'] = 0, dirGuid['S'] = 0;
    if(first == "E" || second == "E" || third == "E" || fourth == "E" /*|| fifth == "E" */){
        dirGuid['E'] = 1;
    }

    if(first == "W" || second == "W" || third == "W" || fourth == "W" /*|| fifth == "W" */){
        dirGuid['W'] = 1;
    }

    if(first == "N" || second == "N" || third == "N" || fourth == "N" /*|| fifth == "N" */){
        dirGuid['N'] = 1;
    }

    if(first == "S" || second == "S" || third == "S" || fourth == "S" /*|| fifth == "S" */){
        dirGuid['S'] = 1;
    }

    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn1+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        if(dirGuid[dir1[0]] == 1){
            mp["Comp"].push_back(getNode(dir1.substr(0,1),"+C"+dir1.substr(0,1)+first+turn1+routerNo));
            mp[dir1.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));

        }
        if(dirGuid[dir2[0]] == 1){
            mp["Comp"].push_back(getNode(dir2.substr(0,1),"+C"+dir2.substr(0,1)+first+turn1+routerNo));
            mp[dir2.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");

        if(first != "L"){
            mp["Comp"].push_back(getNode("L","-CL"+first+turn2+routerNo));//local is always present
            insertOrder.push_back("L");
            mp["L"].push_back(getNode("st","+retComp"+first+turn2+routerNo));

            if(dirGuid[dir3[0]] == 1){
                mp["Comp"].push_back(getNode(dir3.substr(0,1),"-C"+dir3.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir3.substr(0,1));
                mp[dir3.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir4[0]] == 1){
                mp["Comp"].push_back(getNode(dir4.substr(0,1),"-C"+dir4.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir4.substr(0,1));
                mp[dir4.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir5[0]] == 1){
                mp["Comp"].push_back(getNode(dir5.substr(0,1),"-C"+dir5.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir5.substr(0,1));
                mp[dir5.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }


        }else{

            if(dirGuid[second[0]] == 1 ){
                mp["Comp"].push_back(getNode(second+"0","-C"+second+first+turn2+routerNo));
                insertOrder.push_back(second);
                mp[second].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[third[0]] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+third+first+turn2+routerNo));
                insertOrder.push_back(third);
                mp[third].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[fourth[0]] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fourth+first+turn2+routerNo));
                insertOrder.push_back(fourth);
                mp[fourth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }
            /*
            if(dirGuid['S'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fourth+first+turn2+routerNo));
                insertOrder.push_back(fourth);
                mp[fourth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }
            */


        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn3+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        if(dirGuid[dir6[0]] == 1){
            mp["Comp"].push_back(getNode(dir6.substr(0,1),"+C"+dir6.substr(0,1)+first+turn3+routerNo));
            mp[dir6.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));

        }
        if(dirGuid[dir7[0]] == 1){
            mp["Comp"].push_back(getNode(dir7.substr(0,1),"+C"+dir7.substr(0,1)+first+turn3+routerNo));
            mp[dir7.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }





}

void Compute(int no, string first, string second, string third, int router, int n){
    map<string, vector<node *> > mp;
    vector<string> insertOrder;
    string routerNo = to_string(router);
    map<char,int> dirGuid;
    dirGuid['E'] = 0, dirGuid['W'] = 0,dirGuid['N'] = 0, dirGuid['S'] = 0;
    if(first == "E" || second == "E" || third == "E" /*|| fourth == "E" || fifth == "E" */){
        dirGuid['E'] = 1;
    }

    if(first == "W" || second == "W" || third == "W" /*|| fourth == "W" /*|| fifth == "W" */){
        dirGuid['W'] = 1;
    }

    if(first == "N" || second == "N" || third == "N" /*|| fourth == "N" /*|| fifth == "N" */){
        dirGuid['N'] = 1;
    }

    if(first == "S" || second == "S" || third == "S" /*|| fourth == "S" /*|| fifth == "S" */){
        dirGuid['S'] = 1;
    }

    string nextRouter;
    string turn1,turn2,turn3;
    string adjRouter;
    string dir1,dir2,dir3,dir4,dir5,dir6,dir7;
    if(first == "L"){

        turn1 = "";
        turn2 = "";
        turn3 = "";
        dir1 = "Ee";
        dir2 = "Ww";
        dir3 = "Nn";
        dir4 = "Ss";
    }

    if(first == "E"){
        nextRouter = to_string(router+1);
        turn1 = "sw";
        turn2 = "w";
        turn3 = "nw";
        adjRouter = "W";
        dir1 = "Wsw";
        dir2 = "Sws";
        dir3 = "Ww";
        dir4 = "Nwn";
        dir5 = "Sws";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }
    if(first == "W"){
        nextRouter = to_string(router-1);
        turn1 = "se";
        turn2 = "e";
        turn3 = "ne";
        adjRouter = "E";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ee";
        dir4 = "Nen";
        dir5 = "Ses";
        dir6 = "Ene";
        dir7 = "Nen";

    }
    if(first == "N"){
        nextRouter = to_string(router-n);
        turn1 = "es";
        turn2 = "s";
        turn3 = "ws";
        adjRouter = "S";
        dir1 = "Ese";
        dir2 = "Ses";
        dir3 = "Ese";
        dir4 = "Wsw";
        dir5 = "Ss";
        dir6 = "Wsw";
        dir7 = "Sws";

    }
    if(first == "S"){
        nextRouter = to_string(router+n);
        turn1 = "en";
        turn2 = "n";
        turn3 = "wn";
        adjRouter = "N";
        dir1 = "Ene";
        dir2 = "Nen";
        dir3 = "Ene";
        dir4 = "Wnw";
        dir5 = "Nn";
        dir6 = "Wnw";
        dir7 = "Nwn";

    }



    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn1+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn1+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        if(dirGuid[dir1[0]] == 1){
            mp["Comp"].push_back(getNode(dir1.substr(0,1),"+C"+dir1.substr(0,1)+first+turn1+routerNo));
            mp[dir1.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));

        }
        if(dirGuid[dir2[0]] == 1){
            mp["Comp"].push_back(getNode(dir2.substr(0,1),"+C"+dir2.substr(0,1)+first+turn1+routerNo));
            mp[dir2.substr(0,1)].push_back(getNode("st","+retComp"+first+turn1+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    {
        mp.clear();
        insertOrder.clear();

        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn2+routerNo));

        insertOrder.push_back("Comp");

        if(first != "L"){
            mp["Comp"].push_back(getNode("L","-CL"+first+turn2+routerNo));//local is always present
            insertOrder.push_back("L");
            mp["L"].push_back(getNode("st","+retComp"+first+turn2+routerNo));

            if(dirGuid[dir3[0]] == 1){
                mp["Comp"].push_back(getNode(dir3.substr(0,1),"-C"+dir3.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir3.substr(0,1));
                mp[dir3.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir4[0]] == 1){
                mp["Comp"].push_back(getNode(dir4.substr(0,1),"-C"+dir4.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir4.substr(0,1));
                mp[dir4.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[dir5[0]] == 1){
                mp["Comp"].push_back(getNode(dir5.substr(0,1),"-C"+dir5.substr(0,1)+first+turn2+routerNo));
                insertOrder.push_back(dir5.substr(0,1));
                mp[dir5.substr(0,1)].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }


        }else{

            if(dirGuid[second[0]] == 1 ){
                mp["Comp"].push_back(getNode(second+"0","-C"+second+first+turn2+routerNo));
                insertOrder.push_back(second);
                mp[second].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid[third[0]] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+third+first+turn2+routerNo));
                insertOrder.push_back(third);
                mp[third].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }
            /*
            if(dirGuid[fourth[0]] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fourth+first+turn2+routerNo));
                insertOrder.push_back(fourth);
                mp[fourth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }

            if(dirGuid['S'] == 1){
                mp["Comp"].push_back(getNode(second+"0","-C"+fourth+first+turn2+routerNo));
                insertOrder.push_back(fourth);
                mp[fourth].push_back(getNode("st","+retComp"+first+turn2+routerNo));
            }
            */


        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }
    if(first != "L"){
        mp.clear();
        insertOrder.clear();
        insertOrder.push_back("st");
        mp["st"].push_back(getNode("Comp","+Comp"+first+turn3+routerNo));

        insertOrder.push_back("Comp");
        mp["Comp"].push_back(getNode("L0","-CL"+first+turn3+routerNo));//local is always present
        mp["L0"].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        if(dirGuid[dir6[0]] == 1){
            mp["Comp"].push_back(getNode(dir6.substr(0,1),"+C"+dir6.substr(0,1)+first+turn3+routerNo));
            mp[dir6.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));

        }
        if(dirGuid[dir7[0]] == 1){
            mp["Comp"].push_back(getNode(dir7.substr(0,1),"+C"+dir7.substr(0,1)+first+turn3+routerNo));
            mp[dir7.substr(0,1)].push_back(getNode("st","+retComp"+first+turn3+routerNo));
        }

        AdjacencyListTo_GraphGenerator(mp,insertOrder);
    }





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
            Compute(no,params[0],params[1],params[2],router,n);//compute m/c generator called
            ArbiterBuilder(no,params[0],params[1],params[2],router,n);//Arbiter generator called
            PriorityBuilder(no,params[0],router);//priority machine builder called;

        }
        else if(no == 4){
            Buffer(no,params[0],router,n);
            SwitchBuilder(no,params[0],params[1],params[2],params[3],router,n);//switch generator called
            Compute(no,params[0],params[1],params[2],params[3],router,n);//compute m/c generator called
            ArbiterBuilder(no,params[0],params[1],params[2],params[3],router, n);//Arbiter generator called
            PriorityBuilder(no,params[0],router);//priority machine builder called;

        }
        else if(no == 5){
            Buffer(no,params[0],router,n);
            SwitchBuilder(no,params[0],params[1],params[2],params[3],params[4],router,n);//switch generator called
            Compute(no,params[0],params[1],params[2],params[3],params[4],router,n);//compute m/c generator called
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
    freopen("DynamicXYTestMachines/testDy_3_3.txt", "w+", stdout);
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
