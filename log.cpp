// g++ -std=c++11 log.cpp -o log
// ./log 

#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <stdlib.h>
#include <fstream>

    using namespace std;
// <hit, miss>
tuple <int, int> CL1(0,0);
tuple <int, int> CL2(0,0);
tuple <int, int> CL3(0,0);
tuple <int, int> MR(0,0);
tuple <int, int> HD(0,0);

int number_accesses;
int total_sum_penalties;

int main(){
    string file_line;
    ifstream inFile;
    ofstream outFile;

    remove("final.txt");
    outFile.open("final.txt");

    inFile.open("output.txt");
    if (!inFile){
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (inFile >> file_line){
        if(file_line != "//") outFile << file_line;
        outFile << "\n";

        string delimiter = ":";
        size_t pos = file_line.find(delimiter);
        string str = file_line.substr(0, pos);
        file_line.erase(0, pos + delimiter.length());

        string mem_type;
        int penalty;

        if (str == "hit"){
            pos = file_line.find(delimiter);
            mem_type = file_line.substr(0, pos);
            file_line.erase(0, pos + delimiter.length());

            if (mem_type == "CL1") get<0>(CL1)++;
            else if (mem_type == "CL2") get<0>(CL2)++;
            else if (mem_type == "CL3") get<0>(CL3)++;
            else if (mem_type == "MR") get<0>(MR)++;
            else if (mem_type == "HD") get<0>(HD)++;

            pos = file_line.find(delimiter);
            str = file_line.substr(0, pos);
            penalty = stoi(str);
            total_sum_penalties += penalty;
            number_accesses++;
            outFile << "\n";
        } else 
        if (str == "miss")  {
            pos = file_line.find(delimiter);
            mem_type = file_line.substr(0, pos);
            file_line.erase(0, pos + delimiter.length());
            number_accesses++;
            int value;
            if(mem_type == "CL1") get<1>(CL1)++;
            else if (mem_type == "CL2") get<1>(CL2)++;
            else if (mem_type == "CL3") get<1>(CL3)++;
            else if (mem_type == "MR") get<1>(MR)++;
        }
    }

    outFile  << "\n";
    int hit,miss,all_access;
    outFile << "CL1: " << (100 * get<0>(CL1)) / (get<1>(CL1) + get<0>(CL1)) << "%% hit";
    outFile << " ("<< get<0>(CL1) <<") - ";
    outFile << (100 * get<1>(CL1)) / (get<1>(CL1) + get<0>(CL1)) << "%% miss";
    outFile << " (" << get<1>(CL1) << ") \n";

    outFile << "CL2: " << (100 * get<0>(CL2)) / (get<1>(CL2) + get<0>(CL2)) << "%% hit";
    outFile << " (" << get<0>(CL2) << ") - ";
    outFile << (100 * get<1>(CL2)) / (get<1>(CL2) + get<0>(CL2)) << "%% miss";
    outFile << " (" << get<1>(CL2) << ") \n";

    outFile << "CL2: " << (100 * get<0>(CL3)) / (get<1>(CL3) + get<0>(CL3)) << "%% hit";
    outFile << " (" << get<0>(CL3) << ") - ";
    outFile << (100 * get<1>(CL3)) / (get<1>(CL3) + get<0>(CL3)) << "%% miss";
    outFile << " (" << get<1>(CL3) << ") \n";

    outFile << "MR: " << (100 * get<0>(MR)) / (get<1>(MR) + get<0>(MR)) << "%% hit";
    outFile << " (" << get<0>(MR) << ") - ";
    outFile << (100 * get<1>(MR)) / (get<1>(MR) + get<0>(MR)) << "%% miss";
    outFile << " (" << get<1>(MR) << ") \n";

    outFile << "HD: " << (100 * get<0>(HD)) / (get<1>(HD) + get<0>(HD)) << "%% hit";
    outFile << " (" << get<0>(HD) << ") - ";
    outFile << (100 * get<1>(HD)) / (get<1>(HD) + get<0>(HD)) << "%% miss";
    outFile << " (" << get<1>(HD) << ") \n";

    outFile << "\n";
    outFile << "Average access time: " << total_sum_penalties/number_accesses << endl;
    outFile << "Total execution time: " << total_sum_penalties << endl;
    outFile << "\n";

    inFile.close();
    return 0;
}