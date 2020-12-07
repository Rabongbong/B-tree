// Please implement most of your source codes here. 

#include <iostream>
#include "BTree.h"
using namespace std;






int BTreeNode::get_order(){
  return order;
}

void BTreeNode::set_order(int order){
  this->order=order;
}

void BTreeNode::add_order(){
  order++;
}

BTree::BTree() {
  root = NULL;
}

BTree::~BTree() {}

BTreeInternalNode::BTreeInternalNode(){

  this->type = INTERNAL;
  keys[NUM_KEYS]={0, }; 
  child[NUM_KEYS+1];
}

BTreeLeafNode::BTreeLeafNode(){
  
  this -> type = LEAF;
  keys[NUM_KEYS]={0, };
	right_sibling;
}

void BTreeInternalNode::BTreeinsert(int a, long long value){
  keys[a]=value;
}

void BTreeLeafNode::BTreeinsert(int a, long long value){
  keys[a]=value;
}



void BTree::insert(long long value){
  
  
  long long keys[NUM_KEYS];
  BTreeNode *child[NUM_KEYS+1];
  int full;

  if(root ->get_order()==0){
    root = new BTreeNode;
    
  }
  else{
    for(int i=0; i<NUM_KEYS; i++){
      if(value < keys[i]){
        
      }
    }
  }
}


void BTree::printLeafNode(long long value){


}

void BTree::pointQuery(long long value){


}


void BTree::rangeQuery(long long low, long long high){

}


NodeType BTreeNode::getNodeType(){
  return type;
}