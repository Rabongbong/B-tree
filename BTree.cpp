// Please implement most of your source codes here. 
#include <iostream>
#include "BTree.h"
using namespace std;


BTreeNode::BTreeNode(){}

int BTreeNode::get_order(){
  return order;
}

void BTreeNode::set_order(int order){      // 몇 개가 들어가있는지 정하기
  this->order=order;
}

void BTreeNode::set_type(NodeType type){
  this->type = type;
}

void BTreeNode::add_order(){
  order++;
}

BTree::BTree() {
  root = new BTreeInternalNode;
  root->set_type(ROOT);
}

BTree::~BTree() {}

BTreeInternalNode::BTreeInternalNode(){
  this->type = INTERNAL;
  keys[NUM_KEYS]={0, }; 
}

void BTreeInternalNode::make_child(int a, BTreeNode * node){
  this -> child[a] = node;
}

BTreeInternalNode::~BTreeInternalNode(){}


BTreeLeafNode::BTreeLeafNode(){
  
  this -> type = LEAF;
  keys[NUM_KEYS]={0, };
	right_sibling;
}


BTreeLeafNode::~BTreeLeafNode(){}


void BTreeInternalNode::insert_key(int a, long long value){
  this -> keys[a]=value;
}

void BTreeLeafNode::insert_key(int a, long long value){
  this -> keys[a]=value;
}

long long BTreeInternalNode::get_key(int a){
  return keys[a];
}

BTreeNode * BTreeInternalNode::get_child(int a){
  return child[a];
}

void BTreeLeafNode::make_sibling(BTreeLeafNode* leafNode){
  right_sibling = leafNode;
}

BTreeLeafNode* BTreeLeafNode::get_sibling(){
  return  this->right_sibling;
}



void BTree::insert(long long value){
  
  if(root -> get_order() == 0){
    BTreeNode * node= new BTreeNode();
    node = root;
    node -> insert_key(node ->get_order(), value);
    node -> add_order();
    root = node;
  }
  else{   // part 3      1. root만 존재       2. insert 공간이 없어서 split해야 할 때               3. 
    BTreeNode * node = root;
    BTreeNode * temp;
    BTreeNode * leaf1 = new BTreeLeafNode();
    BTreeNode * leaf2 = new BTreeLeafNode();

    cout << node ->get_order() << '\n';
    if(node->get_order() < NUM_KEYS-1 && !node->get_child(0)){   // 1-1. root만 존재
      for(int i = 0; i<=node->get_order(); i++){
        if(value < node ->get_key(i) && i!=node->get_order()){
          for(int j = node->get_order(); i<j; j--){
            node->insert_key(j, node->get_key(j-1));
          }
          node->insert_key(i,value);
          break;
        }
        else if(i==node->get_order()){
          node->insert_key(i,value);
        }
      }
    }
    else if(node->get_order() == NUM_KEYS-1 && !node->get_child(0)){   // 1-2. root 분해 
      for(int i = 0; i<=node->get_order(); i++){
        if(value < node ->get_key(i) && i!=node->get_order()){
          for(int j = node->get_order(); i<j; j--){
            node->insert_key(j, node->get_key(j-1));
          }
          node->insert_key(i,value);
        }else if(i==node->get_order()){
          node->insert_key(i,value);
        }
      }
      for(int i=0; i< NUM_KEYS/2; i++)
        leaf1 ->insert_key(i, node->get_key(i));
      leaf1 -> make_sibling(leaf2); 
    }
    else{
      while(node->getNodeType()!=LEAF){
        temp =  node;
        for(int i=0; i<node->get_order(); i++){
          if(value < node->get_key(i) && node->get_child(i)){
            node = node -> get_child(i);
            break;
          }
          if(i== node->get_order()-1){

          }
      }
    }
    }
    



  node -> add_order();
    root = node;
  }
  cout << root->get_key(0) <<  '\n'  << root->get_key(1) << '\n'  << root->get_key(2) << '\n'  << root->get_key(3) << '\n';
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