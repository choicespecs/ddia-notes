#include "avltree.h"

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::getHeight(Node* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(AVLTree::getHeight(y->left), AVLTree::getHeight(y->right));
    x->height = 1 + std::max(AVLTree::getHeight(x->left), AVLTree::getHeight(x->right));
    
    return x;
}

Node* AVLTree::rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* AVLTree::insert(Node* node, const std::string key, const std::string value)
{
    if (node == nullptr)
        return new Node(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        return node;

    node->height = 1 + std::max(AVLTree::getHeight(node->left), AVLTree::getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) 
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(const std::string key, const std::string value)
{
    root = insert(root, key, value);
}

const std::string AVLTree::getSmallerValue(const std::string key) const
{
    std::string result = "";

    Node* current = root;
    while (current != nullptr)
    {
        if (current->key < key)
        {
            result = current->key;
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return result;
}

const std::string AVLTree::getValue(const std::string key) const
{
    Node* current = root;
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current->value;
        }
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return "";
}
