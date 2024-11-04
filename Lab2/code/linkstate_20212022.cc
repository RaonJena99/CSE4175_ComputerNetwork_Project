#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define PAIR pair<int,int>
#define INF (~0U >> 2)

priority_queue <PAIR,vector<PAIR>,greater<PAIR> > Q;
vector <vector<PAIR> > T(101);
vector <int> Visit(101);
int Node[101][101][2];

fstream topology, message, change, output;
int Src, Des, Cost;
size_t Count;
size_t i, j, t;

void Creating_Graph();
void Init_Table();
void Searching_Route();
void Save_Route();

int main(int argc, char* argv[]){
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  if(argc != 4){
    cout<<"usage: linkstate topologyfile messagesfile changesfile\n";
    return 0;
  }
  //input file
  topology.open(argv[1],ios::in); 
  message.open(argv[2],ios::in);
  change.open(argv[3],ios::in);
  output.open("output_ls.txt",ios::out);

  if(!topology.is_open() || !message.is_open() || !change.is_open()){
    cout<<"Error: open input file.\n";
    return 0;
  }

  Creating_Graph();
  Searching_Route();
  Save_Route();
  message.close(); 


  while(change>>Src>>Des>>Cost){
    message.open(argv[2],ios::in);
    int chk=0;
    if(Cost == -999) Cost = INF;

    for(i=0; i<T[Src].size();i++){
      if(T[Src][i].first == Des){
        T[Src][i].second = Cost;
        chk=1;
      }
    }
    if(!chk) T[Src].push_back(make_pair(Des,Cost));
    chk=0;
    
    for(i=0; i < T[Des].size();i++){
      if(T[Des][i].first == Src){
        T[Des][i].second = Cost;
        chk=1;
      }
    }
    if(!chk) T[Des].push_back(make_pair(Src,Cost));

    Searching_Route();
    Save_Route();
    message.close(); 
  }
  cout<<"Complete. Output file written to output_ls.txt.\n";

  topology.close(); 
  change.close(); 
  output.close();
  return 0;
}

void Creating_Graph(){
  topology>>Count;

  while(topology>>Src>>Des>>Cost){
    T[Src].push_back(make_pair(Des, Cost));
    T[Des].push_back(make_pair(Src, Cost));
  }
}

void Searching_Route(){
  Init_Table();

  for(t=0; t<Count; t++){
    int flag = 0;
    fill(Visit.begin(),Visit.end(),0);

    Q.push(make_pair(0,t));

    while(!Q.empty()){
      int idx = Q.top().second;
      Q.pop();
      if(Visit[idx]) continue;
      else Visit[idx]++;

      for(i=0;i<T[idx].size();i++){
        int K = T[idx][i].first;

        if(!Visit[K]){
          int tmp = Node[t][idx][0] + T[idx][i].second;
          if(tmp < Node[t][K][0]){
            Node[t][K][0] = tmp;
            if(!flag) Node[t][K][1] = K;
            else Node[t][K][1] = Node[t][idx][1];
            Q.push(make_pair(Node[t][K][0],K));
          }
        }
      }
      flag++;
    }

    for(j=0; j<Count; j++)
      if(Node[t][j][0] != INF) output<<j<<" "<<Node[t][j][1]<<" "<<Node[t][j][0]<<"\n";
    output<<"\n";
  }
}

void Save_Route(){
  string line;
  
  while (getline(message, line)){
    stringstream ss1,ss2;
    string tmp, message;
    int from,to;
    tmp = line.substr(0,1);
    ss1 << tmp; ss1 >> from;
    tmp = line.substr(2,3);
    ss2 << tmp; ss2 >> to;
    message = line.substr(4);

    if (Node[from][to][0] != INF) {
      output<<"from "<<from<<" to "<<to<<" cost "<<Node[from][to][0]<<" hops ";
      while(from != to){
        output<<from<<" ";
        from = Node[from][to][1];
      }
      output<<message<<"\n";
    }
    else{
      output<<"from "<<from<<" to "<<to<<" cost infinite hops unreachable message ";
      output<<message<<"\n";
    }
  }
  output<<"\n";
}

void Init_Table(){
  for(i=0;i<Count;i++){
    for(j=0;j<Count;j++){
      Node[i][j][0] = (i == j) ? 0 : INF;
      Node[i][j][1] = (i == j) ? j : -1;
    }
  }
}