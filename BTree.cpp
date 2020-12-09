// Please implement most of your source codes here. 
#include <iostream>
#include "BTree.h"
using namespace std;



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

BTree::BTree() {
  root = new BTreeLeafNode;
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

// void BTreeLeafNode::connect(BTreeLeafNode* node){
//   right_sibling = node;
// }

void BTree::insert(long long value){

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
    //cout << node -> getNodeType() <<'\n';
    // cout << "type: " << node ->getNodeType() << '\n';
    // cout << root->getNodeType() << '\n';
    // cout << root->get_key(0) << '\n';
    //cout << root->get_child(0)->get_key(0) << '\n';
    //cout << '%';

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
    // cout << "===================" <<'\n';
    // for(int i = 0; i< node ->get_order(); i++)
    //   cout << node->get_key(i) << '\n';
    // cout << "===================" <<'\n';
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

      //cout << '2' << '\n';
      node -> add_order();
      //cout << root ->get_order() <<'\n';
    }
    else{         // split
      j = 0;
      //cout << '3' << '\n';
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

      // for(int i=0; i<11; i++)
      //   cout << temp[i] << '\n';
      
      num = (NUM_KEYS/2) + 1;   // 6
      node -> set_order(0);
      for(int i = 0; i<num; i++){
        //cout << '4' << '\n';
        node -> insert_key(i, temp[i]);
        node ->add_order();
      }

      for(int i = num; i < NUM_KEYS; i++){
        //cout << '5' << '\n';
        node -> insert_key(i, 0);
      }

      for(int i=0; i<5; i++){
        //cout << '6' << '\n';
        new_node -> insert_key(i, temp[6+i]); 
        new_node -> add_order();
      }

      if(node ->getNodeType() == root->getNodeType()){
        BTreeInternalNode * internal_node = new BTreeInternalNode();
        internal_node -> set_type(ROOT);
        internal_node -> insert_key(0, new_node->get_key(0));
        //node -> connect(new_node);
        internal_node -> make_child(0, node);
        internal_node -> make_child(1, new_node);
        internal_node -> add_order();
        root = internal_node;
        // cout << root ->get_key(0) << '\n';
        // cout << root->getNodeType();
        // for(int i=0; i < root->get_child(0) ->get_order(); i++)
        //   cout << root->get_child(0) ->get_key(i) << '\n';
        // cout << "---------------" <<'\n';
        // for(int i=0; i < root->get_child(1) ->get_order(); i++)
        //   cout << root->get_child(1) ->get_key(i) << '\n';
      }
      else{
        // cout << '8' << '\n';
        // for(int i=0; i<node->get_order(); i++)
        //   cout << node->get_key(i) <<'\n';
        // for(int i=0; i<new_node->get_order(); i++)
        //   cout << new_node->get_key(i) <<'\n';
        make_internal(parent, new_node, new_node->get_key(0));
      }
    }
  }
}


void BTree::make_internal(BTreeNode * parent, BTreeNode * child, long long value){
  
  int M;
  int j = 0;
  int flag = 0;
  long long k;
  // cout << parent ->get_order();
  // cout << parent->get_key(0);
  // cout << parent->get_key(1);
  // cout << value;
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
    // for(int i=0; i< num; i++){
    //   parent ->get_child(i)->connect(parent ->get_child(i+1));
    // }
    parent->add_order();
    // for(int i=0; i<parent->get_order(); i++)
    //   cout << parent->get_key(i) <<'\n';
  }
  else{  // split
  cout << '*' << '\n';
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
        point[j] = parent->get_child(j);
        j++;
      }
      if(flag ==0)
        temp[10]=value;
      point[11] = parent->get_child(j);

      M = (NUM_KEYS/2) ;   // 5
      parent -> set_order(0);
      for(int i = 0; i<M; i++){
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
      new_internal ->make_child(11, point[11]);

      if(parent ->getNodeType() == root ->getNodeType()){
        cout << '*' << '\n';
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
  //cout << root->get_child(0)->get_key(0) << '\n';
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
  value =  child ->get_key(0);
  while(node -> getNodeType() != LEAF){
    temp = node;
    for(int i=0; i<node->get_order(); i++){
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
  cout << "-=-=-=-=-" << temp ->get_key(0) << "-=-=-=-=-" << '\n' ;
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
  while(node->getNodeType() != LEAF){

    for(int i=0; i<node->get_order(); i++){
      if( low <= node->get_key(i) && node->get_key(i) <= high){
          node = node -> get_child(i);
          break;
      }
      if(i == node -> get_order()-1){
        node = node -> get_child(i+1);   // 가장 바깥쪽으로 간다.
        break;
      }
    }
  }
}
