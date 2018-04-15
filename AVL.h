//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_AVL_H
#define CS223_PROJECT2_AVL_H

#include <iostream>
using namespace std;

class BSTNode {

public:

    int value, height;
    BSTNode *left, *right, *parent;

    BSTNode(int val) {
        // each node is inserted as a leaf
        value = val;
        height = 1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    bool isLeaf() {
        return (left == NULL && right == NULL);
    }

    bool hasRightChild() {
        return (right != NULL);
    }

    bool hasLeftChild() {
        return (left != NULL);
    }

    bool isLeftChildOfParent() {
        if (isRoot())
            return false;
        else
            return parent->left == this;
    }

    bool isRoot() {
        return (parent == NULL);
    }

    void toString() {
        if (isRoot())
            cout << "<" << value << ", null>";
        else
            cout << "<" << value << ", " << parent->value << ">";
    }
};

class BalancedBST {

protected:

    BSTNode *root;
    int size;

private:

    static BSTNode *findMax(BSTNode *node) {
        if (NULL == node)
            return NULL;
        while (node->hasRightChild()) {
            node = node->right;
        }
        return node;
    }

    static int getHeight(BSTNode *node) {
        if (node == NULL)
            return 0;
        else
            return node->height;
    }

    static void setHeight(BSTNode *node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void rotateLeftHelper(BSTNode *node) {
        BSTNode *nodeR = node->right;
        if (!node->isRoot()) {
            BSTNode *nodeParent = node->parent;
            nodeR->parent = nodeParent;
            if (node->isLeftChildOfParent())
                nodeParent->left = nodeR;
            else
                nodeParent->right = nodeR;
        } else {
            root = nodeR;
            nodeR->parent = NULL;
        }
        node->right = nodeR->left;
        if (nodeR->left != NULL)
            nodeR->left->parent = node;
        nodeR->left = node;
        node->parent = nodeR;
        setHeight(node);
        setHeight(nodeR);
    }

    void rotateRightHelper(BSTNode *node) {
        BSTNode *nodeL = node->left;
        if (!node->isRoot()) {
            BSTNode *nodeParent = node->parent;
            nodeL->parent = nodeParent;
            if (node->isLeftChildOfParent())
                nodeParent->left = nodeL;
            else
                nodeParent->right = nodeL;
        } else {
            root = nodeL;
            nodeL->parent = NULL;
        }
        node->left = nodeL->right;
        if (nodeL->right != NULL)
            nodeL->right->parent = node;
        nodeL->right = node;
        node->parent = nodeL;
        setHeight(node);
        setHeight(nodeL);
    }

    void rotateLeft(BSTNode *node) {
        BSTNode *nodeR = node->right;
        int heightRL = getHeight(nodeR->left);
        int heightRR = getHeight(nodeR->right);

        if (heightRR <= heightRL)
            rotateRightHelper(node->right); // need to perform double rotation to left
        rotateLeftHelper(node);
    }

    void rotateRight(BSTNode *node) {
        BSTNode *nodeL = node->left;
        int heightLL = getHeight(nodeL->left);
        int heightLR = getHeight(nodeL->right);

        if (heightLL <= heightLR)
            rotateLeftHelper(node->left); // need to perform double rotation to right
        rotateRightHelper(node);
    }

    void rebalance(BSTNode *node) {
        int heightL = getHeight(node->left);
        int heightR = getHeight(node->right);

        if (heightR > heightL + 1) {
            rotateLeft(node);
        } else if (heightL > heightR + 1) {
            rotateRight(node);
        } else {
            setHeight(node);
        }
    }

    bool deleteAtMostOneChild(BSTNode *delNode) { // delNode must have at most 1 child
        BSTNode *parentOfDelNode = delNode->parent;
        if (delNode->isRoot()) {
            if (delNode->hasLeftChild()) {
                delNode->left->parent = NULL;
                root = delNode->left;
            } else if (delNode->hasRightChild()) {
                delNode->right->parent = NULL;
                root = delNode->right;
            } else {
                root = NULL;
            }
        } else if (delNode->isLeaf()) {
            // CASE 1: delNode is a leaf node
            if (delNode->isLeftChildOfParent())
                parentOfDelNode->left = NULL;
            else
                parentOfDelNode->right = NULL;
        } else {
            // CASE 2: delNode only has a left or a right child
            BSTNode *correctChild;
            if (delNode->hasLeftChild())
                correctChild = delNode->left;
            else
                correctChild = delNode->right;
            if (delNode->isLeftChildOfParent())
                parentOfDelNode->left = correctChild;
            else
                parentOfDelNode->right = correctChild;
            correctChild->parent = parentOfDelNode;
        }
        while (parentOfDelNode != NULL) {
            rebalance(parentOfDelNode);
            parentOfDelNode = parentOfDelNode->parent;
        }
        delNode = NULL;
        size--;
        return true;
    }

    void printBSTHelper(BSTNode *node) {
        if (NULL != node) {
            node->toString();
            cout << " ";
            printBSTHelper(node->left);
            printBSTHelper(node->right);
        }
    }

public:

    BalancedBST() {
        root = NULL;
        size = 0;
    }

    BSTNode *search(int key) {
        BSTNode *tmp = root;
        while (tmp != NULL) {
            if (tmp->value == key)
                return tmp;
            else if (tmp->value > key)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return NULL;
    }

    bool insert(int val) {
        if (root == NULL) {
            root = new BSTNode(val);
        } else {
            BSTNode *tmp = root, *parent = NULL;
            while (tmp != NULL) {
                if (tmp->value == val) {
                    return false;
                } else if (tmp->value > val) {
                    parent = tmp;
                    tmp = tmp->left;
                } else {
                    parent = tmp;
                    tmp = tmp->right;
                }
            }
            BSTNode *newNode = new BSTNode(val);
            newNode->parent = parent;
            if (parent->value > val)
                parent->left = newNode;
            else
                parent->right = newNode;

            while (parent != NULL) {
                rebalance(parent);
                parent = parent->parent;
            }
        }
        size++;
        return true;
    }

    int getTreeHeight() {
        return getHeight(root);
    }

    void printBST() {
        printBSTHelper(root);
    }

    bool remove(int val) {
        BSTNode *delNode = search(val);
        if (delNode == NULL) {
            return false;
        } else if (delNode->hasLeftChild() && delNode->hasRightChild()) {
            // CASE 3: delNode has both left and right child
            BSTNode *maxNodeInLeftSubTree = findMax(delNode->left);
            delNode->value = maxNodeInLeftSubTree->value;
            // reduced to case 1 or 2
            return deleteAtMostOneChild(maxNodeInLeftSubTree);
        } else {
            return deleteAtMostOneChild(delNode);
        }
    }
};

#endif //CS223_PROJECT2_AVL_H
