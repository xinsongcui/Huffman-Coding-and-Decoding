#include <iostream>
#include "HuffTree.h"

void HuffTree::buildTree(MinHeap * mh){
	while(mh->getSize()>1){
		
		TreeNode * T1 = mh->removeMin();
		int f1 = T1->getFrequency();
		TreeNode * T2 = mh->removeMin();
		int f2 = T2->getFrequency();
		TreeNode * T = new TreeNode(0,f1+f2);
		T->join(T2,T1);
		mh->insert(T);
	}
	this->root = mh->removeMin();
}

void HuffTree::generateCodes(){
	TreeNode * temp = root;
	string temps = "";
	Visit(temp,temps);
	delete temp;
}

void HuffTree::Visit(TreeNode* p, string s){
	if(p->isLeafNode()){
		int temp = int(p->getVal());
		hufftable[temp] = s;
	}
		if(p->getLeft()!=NULL){
			string sl = s + '0';	
			Visit(p->getLeft(),sl);
		}
		if(p->getRight()!=NULL){
			string sr = s + '1';
			Visit(p->getRight(),sr);
		}
}

string HuffTree::getCharCode(unsigned int c){
	return hufftable[c];
}
