#pragma once
#include <SFML/Graphics.hpp>
#include "linearStructures/LinkedList.h"
#include "linearStructures/Stack.h"
#include "linearStructures/Queue.h"

class LinearDataStructureMenu
{
private:
    // Enumerations for menus and operations
    enum SubMenu
    {
        LINEARMENU,
        LINKED_LIST,
        STACK,
        QUEUE
    };

    enum Operation
    {
        NONE,
        ADD_NODE,
        SEARCH_NODE,
        DELETE_NODE,
        TRAVERSE_LIST,
        DISPLAY_LIST,
        PUSH_ELEMENT,
        POP_ELEMENT,
        PEEK_ELEMENT,
        DISPLAY_STACK,
        ENQUEUE_ELEMENT,
        DEQUEUE_ELEMENT,
        PEEK_QUEUE_ELEMENT,
        DISPLAY_QUEUE
    };

    // References for window and font
    sf::RenderWindow &window;
    sf::Font &font;
    sf::Font &titleFont;

    // Menu texts
    sf::Text titleText;    // Title text
    sf::Text menuText;
    sf::Text promptText;
    sf::Text inputText;
    sf::Text statusText;
    sf::Text backText;

    // State variables
    SubMenu currentSubMenu;
    Operation currentOperation;
    std::string inputBuffer;
    bool showingDisplay;

    // Data structures
    LinkedList list;
    Stack stack;
    Queue queue;

    // Private methods
    void initializeTexts();
    void updatePrompt();
    void processInput();
    void handleLinkedListOperation(sf::Event &event);
    void handleStackOperation(sf::Event &event);
    void handleQueueOperation(sf::Event &event);
    void setState(SubMenu subMenu);
    void drawDataStructure();

public:
    sf::Color backgroundColor;

    // Constructor
    LinearDataStructureMenu(sf::RenderWindow &window, sf::Font &font, sf::Font &titleFont);

    // Public methods
    void handleEvents(sf::Event &event);
    void draw();
    void reset();
};
