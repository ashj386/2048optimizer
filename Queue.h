#pragma once
#include "objects.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Pair {
    vector<vector<int>> matrix;
    string path;
};

struct Qnode {
    Pair data;
    Qnode* next;
};

class Queue{
    private:
        Qnode* head;
        Qnode* tail;
    public:
        Queue();
        bool isEmpty();
        void push(Pair p);
        Pair pop();
};

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

bool Queue::isEmpty() {
    return (head == nullptr);
}

void Queue::push(Pair p) {
    Qnode* temp = new Qnode();
    temp->data = p;
    temp->next = nullptr;
    if (isEmpty()) {
        head = temp;
        tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
}

Pair Queue::pop() {
    Pair temp = head->data;
    Qnode* del = head;
    head = head->next;
    delete del;
    return temp;
}
