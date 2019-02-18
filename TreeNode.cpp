#include <iostream>
#include "TreeNode.h"

#include <string>


TreeNode::TreeNode(unsigned char val, unsigned int frequency)
{
	this->val = val;
	this->frequency = frequency;
	this->left = NULL;
	this->right = NULL;
}

unsigned int TreeNode::getFrequency()
{
	return this->frequency;
}
unsigned char TreeNode::getVal()
{
	return this->val;
}
