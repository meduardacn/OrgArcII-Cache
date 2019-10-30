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

    cout << token << endl;
    if (token == "ep"){
        // ep endereço do final do programa
        pos = input.find(delimiter);
        token = input.substr(0, pos);
        int value = stoi(token);
        memory.resize(value);
        cout << "memory size";
        cout << value << endl;
    }
    else if (token == "ji"){
        // ji define um saldo incondicional
        
    }
    else if (token == "bi"){
        // bi define um salto condicional.
    }
    // while ((pos = input.find(delimiter)) != string::npos)
    // {
    //     token = input.substr(0, pos);
    //     cout << token << std::endl;
    //     input.erase(0, pos + delimiter.length());
    // }
}

void readInput(){
    string input;
    while (getline(cin, input) ){
        cout << input << endl;
        handle(input);
    }
}

int main(){
    readInput();
    return 0;
}