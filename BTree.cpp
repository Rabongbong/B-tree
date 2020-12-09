// Please implement most of your source codes here. 
#include <iostream>
#include "BTree.h"
using namespace std;

long long data[100000000]={0, };

BTreeNode::BTreeNode(){}

int BTreeNode::get_order(){
  return order;
}

void BTreeNode::set_order(int order){      // 몇 개가 들어가있는지 정하기
  this->order = order;
}

void BTreeNode::set_type(NodeType type){
  this-> type = type;
}

void BTreeNode::add_order(){
  this -> order++;
}

void sort(long long value);
BTree::BTree() {
  root = new BTreeLeafNode();
  root->set_type(ROOT);
}

BTree::~BTree() {}

BTreeInternalNode::BTreeInternalNode(){
  type = INTERNAL;
  keys[NUM_KEYS]={0, }; 
}

void BTreeInternalNode::make_child(int a, BTreeNode* node){
  this->child[a] = node;
}

BTreeInternalNode::~BTreeInternalNode(){}

BTreeLeafNode::BTreeLeafNode(){
  type = LEAF;
  keys[NUM_KEYS]={0, };
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

long long BTreeLeafNode::get_key(int a){
  return keys[a];
}


void BTree::insert(long long value){

  sort(value);

  if(!root -> get_order()){
    BTreeNode * node = root;
    node -> set_type(LEAF);   // set LEAF
    node -> insert_key(node ->get_order(), value);
    node -> add_order();
    root = node;
  }
  else{    
    BTreeNode * node = new BTreeNode();
    node = root;
    BTreeNode * parent;
    BTreeInternalNode * new_node = new BTreeInternalNode();
    new_node ->set_type(LEAF);
    long long temp[NUM_KEYS+1];
    int j;
    int num;
    int flag = 0;

    while(node->getNodeType()!=LEAF){    // LEAF node의 depth로 들어간다.
      //cout << ')';
      parent = node;  // parent node
      //cout << '*';
      for(int i = 0; i < node->get_order(); i++){
        if(value < node->get_key(i)){
            node = node -> get_child(i);
            break;
        }
        if(i == node -> get_order()-1){
          node = node -> get_child(node->get_order());   // 가장 바깥쪽으로 간다.
          break;
        }
      }
    }
    if(node->get_order() < NUM_KEYS){           // root만 존재   or  leaf안에 insert 
      for(int i = 0; i <= node->get_order(); i++){
        if(value < node -> get_key(i) && i != node->get_order()){
          for(j = node->get_order(); i < j; j--){
            node->insert_key(j, node->get_key(j-1));
          }
          node->insert_key(i, value);
          break;
        }
        else if(i == node->get_order()){
          node->insert_key(i, value);
        }
      }
      node -> add_order();
    }
    else{         // split
      j = 0;
      for(int i = 0; i < node->get_order(); i++){
        if(value < node -> get_key(i) && flag == 0){
          temp[j] = value;
          j++;
          flag = 1;
        }
        temp[j] = node->get_key(i);
        j++;
      }
      if(flag ==0)
        temp[10]=value;
      
      num = (NUM_KEYS/2) + 1;   // 6
      node -> set_order(0);
      for(int i = 0; i<num; i++){
        node -> insert_key(i, temp[i]);
        node ->add_order();
      }

      for(int i = num; i < NUM_KEYS; i++){
        node -> insert_key(i, 0);
      }

      for(int i=0; i<5; i++){
        new_node -> insert_key(i, temp[6+i]); 
        new_node -> add_order();
      }

      if(node ->getNodeType() == root->getNodeType()){
        BTreeInternalNode * internal_node = new BTreeInternalNode();
        internal_node -> set_type(ROOT);
        internal_node -> insert_key(0, new_node->get_key(0));
        internal_node -> make_child(0, node);
        internal_node -> make_child(1, new_node);
        internal_node -> add_order();
        root = internal_node;
      }
      else{
        make_internal(parent, new_node, new_node->get_key(0));
      }
    }
  }
}

void sort(long long value){
  
  int j=0;
  int chg = 0;

  if(data[0]==0){
    data[0]=value;
    return;
  }
  while(1){
    if(data[j]==0)
      break;
    j++;
  }

  for(int i=0; i < j; i++){
    if(value <=data[i]){
      for(int k = j-1; i <= k; k--)
        data[k+1]=data[k];
      data[i]=value;
      chg=1;
      break;
    }
  }
  if(chg==0)
    data[j] = value;
}




void BTree::make_internal(BTreeNode * parent, BTreeInternalNode * child, long long value){
  
  int M;
  int j = 0;
  int flag = 0;
  long long k;
  if(parent -> get_order() < NUM_KEYS){
    for(int i = 0; i <=parent -> get_order(); i++){
      if(value < parent ->get_key(i) && i !=parent -> get_order()){
        for(int m = parent -> get_order(); i < m; m--){
          //cout << '*' << '\n';
          parent -> insert_key(m, parent->get_key(m-1));
          parent -> make_child(m+1, parent->get_child(m));
        };
       //cout << '*' << '\n';
        parent -> insert_key(i, value);
        parent -> make_child(i+1, child);
        break;
      }
      else if(i == parent -> get_order()){
        //cout << '*' << '\n';
        parent -> insert_key(i, value);
        parent -> make_child(i+1, child);
      }
    }
    parent->add_order();
  }
  else{  // split
  BTreeInternalNode * new_internal = new BTreeInternalNode();
  new_internal ->set_type(INTERNAL);
  long long temp[NUM_KEYS+1];
  BTreeNode* point[NUM_KEYS+2];
      for(int i = 0; i < parent -> get_order(); i++){
        if(value < parent -> get_key(i) && flag == 0){
          temp[j]=value;
          point[j]=child;
          j++;
          flag = 1;
        }
        temp[j] = parent->get_key(i);
        point[j] = parent->get_child(i);
        j++;
      }
      if(flag == 0){
        temp[10]=value;
        point[10] = parent->get_child(10);
        point[11] = child;
      }
      else{
        point[11] = parent->get_child(10);
      }
      M = (NUM_KEYS/2) ;   // 5
      parent -> set_order(0);
      for(int i = 0; i < M; i++){
        parent -> insert_key(i, temp[i]);
        parent ->make_child(i, point[i]);
        parent ->add_order();
      }
      parent ->make_child(5, point[5]);
      k = parent -> get_key(5);
      for(int i = M; i<NUM_KEYS; i++){
        parent -> insert_key(i, 0);

      }
      for(int i=0; i<5; i++){
        new_internal -> insert_key(i, temp[6+i]); 
        new_internal ->make_child(i, point[6+i]);
        new_internal -> add_order();
      }
      new_internal ->make_child(5, point[11]);

      if(parent == root ){
        //cout << '*' << '\n';
        BTreeInternalNode * internal_node = new BTreeInternalNode();
        internal_node -> set_type(ROOT);
        internal_node -> insert_key(0, k);
        internal_node -> make_child(0, parent);
        internal_node -> make_child(1, new_internal);
        internal_node -> add_order();
        root = internal_node;
      }
      else{
        make_internal(find_parent(parent), new_internal, k);
      }
  }
}

void BTree::printLeafNode(long long value){
  
  BTreeNode * node = root;
  int chg = 0;
  while(node->getNodeType() != LEAF){
    for(int i=0; i<node->get_order(); i++){
      if(value < node->get_key(i)){
          node = node -> get_child(i);
          break;
      }
      if(i == node -> get_order()-1){
        node = node -> get_child(i+1);   // 가장 바깥쪽으로 간다.
        break;
      }
    }
  }
  for(int i=0; i < node -> get_order(); i++){
    if(value == node->get_key(i)){
      chg = 1;
      break;
    }
    chg = 0;
  }
  if(chg == 1){
    for(int i=0; i< node -> get_order()-1; i++)
      cout << node->get_key(i) << ", ";
    cout << node->get_key(node->get_order()-1);
  }
  else{
    cout << "NOT found";
  }
  cout << '\n';
}

BTreeNode* BTree:: find_parent(BTreeNode * child){

  BTreeNode * node = root;
  BTreeNode * temp;
  long long value;
  temp = node;
  while(node -> getNodeType() != LEAF){
    temp = node;
    for(int i = 0; i < node->get_order(); i++){
      if(value < node->get_key(i)){
          node = node -> get_child(i);
          break;
      }
      if(i == node -> get_order()-1){
        node = node -> get_child(node -> get_order());   // 가장 바깥쪽으로 간다.
        break;
      }
    }
    
  }
  return temp;
}

void BTree::pointQuery(long long value){

  BTreeNode * node = root;
  //cout << "==" << node ->getNodeType();
  while(node->getNodeType() != LEAF){
    for(int i=0; i<node->get_order(); i++){
      if(value < node->get_key(i)){
          node = node -> get_child(i);
          break;
      }
      if(i == node -> get_order()-1){
        node = node -> get_child(i+1);   // 가장 바깥쪽으로 간다.
        break;
      }
    }
  }
  for(int i=0; i< node->get_order(); i++){
    if(value == node->get_key(i)){
      cout << value << '\n';
      return;
    }
  }
  cout << "NOT FOUND" << '\n';
}

void BTree::rangeQuery(long long low, long long high){

  BTreeNode * node = root;
  BTreeNode * parent;
  BTreeNode* point[NUM_KEYS+1];
  int i=0;

  parent = node;
  for(int i=0; i<node->get_order(); i++)
    if( low <= node->get_key(i) && node->get_key(i) <= high){
      point[i] = node -> get_child(i);
    }  
  if(node -> get_child(10))
    point[10] =  node ->get_child(10);


  while(data[i]!=0){
    if(low <= data[i] && data[i] <=high)
      cout << ", " << data[i];
    i++;
  }
  cout << '\n';
}