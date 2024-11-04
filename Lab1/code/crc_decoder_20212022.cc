#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <sstream>
#include <cmath>
using namespace std;

ifstream in;
ofstream out,result;
string Gen="",Binary="";
int gen_size;
char Data;

int M_2_D(string T);

int main(int argc, char *argv[]){
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  if(argc != 6){
    cout<<"usage: ./crc_decoder input_file output_file result_file generator dataword_size\n";
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

  result.open(argv[3],ios::out | ios::binary); //result file
  if(!result.is_open()){
    cout<<"result file open error.\n";
    exit(0);
  }

  int data_size = atoi(argv[5]); //dataword_size

  if(data_size != 4 && data_size != 8){
    cout<<"dataword size must be 4 or 8.\n";
    exit(0);
  }

  Gen = argv[4]; //generator
  gen_size = Gen.size(); //generator size

  //str to binary
  while(in.get(Data)){ 
    bitset<8>bi(Data);
    Binary+=bi.to_string();
  }

  //delete padding bit
  int del=0;
  for(int i=7;i>=0;i--){
    if(Binary[7-i]=='1'){
      del+=pow(2,i);
    }
  }

  Binary.erase(0,8+del);

  string data="";
  string outdata="";

  //decode bits
  int code_num=0;
  int error_num=0;

  int code = data_size+gen_size-1;
  for(int i=0;i<Binary.size();i+=code){
    data = Binary.substr(i,data_size);
    outdata += data;
    data = Binary.substr(i,code);
    error_num += M_2_D(data);
    code_num++;
  }

  for(int i=0;i<outdata.size();i+=8){
    string tmp = outdata.substr(i,8);
    bitset<8>op(tmp);
    out << char(op.to_ulong());
  }

  result<<code_num<<" "<<error_num;
  
  in.close();
  out.close();
  result.close();
  return 0;
}

int M_2_D(string T){
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

  if(remind.compare("000")) return 1;
  else return 0;
}
