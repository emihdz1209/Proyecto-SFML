#include "LinkedList.h"

using namespace std;
using namespace sf;

// Constructor for the LinkedList class
LinkedList::LinkedList() : head(nullptr) {}

// Destructor for the LinkedList class
LinkedList::~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

// Function to append a value to the linked list
void LinkedList::append(int val)
{
    Node *newNode = new Node(val);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to search for a value in the linked list
bool LinkedList::search(int val)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data == val)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Function to remove a value from the linked list
int LinkedList::remove(int val)
{
    if (head == nullptr)
        return 0;

    if (head->data == val)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return 1;
    }

    Node *current = head;
    while (current->next != nullptr && current->next->data != val)
    {
        current = current->next;
    }

    if (current->next != nullptr)
    {
        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
        return 1;
    }

    return 0;
}

// Function to traverse and print the linked list
void LinkedList::traverse()
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to display the linked list in the SFML window
void LinkedList::display(RenderWindow &window, Font &font)
{
    Node *temp = head;
    int nodeCount = 0;
    while (temp != nullptr)
    {
        nodeCount++;
        temp = temp->next;
    }

    int divWidth = window.getSize().x;
    int divHeight = window.getSize().y;
    int margins = 100;
    int width = 50;
    int height = 50;
    int totalWidth = nodeCount * margins;
    int x = ((divWidth - totalWidth) / 2)-30;
    int y = ((divHeight - height) / 2)-30;

    temp = head;
    while (temp != nullptr)
    {
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

        // Draw the arrow to the next node
        if (temp->next != nullptr)
        {
            Vertex line[] = {
                Vertex(Vector2f(x + width, y + height / 2), Color::Red),
                Vertex(Vector2f(x + margins, y + height / 2), Color::Red)};
            window.draw(line, 2, Lines);

            // Draw the arrowhead
            Vertex arrowhead[] = {
                Vertex(Vector2f(x + margins - 10, y + height / 2 - 5), Color::Red),
                Vertex(Vector2f(x + margins, y + height / 2), Color::Red),
                Vertex(Vector2f(x + margins - 10, y + height / 2 + 5), Color::Red)};
            window.draw(arrowhead, 3, Triangles);
        }
        else
        {
            // Draw the arrow to "NULL"
            Vertex nullLine[] = {
                Vertex(Vector2f(x + width, y + height / 2), Color::Red),
                Vertex(Vector2f(x + width + 50, y + height / 2), Color::Red)};
            window.draw(nullLine, 2, Lines);

            Vertex nullArrowhead[] = {
                Vertex(Vector2f(x + width + 40, y + height / 2 - 5), Color::Red),
                Vertex(Vector2f(x + width + 50, y + height / 2), Color::Red),
                Vertex(Vector2f(x + width + 40, y + height / 2 + 5), Color::Red)};
            window.draw(nullArrowhead, 3, Triangles);

            // Draw the "NULL" at the end of the list
            Text nullText("NULL", font, 20);
            nullText.setFillColor(Color::White); // White text color
            nullText.setPosition(x + width + 60, y + height / 4);
            window.draw(nullText);
        }

        x += margins;
        temp = temp->next;
    }

    // Draw the head pointer below the first node
    if (head != nullptr)
    {
        Text headText("HEAD", font, 20);
        headText.setFillColor(Color::White);
        headText.setPosition((divWidth - totalWidth) / 2, y + height + 30);
        window.draw(headText);

        Vertex headLine[] = {
            Vertex(Vector2f((divWidth - totalWidth) / 2 + width / 2, y + height + 20), Color::Red),
            Vertex(Vector2f((divWidth - totalWidth) / 2 + width / 2, y + height), Color::Red)};
        window.draw(headLine, 2, Lines);

        Vertex headArrowhead[] = {
            Vertex(Vector2f((divWidth - totalWidth) / 2 + width / 2 - 5, y + height + 5), Color::Red),
            Vertex(Vector2f((divWidth - totalWidth) / 2 + width / 2, y + height), Color::Red),
            Vertex(Vector2f((divWidth - totalWidth) / 2 + width / 2 + 5, y + height + 5), Color::Red)};
        window.draw(headArrowhead, 3, Triangles);
    }

    // Draw the time and space complexity
    Text complexityText("Time Complexity: O(n)\nSpace Complexity: O(n)", font, 20);
    complexityText.setFillColor(Color::White);
    complexityText.setPosition((divWidth - complexityText.getLocalBounds().width) / 2, y + height + 50);
    window.draw(complexityText);
}