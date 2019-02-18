#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
	private:
		//Add class members and methods	
		TreeNode * root;
		

	public:
		
		string hufftable[256];

		HuffTree(){
			for(int i=0; i<256; i++){
				hufftable[i] = "";
			}	
		}

		//build a hiffman  tree  give a minheap
		void buildTree(MinHeap * mh);

		//generate codes by traversing the huffman tree
		//and store them in an internal data structure (array of strings for example)
		void generateCodes();

		//returns root of the tree
		TreeNode * getRoot(){
			return this->root;
		}

		void Visit(TreeNode * p, string s);

		//returns huffman code from the ascii code
		string getCharCode(unsigned int c);

		~HuffTree(){
			deleteNode(this->root);
			delete this->root;
		}
		void deleteNode(TreeNode* n){
			if(n->getLeft()!=NULL){
				deleteNode(n->getLeft());
				delete n->getLeft();
			}
			if(n->getRight()!=NULL){
				deleteNode(n->getRight());
				delete n->getRight();
			}
		}

};


#endif
