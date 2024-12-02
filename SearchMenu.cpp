#include "SearchMenu.h"

using namespace std;
using namespace sf;

SearchMenu::SearchMenu(RenderWindow &window, Font &font, Font &titleFont)
        : window(window), font(font), titleFont(titleFont),
          currentState(MAIN_MENU),
          numberOfElements(0), searchTarget(0),
          searching(false), searchComplete(false),
          selectedAlgorithm(0),
          searchResult(-1)
{
    initializeTexts();
}

// Function to initialize text elements
void SearchMenu::initializeTexts()
{
    // Title text
    titleText.setFont(titleFont);
    titleText.setCharacterSize(26);
    titleText.setString("SEARCH ALGORITHMS");
    titleText.setFillColor(Color(113, 199, 117)); // Light green
    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
            (window.getSize().x - titleBounds.width) / 2.0f, 20.0f
    );

    // Menu text
    menuText.setFont(font);
    menuText.setCharacterSize(24);
    menuText.setString("\n\nSearch Algorithms:\n\n"
                       "1. Linear Search\n"
                       "2. Binary Search\n\n"
                       "Press number to select\n"
                       "-Press ESC to return-");

    menuText.setPosition(
            (window.getSize().x - menuText.getLocalBounds().width) / 2.0f,
            70.0f);

    // Prompt text
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setPosition(
            (window.getSize().x - promptText.getLocalBounds().width) / 2.0f,
            140.0f);

    // Input text
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setString(""); // Clear any leftover input
    inputText.setPosition(
            (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
            250.0f);

    // Status text
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(Color::White);
    statusText.setPosition(
            (window.getSize().x - statusText.getLocalBounds().width) / 2.0f,
            350.0f);

    // Back text
    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setString("Press ESC to return");
    FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition(
            (window.getSize().x - backBounds.width) / 2.0f,
            window.getSize().y - 50.0f);

    updatePrompt();
}

// Function to update the prompt text based on the current state
void SearchMenu::updatePrompt()
{
    if (currentState == MAIN_MENU)
    {
        menuText.setString("\n\nSearch Algorithms:\n\n"
                           "1. Linear Search\n"
                           "2. Binary Search\n\n"
                           "Press number to select\n"
                           "-Press ESC to return-");
    }
    else
    {
        menuText.setString(""); // Clear menu text in other states
    }

    switch (currentState)
    {
        case MAIN_MENU:
            promptText.setString("");
            break;
        case WAITING_FOR_COUNT:
            promptText.setString("Enter the number of elements:\n-Press ESC to return-");
            break;
        case WAITING_FOR_ELEMENTS:
            promptText.setString("Enter the elements separated by spaces:\n-Press ESC to return-");
            break;
        case WAITING_FOR_TARGET:
            promptText.setString("Enter target:\n-Press ESC to return-");
            break;
        default:
            break;
    }

    FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setPosition(
            (window.getSize().x - promptBounds.width) / 2.0f,
            140.0f);
}

// Function to parse input string into a vector of integers
vector<int> SearchMenu::parseInput(const string &input)
{
    vector<int> result;
    stringstream ss(input);
    int number;
    while (ss >> number)
    {
        result.push_back(number);
    }
    return result;
}

// Function to handle events
void SearchMenu::handleEvents(Event &event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Escape)
        {
            if (currentState != MAIN_MENU)
            {
                reset();
                return;
            }
        }

        if (currentState == MAIN_MENU)
        {
            if (event.key.code == Keyboard::Num1)
            {
                selectedAlgorithm = 1;
                currentState = WAITING_FOR_COUNT;
                inputBuffer.clear();
                updatePrompt();
            }
            else if (event.key.code == Keyboard::Num2)
            {
                selectedAlgorithm = 2;
                currentState = WAITING_FOR_COUNT;
                inputBuffer.clear();
                updatePrompt();
            }
        }
        else if (event.key.code == Keyboard::Enter)
        {
            processInput();
        }
    }

    if (event.type == Event::TextEntered && !searching) {
        if (isdigit(event.text.unicode) || event.text.unicode == ' ') {
            inputBuffer += static_cast<char>(event.text.unicode);
            inputText.setString(inputBuffer);
        } else if (event.text.unicode == '\b' && !inputBuffer.empty()) {
            inputBuffer.pop_back();
            inputText.setString(inputBuffer);
        }
    }
}

// Function to process input based on the current state
void SearchMenu::processInput()
{
    switch (currentState)
    {
        case MAIN_MENU:
            break;
        case WAITING_FOR_COUNT:
            numberOfElements = stoi(inputBuffer);
            currentState = WAITING_FOR_ELEMENTS;
            inputBuffer.clear();
            break;
        case WAITING_FOR_ELEMENTS:
            arr = parseInput(inputBuffer);
            if (arr.size() == numberOfElements)
            {
                currentState = WAITING_FOR_TARGET;
                inputBuffer.clear();
            }
            break;
        case WAITING_FOR_TARGET:
            searchTarget = stoi(inputBuffer);
            searching = true;
            currentState = SEARCHING;
            inputBuffer.clear();
            break;
        default:
            break;
    }
    inputText.setString(inputBuffer);
    updatePrompt();
}

// Function to draw the current menu and search results
void SearchMenu::draw()
{
    window.clear(Color(0, 26, 22)); // Dark green background

    window.draw(titleText);
    window.draw(menuText);
    window.draw(promptText);
    window.draw(inputText);
    window.draw(statusText);

    if (searching && currentState == SEARCHING)
    {
        if (selectedAlgorithm == 1)
        {
            searchResult = LinearSearch(arr, searchTarget, window, statusText, searching, font);
        }
        else if (selectedAlgorithm == 2)
        {
            searchResult = BinarySearch(arr, searchTarget, window, statusText, searching, font);
        }
    }

    if (!searching && currentState == SEARCHING)
    {
        currentState = SEARCH_COMPLETE;

        FloatRect statusBounds = statusText.getLocalBounds();
        statusText.setPosition(
                (window.getSize().x - statusBounds.width) / 2.0f,
                350.0f);
    }
}

// Function to reset the menu state
void SearchMenu::reset() {
    currentState = MAIN_MENU;
    searching = false;
    searchComplete = false;
    numberOfElements = 0;
    searchTarget = 0;
    searchResult = -1;
    selectedAlgorithm = 0;

    inputBuffer.clear();         // Clear buffer
    inputText.setString("");     // Clear visible input
    statusText.setString("");    // Reset status text
    menuText.setString("\n\nSearch Algorithms:\n\n"
                       "1. Linear Search\n"
                       "2. Binary Search\n\n"
                       "Press number to select\n"
                       "-Press ESC to return-");
    updatePrompt();
}
