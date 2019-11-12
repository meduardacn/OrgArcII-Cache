//Compile: g++ associative_memory.cpp -o associative_memory
//Run: ./associative_memory <cache size> <words per blocks> <word size> <pathways>



#include <iostream>
#include <fstream>
#include <math.h> 
#include <bitset>
#include <stdio.h>
using namespace std;



int SUBSTITUTION = 0;


typedef struct ass_line
{
    unsigned char valid;
    int tag;
}Ass_line;





bool find (Ass_line* ass_mem, int beg, int end, int add, int word, int tag, int** cache)
{
    for(int i=beg; i<end; i++)
    {
        if(ass_mem[i].tag == tag && cache[i][word] == add) 
            return true;
            
    }
    return false;
}







void substitution(Ass_line* ass_mem, int beg, int end, int add, int word, int tag, int** cache, int words_per_block)
{
    int line = rand()%(end-beg + 1) + beg;
    ass_mem[line].tag = tag;
    cache[line][word] = add;

    int aux_index = word;
    int aux_add = add;
    while(aux_index > 0)
    {
        cache[line][--aux_index] = --aux_add;
        cout<<"armazenei "<<aux_add<<" na posiçao "<<line<<","<<aux_index<<endl;
    }

    aux_index = word;
    aux_add = add;
    while(aux_index < words_per_block - 1)
    {
        cache[line][++aux_index] = ++aux_add;
        cout<<"armazenei "<<aux_add<<" na posiçao "<<line<<","<<aux_index<<endl;
    }

    
    cout<<"armazenei "<<aux_add<<" na posiçao "<<line<<","<<word<<endl;
}

void insert(Ass_line* ass_mem, int beg, int end, int add, int word, int tag, int** cache, int words_per_block)
{
    for(int i=beg; i<end; i++)
    {
        if(ass_mem[i].valid == 0)//if a line with vaidation bit == 0 is finded then
        {                        //the address is saved in this line
            ass_mem[i].valid = 1;
            ass_mem[i].tag = tag;
            cache[i][word] = add;



            int aux_index = word;
            int aux_add = add;
            while(aux_index > 0)
            {
                cache[i][--aux_index] = --aux_add;
                cout<<"armazenei "<<aux_add<<" na posiçao "<<i<<","<<aux_index<<endl;
            }

            aux_index = word;
            aux_add = add;
            while(aux_index < words_per_block - 1)
            {
                cache[i][++aux_index] = ++aux_add;
                cout<<"armazenei "<<aux_add<<" na posiçao "<<i<<","<<aux_index<<endl;
            }



            cout<<"armazenei "<<add<<" na posiçao "<<i<<","<<word<<endl;
            return;
        }
    }
    substitution(ass_mem, beg, end, add, word, tag, cache, words_per_block);
}

















int main(int argc, char** argv)
{
    if(argc < 4)
        cout<<"few arguments provided, it needs four"<<endl;


    int cache_size;     
    int words_per_block; 
    int word_size ;       
    int pathways ;        
    cout << "Tamanho da cache: "<<endl;
    cin >> cache_size;
    cout << "Palavras por bloco: "<<endl;
    cin >> words_per_block;
    cout << "Tamanho da palavra: "<<endl;
    cin >> word_size;
    cout << "Vias: "<<endl;
    cin >> pathways;

    

    int lines = cache_size/(words_per_block * word_size); // calculate number of lines
    Ass_line* ass_mem = new Ass_line[lines]; 
    int ** cache = new int* [lines];
    for (int i=0; i<lines; i++)
        cache[i] = new int[words_per_block];
    

    for(int i=0; i<lines; i++)
    {
        ass_mem[i].valid = 0;
        ass_mem[i].tag = -1;
    }


    int word_rep_size = ceil(log2(words_per_block)); //bits needed to represent a word index
    int ass_set_size = ceil(log2(pathways)); // bits needed to represent associative set
    int tag_rep_size = 32 - (word_rep_size + ass_set_size);// number of bits represent tag

    int tag;
    int ass_set;
    int word_ind;
    int file_line;
    int add;
    int beg_ass_set;
    int end_ass_set;
    ifstream inFile;
    ofstream outFile;

    remove("output.txt");
    outFile.open("output.txt");


    
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

        //cout<<"add: "<< bitset<16>(add)<<"  tag: "<< bitset<16>(tag)<<"  ass set: "<<bitset<16>(ass_set)<<
        //"  word: "<<bitset<16>(word_ind) <<"\n"<<endl;

        beg_ass_set = (lines/pathways) * ass_set;
        end_ass_set = beg_ass_set + (lines/pathways);

        int random = rand()  % 100 + 1;
        if (find(ass_mem, beg_ass_set, end_ass_set, add, word_ind, tag, cache))
        {
            outFile << "hit : 1 \n";
        }
        else
        {
            int random = rand()  % 100 + 1;
            if(random <= 20)
            {
                outFile << "miss, CL2:10 \n";
                insert(ass_mem, beg_ass_set, end_ass_set, add, word_ind, tag, cache, words_per_block);
            }
            else
            {
                random = rand()  % 100 + 1;
                if(random <= 20)
                {
                    outFile << "miss, CL3:30 \n";
                    insert(ass_mem, beg_ass_set, end_ass_set, add,  word_ind, tag, cache, words_per_block);
                }
                else
                {
                    random = rand()  % 100 + 1;
                    if(random <= 40)
                    {
                        outFile << "miss, MR:100 \n";
                        insert(ass_mem, beg_ass_set, end_ass_set, add,  word_ind, tag, cache, words_per_block);
                    }
                    else
                    {
                        outFile << "miss, HD:1000 \n";
                        insert(ass_mem, beg_ass_set, end_ass_set, add,  word_ind, tag, cache, words_per_block);
                    }
                }
            }
            
        }

        //cout<<"beg_ass_set: "<<beg_ass_set<<endl;
        //cout<<"end_add_set: "<<end_ass_set<<endl;
        
    }
    
    inFile.close();
    return 0;
}
