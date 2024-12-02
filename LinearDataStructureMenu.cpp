#include "LinearDataStructureMenu.h"
#include <sstream>


using namespace std;
using namespace sf;

// Constructor for the LinearDataStructureMenu class
LinearDataStructureMenu::LinearDataStructureMenu(RenderWindow &window, Font &font, Font &titleFont)
        : window(window), font(font), titleFont(titleFont), currentSubMenu(LINEARMENU), currentOperation(NONE), showingDisplay(false) {
    initializeTexts();
}


// Function to initialize text elements
void LinearDataStructureMenu::initializeTexts() {
    // Title text
    titleText.setFont(titleFont);
    titleText.setCharacterSize(26);
    titleText.setString("LINEAR D.S");
    titleText.setFillColor(sf::Color(113, 199, 117)); // Light green
    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
            (window.getSize().x - titleBounds.width) / 2.0f, 20.0f
    );

    // Prompt text
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setPosition(
            (window.getSize().x - promptText.getLocalBounds().width) / 2.0f,
            100.0f
    );

    // Input text
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(Color::White);
    inputText.setPosition(
            (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
            250.0f
    );

    // Status text
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(Color::White);
    statusText.setPosition(
            (window.getSize().x - statusText.getLocalBounds().width) / 2.0f,
            350.0f
    );

    // Back text
    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setString("Press ESC to return");
    FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition(
            (window.getSize().x - backBounds.width) / 2.0f,
            window.getSize().y - 50.0f
    );

    updatePrompt();
}

// Function to update the prompt text based on the current submenu
void LinearDataStructureMenu::updatePrompt() {
    switch (currentSubMenu) {
        case LINEARMENU:
            promptText.setString(
                    "Linear Data Structures:\n\n"
                    "1. Linked List\n"
                    "2. Stack\n"
                    "3. Queue\n\n"
                    "Input number for your selection\n-Press ESC to return-"
            );
            break;
        case LINKED_LIST:
            promptText.setString(
                    "Linked List Operations\n\n"
                    "1. Insert\n"
                    "2. Delete\n"
                    "3. Display\n\n"
                    "-Press ESC to return-"
            );
            break;
        case STACK:
            promptText.setString(
                    "Stack Operations\n\n"
                    "1. push\n"
                    "2. Pop\n"
                    "3. Display\n\n"
                    "-Press ESC to return-"
            );
            break;
        case QUEUE:
            promptText.setString(
                    "Queue Operations\n\n"
                    "1. Enqueue\n"
                    "2. Dequeue\n"
                    "3. Display\n\n"
                    "-Press ESC to return-"
            );
            break;
    }

    // Center prompt text
    FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setPosition(
            (window.getSize().x - promptBounds.width) / 2.0f,
            100.0f
    );
}

// Function to handle events
void LinearDataStructureMenu::handleEvents(Event& event) {
    if (event.type == Event::KeyPressed) {
        // Handle Back button
        if (event.key.code == Keyboard::B) {
            if (showingDisplay) {
                showingDisplay = false;
            } else if (currentSubMenu != LINEARMENU) {
                setState(LINEARMENU);
                return;
            }
        }

        // Handle menu navigation only if not in an input operation
        if (currentOperation == NONE) {
            switch (currentSubMenu) {
                case LINEARMENU:
                    if (event.key.code == Keyboard::Num1) {
                        setState(LINKED_LIST);
                    } else if (event.key.code == Keyboard::Num2) {
                        setState(STACK);
                    } else if (event.key.code == Keyboard::Num3) {
                        setState(QUEUE);
                    }
                    break;

                case LINKED_LIST:
                    handleLinkedListOperation(event);
                    break;

                case STACK:
                    handleStackOperation(event);
                    break;

                case QUEUE:
                    handleQueueOperation(event);
                    break;
            }

            // Center status text
            FloatRect statusBounds = statusText.getLocalBounds();
            statusText.setPosition(
                    (window.getSize().x - statusBounds.width) / 2.0f,
                    350.0f
            );

            updatePrompt();
        }
    }

    // Handle text input
    if (event.type == Event::TextEntered) {
        if (currentOperation != NONE) {
            if (isdigit(event.text.unicode)) {
                inputBuffer += static_cast<char>(event.text.unicode);
                inputText.setString(inputBuffer);
            } else if (event.text.unicode == '\b' && !inputBuffer.empty()) {
                inputBuffer.pop_back();
                inputText.setString(inputBuffer);
            } else if (event.text.unicode == '\r') {
                processInput();
            }
        }
    }
}

