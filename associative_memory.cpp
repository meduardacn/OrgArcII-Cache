//Compile: g++ associative_memory.cpp -o associative_memory
//Run: ./associative_memory <cache size> <words per blocks> <word size> <pathways>



#include <iostream>

using namespace std;



struct line 
{
    unsigned char valid_bit;
    unsigned char* tag;
    unsigned char* data;

}Line;



int main(int argc, char argv[])
{
    int cache_size = argv[1];
    int words_per_block = argv[2];
    int word_size = argv[3];
    int pathways = argv[4];
    
    int n_linhas = cache_size/(words_per_block * word_size);
    
    return 0;
}
