#ifndef STACK_H
#define STACK_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Stack{
    private:
        struct Node{
            int data;
            Node *next;
            Node(int val) : data(val), next(nullptr) {}
        };
        Node *top;

    public:
        Stack();
        ~Stack();
        void push(int val);
        int pop();
        int peek() const;
        bool isEmpty() const;
        void display(RenderWindow &window, Font &font) const;
};

#endif // STACK_H