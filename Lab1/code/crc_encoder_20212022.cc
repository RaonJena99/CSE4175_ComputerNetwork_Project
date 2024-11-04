#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <sstream>
using namespace std;

ifstream in;
ofstream out;
string Gen="",Binary="";
int gen_size;
char Data;

string M_2_D(string T);

int main(int argc, char *argv[]){
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  if(argc != 5){
    cout<<"usage: ./crc_encoder input_file output_file generator dataword_size\n";
    exit(0);
  }

  in.open(argv[1],ios::in | ios::binary); //input file
  if(!in.is_open()){
    cout<<"input file open error.\n";
    exit(0);
  }

  out.open(argv[2],ios::out | ios::binary); //output file
  if(!out.is_open()){
    cout<<"output file open error.\n";
    exit(0);
  }

  int data_size = atoi(argv[4]); //dataword_size

  if(data_size != 4 && data_size != 8){
    cout<<"dataword size must be 4 or 8.\n";
    exit(0);
  }

  Gen = argv[3]; //generator
  gen_size = Gen.size(); //generator size

  //str to binary
  while(in.get(Data)){ 
    bitset<8>bi(Data);
    Binary+=bi.to_string();
  }

  string data="";
  string outdata="";

  //make codeword
  for(int i=0;i<Binary.size();i+=data_size){
    data = Binary.substr(i,data_size);
    outdata += M_2_D(data);
  }

  int pad = 8 - (outdata.size()%8); //get padding bit size
  bitset<8>padbit(pad);
  string padding = padbit.to_string(); // get padding_count bit
  outdata.insert(0,string(pad,'0')); //add '0'bits
  outdata.insert(0,padding); //add padding bit size

  for(int i=0;i<outdata.size();i+=8){
    string tmp = outdata.substr(i,8);
    bitset<8>op(tmp);
    out << char(op.to_ulong());
  }
  
  in.close();
  out.close();
  return 0;
}

string M_2_D(string T){
  string D = T;
  T.append(gen_size-1, '0'); //add '0' bit
  string remind = T.substr(0,gen_size); //initialize reminder

  int t=T.size();
  int i=gen_size;
  while (i < t){
    if(remind[0]== '0'){ 
      remind.erase(0,1);
      remind.push_back(T[i++]);
    }

    if(remind[0]=='0') continue;
    if(i>t) break;
    
    for(int j=0;j<gen_size;j++) 
      remind[j] = (remind[j] == Gen[j])?'0':'1'; //XOR operation
  }
  remind.erase(0,1);

  return D+remind;
}
