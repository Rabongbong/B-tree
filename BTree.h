// Note: You need to add additional member variables and functions as you need.

#define NUM_KEYS 10 
// NUM_KEYS should be set to make each tree node as large as 4KB. 
// But for this assignment, we will set the degree of node small to make debugging and grading easy
// Please do not change this number. 
// In practice, DBMS employs 'slotted page structure' to store variable-length records in B+tree.
// But the purpose of this assignment is to make students familiar with B-tree itself. 


enum NodeType{
	ROOT,  
	INTERNAL,
	LEAF
};



class BTreeNode{   
  protected:
	NodeType type;  // type.ROOT , type.INTERVAL, type.LEAF
	int order;
  public:
	BTreeNode();
	virtual ~BTreeNode() {}
	NodeType getNodeType() {return type;}
	void set_type(NodeType type);
	int get_order();
	void set_order(int order);
  void add_order();    
	//virtual void connect(BTreeNode* node);
	virtual void insert_key(int a, long long value) {}
	virtual long long get_key(int a) {return 0;}
	virtual BTreeNode * get_child(int a) {return 0;}
	virtual void make_child(int a, BTreeNode* node) {}
};



class BTreeInternalNode:public BTreeNode{  // 상속  NodeType
	private:
	long long keys[NUM_KEYS];
	BTreeNode* child[NUM_KEYS+1];
  public:
	BTreeInternalNode();
	~BTreeInternalNode();
	void insert_key(int a, long long value);    // insert key
	long long get_key(int a);
	BTreeNode * get_child(int a);
	void make_child(int a, BTreeNode* node);   // point to child
};


class BTreeLeafNode:public BTreeNode{    // 상속  NodeType
	private:
	long long keys[NUM_KEYS];
	BTreeLeafNode* right_sibling;
  public:
	BTreeLeafNode();
	~BTreeLeafNode();
	//void connect(BTreeLeafNode* node) override;
	void insert_key(int a, long long value);  // insert key
	long long get_key(int a);
	void printLeafNode(long long value); // print all keys in the current leaf node, separated by comma.
};



class BTree{  
  private:
	BTreeNode *root;
  public:
	// You are not allowed to change the interfaces of these public methods.
	BTree(); 
	~BTree(); 
	void insert(long long value);  
	//void remove(long long value);
	void printLeafNode(long long value);
	// find the leaf node that contains 'value' and print all values in the leaf node.
	void pointQuery(long long value); 
	// print the found value or "NOT FOUND" if there is no value in the index
	void rangeQuery(long long low, long long high); 
	// print all found keys (low <= keys < high), separated by comma (e.g., 10, 11, 13, 15\n) 
	void make_internal(BTreeNode * parent, BTreeNode * leaf, long long value);
	BTreeNode * find_parent(BTreeNode * child);
};

