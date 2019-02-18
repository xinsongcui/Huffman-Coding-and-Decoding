#ifndef ENCODER_H
#define ENCODER_H


#include <string>
#include <fstream>
#include <sstream>
#include "HuffTree.h"
#include "MinHeap.h"

using namespace std;

class Encoder
{
	private:
		unsigned frequency_table[256];
		HuffTree* huf;
		string s;
		int max = 0;
		int flag = 0;

		// You need to add more class memeber and methods
	public:
		//test_file_path is the input (decoded) file
		Encoder(string file_path){
			this->s = file_path;
		}

		//Fills up the frequency_table array where frequency_table[i]
		//will contain the frequency of char with ASCII code

		//void buildFrequencyTable();
		void buildFrequencyTable(){
			for(int a=0; a<256; a++){
				frequency_table[a]=0;
			}
			unsigned int a;
			FILE* infile = fopen(s.c_str(),"r");
			if(infile!=NULL){
				while((a=fgetc(infile))!=EOF){
					frequency_table[a]++;
					a = 0;
				}
				fclose(infile);
			}
		}
		//Builds the min head and run the encoding algorithm
		void encode();

		//Generates the encoded file and save it as output_file_path
		void writeEncodedFile(string output_file_path);
	
		~Encoder(){
			delete this->huf;
		}
};

#endif
