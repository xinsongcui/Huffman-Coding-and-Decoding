#include <iostream>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

void printHelp(){
	cout << "Invalid arguments." << endl;
	cout << "Type \"huffman [mode] [arguments]\" where mode and its arguments are one of the following:" << endl;
	cout << "-e [src] [dest]: encode the source file and place the result into the specified destination" << endl;
	cout << "-d [src] [dest]: decode the source file and place the result into the specified destination" << endl;
	exit(1);
}


int main (int argc, char** argv){
	string mode = string(argv[1]);
	if(mode == "-e"){
		string fileName = string(argv[2]);
		string destName = string(argv[3]);
		Encoder* e = new Encoder(fileName);
		e->encode();
		e->writeEncodedFile(destName);
		//delete e;
	}
	else if(mode == "-d"){
		string sfile = string(argv[2]);
		string dfile = string(argv[3]);
		Decoder* d = new Decoder(sfile);
		d->decode();
		d->writeUncompressedFile(dfile);
		delete d;
	}
	
	else printHelp();
	return 0;
}
