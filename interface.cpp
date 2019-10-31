// c++ - std = c++ 11 - stdlib = libc++ interface.cpp - o interface
// ./interface < values.txt
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

typedef tuple<string, int, int,int > myTuple;
vector< myTuple > memory;

void handle(string input){
    string delimiter = ":";
    size_t pos = input.find(delimiter);
    string token = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());

    if (token == "ep"){
        // ep endereço do final do programa
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        int value = stoi(token);
        memory.resize(value);

        // tuple<string, int, int, int> tp("ep", value,0,0);
        // memory[value] = tp
        // cout << get<0>(tp)  << endl;
        // cout << memory.size() << endl;
    }
    else if (token == "ji"){
        // ji define um saldo incondicional
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());
        int adr = stoi(token);
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        int tgt = stoi(token);
        tuple<string, int, int, int> tp("ji", adr, tgt, NULL);
        memory[adr] = tp;
    }
    else if (token == "bi"){
        // bi define um salto condicional.
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());
        int adr = stoi(token);
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());
        int tgt = stoi(token);
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        int pbd = stoi(token);
        tuple<string, int, int, int> tp("bi", adr, tgt, pbd);
        memory[adr] = tp;
    }
}

void readInput(){
    string input;
    while(getline(cin, input)){
        handle(input);
    }
}

void printVector(){
    for (int i = 0; i < memory.size(); i++){
        cout << get<0>(memory[i]) << " "<< get<1>(memory[i]) << " " << get<2>(memory[i]) << " " << get<3>(memory[i])  << endl;
    }
}
int main(){
    readInput();
    // printVector();
    return 0;
}