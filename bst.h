#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}


template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}


template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}


template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}


template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}


template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}


template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/


template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); 
    virtual ~BinarySearchTree(); 
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); 
    void clear(); 
    void clear_Helper(Node<Key, Value>* node);
    bool isBalanced(); 
    bool isBalanced_Helper(Node<Key, Value>* node);
    int isBalanced_Height(Node<Key, Value>* node);
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
  
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    


protected:
    Node<Key, Value>* root_;
    
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    this->current_ = ptr;
}


template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    this->current_ = nullptr;

}


template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}


template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}


template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (this->current_ == rhs.current_) {
        return true;
    }
    else return false;
}


template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (this->current_ == rhs.current_) {
        return false;
    }
    else return true;
}



template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    this->current_ = BinarySearchTree<Key, Value>::successor(current_);
    
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(nullptr)
{

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    this->clear();
}
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return this->root_ == nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}


template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}


template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}


template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}


template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair) {
    if (this->empty()) { 
        this->root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    }
    else {
        Node<Key, Value>* node = this->root_;
        Node<Key, Value>* parent;

        while (node) { 
            parent = node;
            if (node->getKey() > keyValuePair.first) {
                node = node->getLeft();
            }
            else if (node->getKey() < keyValuePair.first) {
                node = node->getRight();
            }
            else {
                node->setValue(keyValuePair.second);
                return;
            }
        }
        if (parent->getKey() > keyValuePair.first) { //Right child
            parent->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
            parent->getLeft()->setParent(parent);
            parent->getLeft()->setLeft(nullptr);
            parent->getLeft()->setRight(nullptr);
        }
        else {
            parent->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent));
            parent->getRight()->setParent(parent);
            parent->getRight()->setLeft(nullptr);
            parent->getRight()->setRight(nullptr);
        }
    }
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key & key) {
    Node<Key, Value>* node = internalFind(key);

    if (!node) {
        return;
    }

    if (node->getLeft() != nullptr && node->getRight() != nullptr ) { //If node has two children
        nodeSwap(node, predecessor(node));
    }

    if (node->getLeft() != nullptr && node->getRight() == nullptr ) { //Only Left child
        if (node->getParent()) {
            Node<Key, Value>* parent = node->getParent();
            if (node->getParent()->getLeft() != node) {
                node->getParent()->setRight(node->getLeft());
                parent->getRight()->setParent(parent);
            } else {
                node->getParent()->setLeft(node->getLeft());
                parent->getLeft()->setParent(parent);
            }
        } else { //Must be the root node
            root_ = node->getLeft();
            node->getLeft()->setParent(NULL);
        }

        delete node;
        return;
    }

    if ( node->getLeft() == nullptr && node->getRight()) { //Only right child
        if (node->getParent()) {
            Node<Key, Value>* parent = node->getParent();
            if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(node->getRight());
                parent->getLeft()->setParent(parent);
            } else {
                node->getParent()->setRight(node->getRight());
                parent->getRight()->setParent(parent);
            }
        } else { //Must be the root node
            root_ = node->getRight();
            node->getRight()->setParent(nullptr);
        }

        delete node;
        return;
    }

    if (node->getLeft() == nullptr && node->getRight() == nullptr) { //Node has no children
        if (node->getParent()) {
            if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(nullptr);
            } else {
                node->getParent()->setRight(nullptr);
            }
        } else { 
            root_ = nullptr;
        }

        delete node;
        return;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    if (current->getLeft()) {
        current = current->getLeft();

        while (current->getRight()) {
            current = current->getRight();
        }

        return current;
    }
    else {
        if (current->getParent() == nullptr) {
            return nullptr;
        }

        while (current->getParent()) {
            if (current->getParent()->getRight() == current) {
                return current->getParent();
            }
            current = current->getParent();
        }

        return nullptr;
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    if (current->getRight()) {
        current = current->getRight();

        while (current->getLeft()) {
            current = current->getLeft();
        }

        return current;
    }
    else {
        Node<Key, Value>* buff = current->getParent();

        while (buff && current == buff->getRight()) {
            current = buff;
            buff = buff->getParent();
        }

        return buff;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    this->clear_Helper(this->root_);
    this->root_ = nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_Helper(Node<Key, Value>* node) {
    if (node){
        clear_Helper(node->getRight());
        clear_Helper(node->getLeft());
        delete node;
        node = nullptr;
    }
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    if (this->empty()) return nullptr;

    Node<Key, Value>* temp = this->root_;
    while (temp->getLeft() != nullptr) {
        temp = temp->getLeft();
    }

    return temp;
}
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    if (this->empty()) {
        return nullptr;
    }

    Node<Key, Value>* node = this->root_;

    while (node != nullptr) {
        if (node->getKey() > key) {
            node = node->getLeft();
        }
        else if (node->getKey() < key) {
            node = node->getRight();
        }
        else {
            return node;
        }
    }

    return nullptr;
}


template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
    if (this->empty()) return true;

    return this->isBalanced_Helper(root_);
}

template<typename Key, typename Value> 
bool BinarySearchTree<Key, Value>::isBalanced_Helper(Node<Key, Value>* node) {
    if (!node) {
        return true;
    }

    int leftHeight = isBalanced_Height(node->left_);
    int rightHeight = isBalanced_Height(node->right_);

    if (std::abs(leftHeight - rightHeight) <= 1 && isBalanced_Helper(node->left_) && isBalanced_Helper(node->right_)) {
        return true;
    }

    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalanced_Height(Node<Key, Value>* node) {
    if (!node) return 0;
    
    return 1 + std::max(isBalanced_Height(node->getLeft()), isBalanced_Height(node->getRight()));
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}



#include "print_bst.h"


#endif