// Function to process input based on the current operation
void LinearDataStructureMenu::processInput() {
    if (inputBuffer.empty()) return;

    int value = stoi(inputBuffer);
    inputBuffer.clear();
    inputText.setString("");

    switch (currentOperation) {
        case ADD_NODE:
            list.append(value);
            statusText.setString("Node added");
            break;
        case DELETE_NODE:
            if(list.remove(value)) {  // Now returns int (1 for success, 0 for failure)
                statusText.setString("Node deleted");
            } else {
                statusText.setString("Node not found");
            }
            break;
        case PUSH_ELEMENT:
            stack.push(value);
            statusText.setString("Element pushed");
            break;
        case ENQUEUE_ELEMENT:
            queue.enqueue(value);
            statusText.setString("Element enqueued");
            break;
        default:
            break;
    }

    currentOperation = NONE;
}

// Function to handle linked list operations
void LinearDataStructureMenu::handleLinkedListOperation(Event& event) {
    if (event.key.code == Keyboard::Num1) {
        statusText.setString("Enter value to insert:");
        currentOperation = ADD_NODE;
        showingDisplay = false;
    }
    else if (event.key.code == Keyboard::Num2) {
        statusText.setString("Enter value to delete:");
        currentOperation = DELETE_NODE;
        showingDisplay = false;
    }
    else if (event.key.code == Keyboard::Num3) {
        showingDisplay = true;
        statusText.setString("List displayed");
    }
}

// Function to handle stack operations
void LinearDataStructureMenu::handleStackOperation(Event& event) {
    if (event.key.code == Keyboard::Num1) {
        statusText.setString("Enter value to push:");
        currentOperation = PUSH_ELEMENT;
        showingDisplay = false;
    }
    else if (event.key.code == Keyboard::Num2) {
        showingDisplay = false;
        if (!stack.isEmpty()) {
            int value = stack.pop();  // Store return value
            statusText.setString("Popped: " + to_string(value));
        } else {
            statusText.setString("Stack is empty");
        }
    }
    else if (event.key.code == Keyboard::Num3) {
        showingDisplay = true;
        statusText.setString("Stack displayed");
    }
}

// Function to handle queue operations
void LinearDataStructureMenu::handleQueueOperation(Event& event) {
    if (event.key.code == Keyboard::Num1) {
        statusText.setString("Enter value to enqueue:");
        currentOperation = ENQUEUE_ELEMENT;
        showingDisplay = false;
    }
    else if (event.key.code == Keyboard::Num2) {
        showingDisplay = false;
        if (!queue.isEmpty()) {
            int value = queue.dequeue();  // Store return value
            statusText.setString("Dequeued: " + to_string(value));
        } else {
            statusText.setString("Queue is empty");
        }
    }
    else if (event.key.code == Keyboard::Num3) {
        showingDisplay = true;
        statusText.setString("Queue displayed");
    }
}

// Function to draw the menu and data structures
void LinearDataStructureMenu::draw() {
    window.clear(Color(0, 26, 22)); // Dark green background

    // Draw title
    window.draw(titleText);

    if (showingDisplay) {
        drawDataStructure();
    } else {
        window.draw(promptText);
        window.draw(inputText);
        window.draw(statusText);
        window.draw(backText);
    }
}

// Function to draw the current data structure
void LinearDataStructureMenu::drawDataStructure() {
    switch (currentSubMenu) {
        case LINKED_LIST:
            list.display(window, font);
            break;
        case STACK:
            stack.display(window, font);
            break;
        case QUEUE:
            queue.display(window, font);
            break;
        default:
            break;
    }
    window.draw(backText); // Draw the back text
}

// Function to reset the menu state
void LinearDataStructureMenu::reset() {
    currentSubMenu = LINEARMENU;
    currentOperation = NONE;
    showingDisplay = false;
    inputBuffer.clear();
    statusText.setString("");
    inputText.setString("");
    updatePrompt();
}

// Function to set the current submenu state
void LinearDataStructureMenu::setState(SubMenu newState) {
    currentSubMenu = newState;
    currentOperation = NONE;
    showingDisplay = false;
    inputBuffer.clear();
    inputText.setString("");
    statusText.setString("");
    updatePrompt();
}