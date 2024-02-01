// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    if(root!=nullptr)
    {
        clear(root);
    }
}

// recursive helper for destructor
void IntBST::clear(Node *n) {

    if(n->left!=nullptr)
    {
        clear(n->left);
    }

    if(n->right!=nullptr)
    {
        clear(n->right);
    }

    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(root == nullptr)
    {
        root = new Node(0);
        root->info = value;
        return true;
    }

    return insert(value, root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    
    if(value < n->info)
    {
        if(n->left==nullptr)
        {
            Node* temp = new Node(value);
            temp->parent = n;
            n->left = temp;
            return true;
        }
        return insert(value, n->left);
    }

    if(value > n->info)
    {
        if(n->right==nullptr)
        {
            Node* temp = new Node(value);
            temp->parent = n;
            n->right = temp;
            return true;
        }
        return insert(value, n->right);
    }

    return false;

}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n==nullptr){return;}
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(n==nullptr){return;}
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(n==nullptr){return;}
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n==nullptr){return 0;}
    return n->info+sum(n->left)+sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n==nullptr){return 0;}
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n==nullptr){ return NULL; }
    if(value < n->info){ return getNodeFor(value, n->left); }
    if(value > n->info){ return getNodeFor(value, n->right); }
    return n;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != NULL;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* temp = getNodeFor(value, root);
    if(temp==nullptr){return nullptr;}

    if(temp->left!=nullptr){
        temp = temp->left;
        while(temp->right!=nullptr){
            temp = temp->right;
        }
        return temp;
    }

    if(temp->parent!=nullptr){
        if(temp->parent->info < temp->info){
            return temp->parent;
        }
        if(temp->parent->info > temp->info){
            temp = temp->parent;
            while(temp->parent!=nullptr){
                if(temp->info < value){
                    return temp;
                }
                temp = temp->parent;
            }
            return nullptr;
        }
    }

    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* temp = getPredecessorNode(value);
    if(temp==nullptr)
    {
        return 0;
    }
    return temp->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* temp = getNodeFor(value, root);
    if(temp==nullptr){return nullptr;}

    if(temp->right!=nullptr){
        temp = temp->right;
        while(temp->left!=nullptr){
            temp = temp->left;
        }
        return temp;
    }

    if(temp->parent!=nullptr){
        if(temp->parent->info > temp->info){
            return temp->parent;
        }
        if(temp->parent->info < temp->info){
            temp = temp->parent;
            while(temp->parent!=nullptr){
                if(temp->info > value){
                    return temp;
                }
                temp = temp->parent;
            }
            return nullptr;
        }
    }

    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* temp = getSuccessorNode(value);
    if(temp==nullptr)
    {
        return 0;
    }
    return temp->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){

    Node* temp = getNodeFor(value, root);

    if(temp==nullptr)
    {
        return false;
    }

    if(temp->left==nullptr && temp->right==nullptr)
    {
        if(temp->parent==nullptr)
        {
            root = nullptr;
            delete temp;
            return true;
        }

        if(temp->parent->info > temp->info){
            temp->parent->left = nullptr;
        }
        else{
            temp->parent->right = nullptr;
        }
        delete temp;
        return true;
    }

    if(temp->left == nullptr)
    {
        if(temp==root)
        {
            root = root->right;
            root->parent = nullptr;
        }
        else if(temp->parent->left == temp)
        {
            temp->parent->left = temp->right;
            temp->right->parent = temp->parent;
        }
        else
        {
            temp->parent->right = temp->right;
            temp->right->parent = temp->parent;
        }

        delete temp;
        return true;
    }

    if(temp->right == nullptr)
    {
        if(temp==root)
        {
            root = root->left;
            root->parent = nullptr;
        }
        else if(temp->parent->left == temp)
        {
            temp->parent->right = temp->right;
            temp->right->parent = temp->parent;
        }
        else
        {
            temp->parent->right = temp->left;
            temp->left->parent = temp->parent;
        }

        delete temp;
        return true;
    }

    Node* next = getSuccessorNode(temp->info);
    
    int tval = 0;
    tval = temp->info;
    temp->info = next->info;
    next->info = tval;
    
    if(next->parent->right == next)
    {
        next->parent->right = next->right;
        next->right->parent = next->parent;
    }
    else
    {
        next->parent->left = next->right;
        if(next->right != nullptr)
        {
            next->right->parent = next->parent;
        }
    }

    delete next;
    return true;
}