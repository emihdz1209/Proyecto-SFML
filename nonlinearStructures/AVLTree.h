#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct AVLNode{
    int key;
    AVLNode *leftNode;
    AVLNode *rightNode;
    int height;
    AVLNode(int k) : key(k), leftNode(nullptr), rightNode(nullptr), height(1) {}
};

class AVLTree{
    private:
        AVLNode *root;
        sf::RenderWindow &window;
        sf::Font &font;
        AVLNode *insert(AVLNode *node, int key);
        AVLNode *deleteNode(AVLNode *root, int key);
        int height(AVLNode *node);
        int getBalance(AVLNode *node);
        AVLNode *minumalValueNode(AVLNode *node);
        AVLNode *rightRotate(AVLNode *y);
        AVLNode *leftRotate(AVLNode *x);
        void drawNode(AVLNode *node, float x, float y, float xOffset);

    public:
        AVLTree(sf::RenderWindow &window, sf::Font &font);
        void draw();
        void insert(int key);
        void deleteKey(int key);
        void reset();
};