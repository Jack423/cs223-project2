//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_LINKEDLIST_H_
#define CS223_PROJECT2_LINKEDLIST_H_

#include <iostream>
using namespace std;

class ListNode {

public:

    int value;
    ListNode *next;

    ListNode(int val) {
        value = val;
        next = NULL;
    }
};

class LinkedList {

public:

    ListNode *head, *tail;
    int size;

    LinkedList() {
        head = tail = NULL;
        size = 0;
    }

    bool removeFirst(int val) { // fill this method
        ListNode *tmp = head;
        if(tmp->value == val){
            deleteHead();
            return true;
        }
        for (int i = 0; i < size - 1; i++) {
            if (tmp->next->value == val){ //Arnab: There is a flaw. What happens when val is not on the list? You will continue all the way upto the end, and tmp becomes tail. Then, tmp->next is NULL. So, you are trying to do NULL->value, which is a null pointer reference. So you should not go all the way to the end. Hence, change to i < size - 1 in the for loop.
                deleteAfter(tmp); //Arnab: This is incorrect. Recall that deleteAfter deletes the node following the argument. In this case, your tmp->next->value == val, so you should delete tmp->next. Hence, change the call to deleteAfter(tmp).
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    void deleteAfter(ListNode *argNode) {
        if (argNode == tail) {
            cout << "Cannot delete after tail." << endl;
        } else if (argNode->next == tail) {
            // fill this part
            argNode->next = NULL;
            delete tail;
            tail = argNode;
            size--;
        } else {
            ListNode *tmp = argNode->next;
            argNode->next = argNode->next->next;
            delete tmp;
            size--;
        }
    }

    int search(int key) {

        ListNode *tmp = head;
        for (int i = 0; i < size; i++) {
            if (tmp->value == key)
                return i;
            tmp = tmp->next;
        }
        return -1;
    }

    ListNode *insertAtEnd(int value) {
        ListNode *newNode = new ListNode(value);
        if (size == 0) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
        return newNode;
    }

    void deleteHead() {
        if (0 == size) {
            cout << "Cannot delete from an empty list." << endl;
        } else if (1 == size) {
            size--;
            delete head;
        } else {
            size--;
            ListNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void printList() {
        if (size == 0)
            cout << "[]" << endl;
        else {
            ListNode *tmp = head;
            cout << "[";
            for (int i = 0; i < size - 1; i++) {
                cout << tmp->value << " -> ";
                tmp = tmp->next;
            }
            cout << tail->value << "]" << endl;
        }
    }

    int getSize() {
        return size;
    }
};

#endif
