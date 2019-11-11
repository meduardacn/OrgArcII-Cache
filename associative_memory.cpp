//Compile: g++ associative_memory.cpp -o associative_memory
//Run: ./associative_memory <cache size> <words per blocks> <word size> <pathways>



#include <iostream>
#include <fstream>
#include <math.h> 
#include <bitset>
using namespace std;






int main(int argc, char** argv)
{
    if(argc < 4)
        cout<<"few arguments provided, it needs four"<<endl;


    int cache_size = (int) *argv[1] - 48;     //convert char to int
    int words_per_block = (int) *argv[2]- 48; //convert char to int
    int word_size = (int) *argv[3]- 48;       //convert char to int
    int pathways = (int) *argv[4]- 48;        //convert char to int
    


    
    int lines = cache_size/(words_per_block * word_size); // calculate number of lines
    int * ass_mem = new int[lines]; 
    int ** cache = new int* [lines];
    for (int i=0; i<lines; i++)
        cache[i] = new int[words_per_block];
    

    int word_rep_size = ceil(log2(words_per_block)); //bits needed to represent a word index
    int ass_set_size = ceil(log2(pathways)); // bits needed to represent associative set
    int tag_rep_size = 32 - (word_rep_size + ass_set_size);// number of bits represent tag

    int tag;
    int ass_set;
    int word_ind;
    int file_line;
    int add;
    int beg_ass_set;
    ifstream inFile;


    
    inFile.open("saida.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> file_line) 
    {
        add = file_line;
        tag = add>>(32 - tag_rep_size); 


        ass_set = add<<tag_rep_size;
        ass_set >>= tag_rep_size+word_rep_size;
        ass_set &=  (unsigned char)(pow(2,ass_set_size) - 1);


        word_ind = add<<tag_rep_size+ass_set_size;
        word_ind >>= tag_rep_size+ass_set_size;
        word_ind &= (unsigned char) (pow(2, word_rep_size) - 1);

        //cout<< bitset<16>(pow(2,ass_set_size) - 1)<<endl;
        cout<<"add: "<< bitset<16>(add)<<"  tag: "<< bitset<16>(tag)<<"  ass set: "<<bitset<16>(ass_set)<<
        "  word: "<<bitset<16>(word_ind) <<"\n"<<endl;

        beg_ass_set = (lines/pathways);
        cout<<"beg_ass_set: "<<beg_ass_set<<endl;
        
    }
    
    inFile.close();
    return 0;
}
