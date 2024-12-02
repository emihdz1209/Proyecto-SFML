#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

struct Node{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList{
    private:
        Node *head;

    public:
        LinkedList();
        ~LinkedList();
        void append(int val);
        bool search(int val);
        int remove(int val);
        void traverse();
        void display(RenderWindow &window, Font &font);
};

#endif // LINKEDLIST_H
