#include <iostream>

/*
 * BTreeNode Class: This class represens a node in the B-tree.
 * Each node has an array of keys (int *keys), an array of pointers to child nodes (BTreeNode **children)
 * the number of keys currently stored in the node (int t), anda  flag indicating whether the node is a leaf (bool leaf)
 */
class BTreeNode 
{
    int *keys;
    int t;
    BTreeNode **children;
    int n;
    bool leaf;

public:
    BTreeNode(int _t, bool _leaf);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    friend class BTree;
};

/*
 * BTree Class
 * This class represents the B-tree structure. It has a root node and a degree of t.
 */
class BTree 
{
    BTreeNode *root;
    int t;

public:
    // Initializes an empty B-tree. If the tree is empty, it creates a root node and sets the first key.
    BTree(int _t) 
    {
        root = nullptr;
        t = _t;
    }

    void insert(int k);
    void traverse()
    {
        if (root != nullptr)
            root->traverse();
    }
};

/*
 * BTreeNode constructor
 * The constructor intiializes the node with the specified minimum degree t and leaf status.
 * It allocates memory for the array keys and children based on the degree t.
 */
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    t = _t;
    leaf = _leaf;
    keys = new int[2 * t - 1];
    children = new BtreeNode * [2 * t];
    n = 0;
}

/*
 * This function traverses the B-tree printing the keys in ascending order. It does this by moving through the child nodes and keys in each node.
 */
void BTreeNode::traverse() 
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!leaf)
            children[i]->traverse();
        std::cout << " " << keys[i];
    }
    if (!leaf)
        children[i]->traverse();
}

/*
 * This function inserts a key k into the B-Tree. If the root is full (has 2 * t - 1 keys), it first creates a new root and then splits the old root.
 * Otherwise, it calls the insertNonFull function on the root.
 */
void BTree::insert(int k)
{
    if (root == nullptr)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else 
        {
            root->insertNonFull(k);
        }
    }
}

/*
 * This function is used to insert a key k into a non-full node. If the node is a leaf, it finds the correct position for the key and inserts it.
 * If the node is not a leaf and has a full child, it splits the child before inserting the key.
 */
void BTreeNode::insertNonFull(int k)
{
    int i = n - 1;
    if (leaf)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && key[i] > k)
            i--;
        if (children[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

/*
 * This function is used to split a full child node y of the current node at index i. 
 * It creates a new node z, moves key and children from y to z, and then updates the current node.
 */
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];
    children[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n = n + 1;
}

