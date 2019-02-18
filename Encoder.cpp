#include <iostream>
#include "Encoder.h"

using namespace std;


void Encoder::encode(){
	buildFrequencyTable();
	MinHeap* mh = new MinHeap();
	TreeNode* n;
	for(int i=0;i<256; i++){
		if(frequency_table[i]!=0){
			n = new TreeNode(i,frequency_table[i]);
			mh->insert(n);
		}
	}
	huf = new HuffTree();
	huf->buildTree(mh);
	huf->generateCodes();
	delete  mh;
}

void Encoder::writeEncodedFile(string output_file_path){

	//write on file
	FILE* fOut = fopen(output_file_path.c_str(),"w");
	unsigned int Unichars = 0;
	string cbuffer;
	unsigned w;
	unsigned z;		
	unsigned x;
	unsigned y;
	

	//write header 	
	for(int i=0; i<256; i++){
		if(huf->getCharCode(i).compare("")!=0){
			Unichars++;
		}
	}
	fwrite(&Unichars,1,1,fOut);
	if(Unichars==256)w=1;
	else if(Unichars<256)w=0;
	fwrite(&w,1,1,fOut);	
	for(unsigned j=0; j<256; j++){
		if(huf->getCharCode(j).compare("")!=0){
			int k = 0;
			fwrite(&j,1,1,fOut);
			z = frequency_table[j];			
			while(k<4){
				unsigned hbuffer = z % 256;
				fwrite(&hbuffer,1,1,fOut);
				z = z / 256;
				k++;
			}
		}
	}
	//write body
	FILE* fin = fopen(s.c_str(),"r");
	while((x=fgetc(fin))!=EOF){
		cbuffer = cbuffer + huf->getCharCode(x);
		while(cbuffer.length()>=8){
			y = 0;
			for(int i=0; i<=7; i++){
				if(cbuffer[i]=='1') y|=(1 << (7-i));
			}
			fwrite(&y,1,1,fOut);
			cbuffer.erase(0,8);
		}
	}

	if(cbuffer.length()!=0){
		while(cbuffer.length()<8){
			cbuffer=cbuffer+"0";
		}
		y = 0;
		for(int i=0; i<=7; i++){
			if(cbuffer[i]=='1') y|=(1 << (7-i));	
		}
		fwrite(&y,1,1,fOut);
	}
	fclose(fin);
	fclose(fOut);
}
