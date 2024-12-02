#include "Queue.h"
#include <iostream>

using namespace sf;
using namespace std;

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue()
{
    while (front != nullptr){
        Node *temp = front;
        front = front->next;
        delete temp;
    }
}

void Queue::enqueue(int val)
{
    Node *newNode = new Node(val);
    if (rear == nullptr){
        front = rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
}

int Queue::dequeue(){
    if (isEmpty()){
        return -1; 
    }
    int value = front->data;
    Node *temp = front;
    front = front->next;

    if (front == nullptr){
        rear = nullptr;
    }
    delete temp;
    return value;
}

int Queue::peek() const{

    if (front == nullptr)
        throw runtime_error("Queue is empty");
    return front->data;
}

bool Queue::isEmpty() const{
    return front == nullptr;
}

void Queue::display(RenderWindow &window, Font &font) const{
    Node *temp = front;
    int divWidth = window.getSize().x;
    int x = divWidth / 2 - 25;
    int y = 200;
    int margins = 70;
    int width = 50;
    int height = 30;

    while (temp != nullptr){
        // Draw the rectangle
        RectangleShape rectangle(Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(Color(113, 198, 117)); // Light blue fill color
        rectangle.setOutlineColor(Color::Black);      // Black outline color
        rectangle.setOutlineThickness(2);
        window.draw(rectangle);

        // Draw the data
        Text dataText(to_string(temp->data), font, 20);
        dataText.setFillColor(Color::Black); // Black text color
        dataText.setPosition(x + width / 4, y + height / 2);
        window.draw(dataText);
        y += margins;
        temp = temp->next;
    }

    if (front != nullptr){
        Text frontText("Front", font, 20);
        frontText.setFillColor(Color::White);
        frontText.setPosition(x, 150 - margins / 2);
        window.draw(frontText);

        Vertex frontLine[] = {
            Vertex(Vector2f(x + width / 2, 150 - margins / 2 + 20), Color::Red),
            Vertex(Vector2f(x + width /2, 200), Color::Red)
        };
        window.draw(frontLine, 2, Lines);

        Vertex frontArrowhead[] = {
            Vertex(Vector2f(x +width / 2 - 5, 200 - 5), Color::Red),
            Vertex(Vector2f(x +width / 2, 200), Color::Red),
            Vertex(Vector2f(x + width / 2 + 5, 200 - 5), Color::Red)};
        window.draw(frontArrowhead, 3, Triangles);
    }

    if (rear != nullptr){
        Text rearText("REAR", font, 20);
        rearText.setFillColor(Color::White);
        rearText.setPosition(x + width + 20, y - margins);
        window.draw(rearText);
        Vertex rearLine[] = {
            Vertex(Vector2f(x + width, y - margins + height / 2), Color::Red),
            Vertex(Vector2f(x + width + 20, y - margins + height / 2), Color::Red)
        };
        window.draw(rearLine, 2, Lines);
        Vertex rearArrowhead[] = {
            Vertex(Vector2f(x + width + 15, y - margins + height / 2 - 5), Color::Red),
            Vertex(Vector2f(x + width + 20, y - margins + height / 2), Color::Red),
            Vertex(Vector2f(x + width + 15, y - margins + height / 2 + 5), Color::Red)};
        window.draw(rearArrowhead, 3, Triangles);
    }

    Text complexityText("Time Complexity: O(1)\nSpace Complexity: O(n)", font, 20);
    complexityText.setFillColor(Color::White);
    complexityText.setPosition((divWidth - complexityText.getLocalBounds().width) / 2, y + 50);
    window.draw(complexityText);
}