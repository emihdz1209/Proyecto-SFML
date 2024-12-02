#include "AVLTree.h"

using namespace std;
using namespace sf;

AVLTree::AVLTree(RenderWindow &window, Font &font) : window(window), font(font), root(nullptr) {}

// Function to insert a key into the AVL tree
AVLNode *AVLTree::insert(AVLNode *node, int key){
    // Perform the normal BST insertion
    if (!node)
        return new AVLNode(key);
    if (key < node->key)
        node->leftNode = insert(node->leftNode, key);
    else if (key > node->key)
        node->rightNode = insert(node->rightNode, key);
    else
        return node;

    node->height = 1 + max(height(node->leftNode), height(node->rightNode));
    int balance = getBalance(node);

    // LLR
    if (balance > 1 && key < node->leftNode->key)
        return rightRotate(node);

    // RRR
    if (balance < -1 && key > node->rightNode->key)
        return leftRotate(node);

    // LLR?!?!?!
    if (balance > 1 && key > node->leftNode->key)
    {
        node->leftNode = leftRotate(node->leftNode);
        return rightRotate(node);
    }

    // RLR.....
    if (balance < -1 && key < node->rightNode->key)
    {
        node->rightNode = rightRotate(node->rightNode);
        return leftRotate(node);
    }

    return node;
}

AVLNode *AVLTree::deleteNode(AVLNode *root, int key){
    if (!root)
        return root;
    if (key < root->key)
        root->leftNode = deleteNode(root->leftNode, key);
    else if (key > root->key)
        root->rightNode = deleteNode(root->rightNode, key);
    else
    {
        if (!root->leftNode || !root->rightNode)
        {
            AVLNode *temp=root->leftNode ? root->leftNode :root->rightNode;
            if (!temp){
                temp =root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else{
            AVLNode *temp= minumalValueNode(root->rightNode);
            root->key =temp->key;
            root->rightNode = deleteNode(root->rightNode, temp->key);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(height(root->leftNode), height(root->rightNode));

    int balance = getBalance(root);


    // llr
    if (balance > 1 && getBalance(root->leftNode) >= 0)
        return rightRotate(root);

    // lrR
    if (balance > 1 && getBalance(root->leftNode) < 0)
    {
        root->leftNode = leftRotate(root->leftNode);
        return rightRotate(root);
    }

    // RRR!!
    if (balance < -1 && getBalance(root->rightNode) <= 0)
        return leftRotate(root);

    // RLR.!!!??!
    if (balance < -1 && getBalance(root->rightNode) > 0)
    {
        root->rightNode = rightRotate(root->rightNode);
        return leftRotate(root);
    }

    return root;
}

int AVLTree::height(AVLNode *node){
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode *node){
    return node ? height(node->leftNode) - height(node->rightNode) : 0;
}

AVLNode *AVLTree::minumalValueNode(AVLNode *node){
    AVLNode *current= node;
    while (current-> leftNode)
        current = current ->leftNode;
    return current;
}

AVLNode *AVLTree::rightRotate(AVLNode *y){
    AVLNode *x =y->leftNode;
    AVLNode *T2 =x->rightNode;
    x->rightNode = y;
    y->leftNode =T2;
    y->height = max(height(y->leftNode),height(y->rightNode)) + 1;
    x->height = max(height(x->leftNode), height(x->rightNode)) + 1;
    return x;
}

AVLNode *AVLTree::leftRotate(AVLNode *x){
    AVLNode *y = x->rightNode;
    AVLNode *T2 = y->leftNode;
    y->leftNode = x;
    x->rightNode = T2;
    x->height = max(height(x->leftNode), height(x->rightNode)) + 1;
    y->height = max(height(y->leftNode), height(y->rightNode)) + 1;
    return y;
}

void AVLTree::insert(int key){
    root = insert(root, key);
}

void AVLTree::deleteKey(int key){
    root = deleteNode(root, key);
}

void AVLTree::drawNode(AVLNode *node, float x, float y, float xOffset){
    if (!node)
        return;

    CircleShape circle(20);
    circle.setFillColor(Color(113, 199, 117));
    circle.setPosition(x, y);
    window.draw(circle);

    Text text;
    text.setFont(font);
    text.setString(to_string(node->key));
    text.setCharacterSize(19);
    text.setFillColor(Color::White);
    text.setPosition(x + 6, y + 22);
    window.draw(text);

    // Draw the left child
    if (node->leftNode)
    {
        Vertex line[] = {
            Vertex(Vector2f(x + 20, y + 20)),
            Vertex(Vector2f(x - xOffset + 20, y + 80))};
        window.draw(line, 2, Lines);
        drawNode(node->leftNode, x - xOffset, y + 80, xOffset / 2);
    }

    if (node->rightNode)
    {
        Vertex line[] = {
            Vertex(Vector2f(x + 20, y + 20)),
            Vertex(Vector2f(x + xOffset + 20, y + 80))};
        window.draw(line, 2, Lines);
        drawNode(node->rightNode, x + xOffset, y + 80, xOffset / 2);
    }
}

void AVLTree::draw(){
    drawNode(root, window.getSize().x / 2, 200, window.getSize().x / 4);
}

void AVLTree::reset(){
    root = nullptr;
}