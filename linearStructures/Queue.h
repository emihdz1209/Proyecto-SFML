#ifndef QUEUE_H
#define QUEUE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Queue{
    private:
        struct Node{
            int data;
            Node *next;
            Node(int val) : data(val), next(nullptr) {}
        };
        Node *front;
        Node *rear;

    public:
        Queue();
        ~Queue();
        void enqueue(int val);
        int dequeue();
        int peek() const;
        bool isEmpty() const;
        void display(RenderWindow &window, Font &font) const;
};

#endif // QUEUE_H