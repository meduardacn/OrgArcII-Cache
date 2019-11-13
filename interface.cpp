// g++ -std=c++11 interface.cpp -o interface
// ./interface <values.txt>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <stdlib.h>

using namespace std;

typedef tuple<string, int, int,int > myTuple;
vector< myTuple > memory;

ifstream inFile;
ofstream outFile;

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

void readInput(char** argv){
    remove("saida.txt");
    outFile.open("trace.txt");
    inFile.open(argv[1]);

    if (!inFile){
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    string input;
    while (inFile >> input){
        handle(input);
    }
}

void printVector(){
    for (int i = 0; i < memory.size(); i++){
        cout << get<0>(memory[i]) << " "<< get<1>(memory[i]) << " " << get<2>(memory[i]) << " " << get<3>(memory[i])  << endl;
    }
}

void trace(){
    bool next  = true;
    int pos = 0;
    while(next){
        string type = get<0>(memory[pos]);
        if(type == "ji"){
            outFile << pos << endl;
            pos = get<2>(memory[pos]);
            //cout << get<1>(memory[pos]) << " -> " << get<2>(memory[pos]) << endl;
        }else if(type == "bi"){
            outFile << pos << endl;
            int random = rand()  % 100 + 1;
            int prob = get<3>(memory[pos]);
            //FIXME: saltar ou não de acordo com essa probabilidade 
            if(random > prob ){
                pos += 1;
            }else{
                pos = get<2>(memory[pos]);
            }
        }else{
            outFile << pos << endl;
            pos += 1;
        }
        //FIXME: testar se de fato isso faz parar
        if(pos > memory.size()){
            next = false;
        }
    }
}

int main(int argc, char** argv){
    readInput(argv);
    // printVector();
    trace();
    return 0;
}