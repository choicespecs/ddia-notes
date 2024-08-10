#pragma once

#include <string>

struct Node 
{
    std::string key;
    std::string value;
    int height;
    Node * left;
    Node * right;

    Node(const std::string k, const std::string v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree 
{
    private:
        Node* root;

        int getHeight(Node* node);
        int getBalanceFactor(Node* node);
        Node* rotateRight(Node* y);
        Node* rotateLeft(Node* x);
        Node* insert(Node* node, const std::string key, const std::string value);

    public:
        AVLTree(); 

        void insert(const std::string key, const std::string value);
        const std::string getValue(const std::string key) const;
        const std::string getSmallerValue(const std::string key) const;
};


