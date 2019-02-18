#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <vector>

#define ileft(p) (2*(p)+1)
#define iright(p) (2*(p)+2)
#define iparent(ch) (((ch)-1)/2)

using namespace std;

class MinHeap
{
	private:
		vector<TreeNode*> myHeap;  
		int n; 
	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap(){};
};

#endif
