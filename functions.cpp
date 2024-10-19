/*This file contains function helpfull for functioningof other files
Function declared here rarelly changes
This file also contains important files to #include*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include<algorithm>
#include<bits/stdc++.h>

using namespace std;




string getString(char c){
  string s(1,c) ;
  return s ;
}

string intToStringHex(int x,int fill = 5){
  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string temp = s.str();
  temp = temp.substr(temp.length()-fill,fill);
  transform(temp.begin(), temp.end(),temp.begin(),::toupper);
  return temp;
}

string expandString(string data,int length,char fillChar,bool back=false){
  if(back){
    if(length<=data.length()){
      return data.substr(0,length);
    }
    else{
      for(int i = length-data.length();i>0;i--){
        data += fillChar;
      }
    }
  }
  else{
    if(length<=data.length()){
      return data.substr(data.length()-length,length);
    }
    else{
      for(int i = length-data.length();i>0;i--){
        data = fillChar + data;
      }
    }
  }
  return data;
}
int stringHexToInt(string x){
  return stoul(x,nullptr,16);
}

string stringToHexString(const string& input){
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}



void splitString(string& input, char delimiter, string* output, int& count) {
    std::stringstream ss(input);
    std::string token;
    count = 0;
    while (std::getline(ss, token, delimiter)) {
        output[count++] = token;
    }
}

int checkSign(string& input) {
    for (char c : input) {
        if (c == '+') {
            return 1;
        } else if (c == '-') {
            return 0;
        }
    }
    return -1;
}

string getStringBeforeComma(string& input) {
    std::string result;
    bool commaFound = false;
    for (char c : input) {
        if (c == ',') {
            commaFound = true;
            break;
        }
        result += c;
    }
    if (!commaFound) {
        result = input; // No comma found, return the entire input string
    }
    return result;
}










bool checkWhiteSpace(char x){
  if(x==' ' || x=='\t'){
    return true;
  }
  return false;
}

bool checkCommentLine(string line){
  if(line[0]=='.'){
    return true;
  }
  return false;
}

bool if_all_num(string x){
  bool all_num = true;
  int i = 0;
  while(all_num && (i<x.length())){
    all_num &= isdigit(x[i++]);
  }
  return all_num;
}

void readFirstNonWhiteSpace(string line,int& index,bool& status,string& data,bool readTillEnd=false){
  data = "";
  status = true;
  if(readTillEnd){
    data = line.substr(index,line.length() - index);
    if(data==""){
      status = false;
    }
    return;
  }
  while(index<line.length()&&!checkWhiteSpace(line[index])){//If no whitespace then data
    data += line[index];
    index++;
  }

  if(data==""){
    status = false;
  }

  while(index<line.length()&&checkWhiteSpace(line[index])){//Increase index to pass all whitespace
    index++;
  }
}

void readByteOperand(string line,int& index,bool& status,string& data){
  data = "";
  status = true;
  if(line[index]=='C'){
    data += line[index++];
    char identifier = line[index++];
    data += identifier;
    while(index<line.length() && line[index]!=identifier){//Copy all data until next identifier regardless of whitespace
      data += line[index];
      index++;
    }
    data += identifier;
    index++;//Shift to next of identifier
  }
  else{
    while(index<line.length()&&!checkWhiteSpace(line[index])){//In no whitespace then data
      data += line[index];
      index++;
    }
  }

  if(data==""){
    status = false;
  }

  while(index<line.length()&&checkWhiteSpace(line[index])){//Increase index to pass all whitespace
    index++;
  }
}

void writeToFile(ofstream& file,string data,bool newline=true){
  if(newline){
    file<<data<<endl;
  }else{
    file<<data;
  }
}

string getRealOpcode(string opcode){
  if(opcode[0] == '+' || opcode[0] == '@'){
    return opcode.substr(1,opcode.length() - 1);
  }
  return opcode;
}

char getFlagFormat(string data){
  if(data[0] == '#' || data[0] == '+' || data[0] == '@' || data[0] == '='){
    return data[0];
  }
  return ' ';
}

class EvaluateString{
public:
  int getResult();
  EvaluateString(string data);
private:
  string storedData;
  int index;
  char peek();
  char get();
  int term();
  int factor();
  int number();
};

EvaluateString::EvaluateString(string data){
  storedData = data;
  index=0;
}

int EvaluateString::getResult(){
  int result = term();
  while(peek()=='+' || peek() == '-'){
    if(get() == '+'){
      result += term();
    }else{
      result -= term();
    }
  }
  return result;
}

int EvaluateString::term(){
  int result = factor();
  while(peek() == '*' || peek() == '/'){
    if(get()=='*'){
      result *= factor();
    }
    else{
      result /= factor();
    }
  }
  return result;
}

int EvaluateString::factor(){
  if(peek() >= '0' && peek() <= '9'){
    return number();
  }
  else if(peek() == '('){
    get();
    int result = getResult();
    get();
    return result;
  }
  else if(peek()=='-'){
    get();
    return -factor();
  }
  return 0;
}

int EvaluateString::number(){
  int result = get() - '0';
  while(peek() >= '0' && peek() <= '9'){
    result = 10*result + get()-'0';
  }
  return result;
}

char EvaluateString::get(){
  return storedData[index++];
}

char EvaluateString::peek(){
  return storedData[index];
}


