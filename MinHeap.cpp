#include <iostream>
#include <climits>

#include "MinHeap.h"



//implement the methods in MinHeap.h

MinHeap::MinHeap()
{
	this->n = 0;
}

void MinHeap::insert(TreeNode * val)
{
	myHeap.push_back(val);
	n++;
	int child = n - 1;
	int parent = (((child)-1)/2);
	while(child > 0){
		if(myHeap[child]->getFrequency() >= myHeap[parent]->getFrequency()){
			break;			
		}
		swap(myHeap[child],myHeap[parent]);
		child = parent;
		parent = (((child)-1)/2);
	}
}

int MinHeap::getSize()
{
	return n;
}

TreeNode * MinHeap::removeMin()
{
	if(n<=0)return NULL;
	TreeNode* minKey = myHeap[0];
	n--;
	if(n==0){
		myHeap.pop_back();
		return minKey;
	}
	myHeap[0] = myHeap[n];
	myHeap.pop_back();
	int parent = 0;
	int left = (2*(parent)+1);
	int right = (2*(parent)+2);
	while(left < n){
		int minChild = left;
		if(right < n && myHeap[right]->getFrequency() <= myHeap[left]->getFrequency()){
			if(myHeap[right]->getFrequency()==myHeap[left]->getFrequency()){
				minChild = left;
			}
			else
			minChild = right;
		}
		if((myHeap[parent]->getFrequency()) <= (myHeap[minChild]->getFrequency())){
			break;
		}
		swap(myHeap[minChild],myHeap[parent]);
		parent = minChild;
		left = 2*parent + 1;
		right = 2*parent + 2;
	}	
	return minKey;
	

}



