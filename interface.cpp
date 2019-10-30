#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void handle(){

}
int main(){
    // read input
    string input;
    int flag = 1;
    while(flag){
        getline(cin, input);
        handle();
        cout << input << endl;
        if(input  == "//"){
            flag = 0;
        }
    }
}