#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <fstream>
#include <bitset>
#include "HuffTree.h"
#include "MinHeap.h"


using namespace std;



class Decoder
{
	private:
		unsigned frequency_table[256];
		HuffTree* ht;
		ifstream infile;
		string s;
		// You need to add more class memeber and methods

	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		Decoder(string huff_file_path){
			this->s = huff_file_path;
			buildFrequencyTableFromFile();
		}

		//Fills up the frequency_table array where frequency_table[i]
		//will contain the frequency of char with ASCII code i
		//This method will read the header of the encoded file to
		//extract the chars and their frequency
		void buildFrequencyTableFromFile(){
			for(int i=0; i<256; i++){
				frequency_table[i] = 0;
			}
			infile.open(s,ios::in|ios::binary);
			unsigned int u = 0;
			unsigned int c = 0;
			unsigned int f = 0;			
			if(infile.is_open()){
				infile.read((char*)&u, 2);
				for(int i=0; i<u; i++){
					infile.read((char*)&c, 1);
					infile.read((char*)&f, 4);
					frequency_table[c] = f;
					
				}
			}
		}

		//Creates a min-heap and builds the Huffman tree
		void decode(){
			MinHeap* mh = new MinHeap();
			TreeNode* n;
			for(int i=0; i<256; i++){
				if(frequency_table[i]!=0){
					n = new TreeNode(i,frequency_table[i]);
					mh->insert(n);
				}
			}
			ht = new HuffTree();
			ht->buildTree(mh);
			delete mh;
		}

		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string file_path){
			ofstream outfile(file_path, ios::out);
			TreeNode* root = ht->getRoot();
			int totalChars = root->getFrequency();
			unsigned char body;
			while(!infile.eof()){
				infile.read((char*)&body,1);
				bitset<8> b(body);		
				for(int i=7; i>=0; i--){
					if(totalChars<=0)break;
					if(root->isLeafNode()){
						outfile << root->getVal();
						totalChars--;	
						root = ht->getRoot();
					}
					if(b[i]==0){
						root = root->getLeft();				
					}
					if(b[i]==1){
						root = root->getRight();
					}
				
				}	
			}
			outfile.close();
			infile.close();
		}
		~Decoder(){
			delete this->ht;
		}

};

#endif
