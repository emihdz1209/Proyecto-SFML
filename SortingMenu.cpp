#include "SortingMenu.h"

using namespace std;
using namespace sf;

SortingMenu::SortingMenu(RenderWindow &window, Font &font, Font &titleFont)
        : window(window), font(font), titleFont(titleFont),
          enteringNumberCount(true), sorting(false), sortingComplete(false),
          numberOfElements(0), currentAlgorithm(BUBBLE_SORT),
          currentState(ALGORITHM_SELECTION)
{
    initializeTexts();
}

// Function to initialize text elements
void SortingMenu::initializeTexts()
{
    // Title text
    titleText.setFont(titleFont);
    titleText.setCharacterSize(26);
    titleText.setString("SORTING ALGORITHMS");
    titleText.setFillColor(Color(113, 199, 117)); // Light green
    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
            (window.getSize().x - titleBounds.width) / 2.0f, 20.0f
    );

    // Menu title and options
    menuText.setFont(font);
    menuText.setCharacterSize(24);

    // Prompt text with more space
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setPosition(
            (window.getSize().x - promptText.getLocalBounds().width) / 2.0f,
            100.0f);

    // Input text below prompt
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setPosition(
            (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
            250.0f);

    // Algorithm status text at bottom
    algorithmText.setFont(font);
    algorithmText.setCharacterSize(24);
    algorithmText.setFillColor(Color::White);
    algorithmText.setPosition(
            (window.getSize().x - algorithmText.getLocalBounds().width) / 2.0f,
            350.0f);

    setState(ALGORITHM_SELECTION);
}

// Function to update the prompt text based on the current state
void SortingMenu::updatePrompt()
{
    switch (currentState)
    {
        case WAITING_FOR_COUNT:
            promptText.setString("\nEnter the ammount of unsorted elements:\nPress Enter to continue, ESC to go back");
            break;
        case WAITING_FOR_ELEMENTS:
            promptText.setString("\nEnter each element, separated by spaces:\nPress Enter to start sorting, ESC to go back");
            break;
        case ALGORITHM_SELECTION:
            promptText.setString(
                    "Select Sorting Algorithm:\n\n"
                    "1. Bubble Sort\n"
                    "2. Insertion Sort\n"
                    "3. Selection Sort\n"
                    "4. Quick Sort\n"
                    "5. Merge Sort\n\n"
                    "Press number to select\n"
                    "-Press ESC to return-");
            break;
    }

    // Recenter prompt
    FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setPosition(
            (window.getSize().x - promptBounds.width) / 2.0f,
            100.0f);
}

// Function to parse input string into a vector of integers
vector<int> SortingMenu::parseInput(const string &input)
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
void SortingMenu::handleEvents(Event &event)
{
    if (event.type == Event::KeyPressed)
    {
        // Handle Back button
        if (event.key.code == Keyboard::Escape)
        {
            if (currentState != ALGORITHM_SELECTION)
            {
                setState(ALGORITHM_SELECTION);
                return;
            }
        }

        if (currentState == ALGORITHM_SELECTION)
        {
            switch (event.key.code)
            {
                case Keyboard::Num1:
                    currentAlgorithm = BUBBLE_SORT;
                    setState(WAITING_FOR_COUNT);
                    break;
                case Keyboard::Num2:
                    currentAlgorithm = INSERTION_SORT;
                    setState(WAITING_FOR_COUNT);
                    break;
                case Keyboard::Num3:
                    currentAlgorithm = SELECTION_SORT;
                    setState(WAITING_FOR_COUNT);
                    break;
                case Keyboard::Num4:
                    currentAlgorithm = QUICK_SORT;
                    setState(WAITING_FOR_COUNT);
                    break;
                case Keyboard::Num5:
                    currentAlgorithm = MERGE_SORT;
                    setState(WAITING_FOR_COUNT);
                    break;
            }

            FloatRect algoBounds = algorithmText.getLocalBounds();
            algorithmText.setPosition(
                    (window.getSize().x - algoBounds.width) / 2.0f,
                    350.0f);
        }

        if (currentState == WAITING_FOR_COUNT || currentState == WAITING_FOR_ELEMENTS)
        {
            if (event.key.code == Keyboard::Enter)
            {
                if (currentState == WAITING_FOR_COUNT)
                {
                    try
                    {
                        numberOfElements = stoi(inputBuffer);
                        if (numberOfElements > 0 && numberOfElements <= 100)
                        {
                            inputBuffer.clear();
                            setState(WAITING_FOR_ELEMENTS);
                        }
                        else
                        {
                            algorithmText.setString("Enter a number between 1 and 100");
                        }
                    }
                    catch (...)
                    {
                        algorithmText.setString("Invalid Number");
                    }
                }
                else if (currentState == WAITING_FOR_ELEMENTS)
                {
                    arr = parseInput(inputBuffer);
                    if (arr.size() == numberOfElements)
                    {
                        setState(SORTING_VISUALIZATION);
                        sorting = true;
                    }
                    else
                    {
                        algorithmText.setString("Please enter all " + to_string(numberOfElements) + " numbers");
                    }
                }
            }
        }
    }

    if (event.type == Event::TextEntered)
    {
        if (currentState == WAITING_FOR_COUNT || currentState == WAITING_FOR_ELEMENTS)
        {
            if (isdigit(event.text.unicode) || event.text.unicode == ' ')
            {
                inputBuffer += static_cast<char>(event.text.unicode);
                inputText.setString(inputBuffer);
            }
            else if (event.text.unicode == '\b' && !inputBuffer.empty())
            {
                inputBuffer.pop_back();
                inputText.setString(inputBuffer);
            }
        }
    }
}

// Function to handle the selected sorting algorithm
void SortingMenu::handleSortingAlgorithm()
{
    if (!sorting)
        return;

    switch (currentAlgorithm)
    {
        case BUBBLE_SORT:
            BubbleSort(arr, window, algorithmText, sorting, font);
            break;
        case INSERTION_SORT:
            InsertionSort(arr, window, algorithmText, sorting, font);
            break;
        case SELECTION_SORT:
            SelectionSort(arr, window, algorithmText, sorting, font);
            break;
        case QUICK_SORT:
            QuickSort(arr, 0, arr.size() - 1, window, algorithmText, sorting, font);
            break;
        case MERGE_SORT:
            MergeSort(arr, 0, arr.size() - 1, window, algorithmText, sorting, font);
            break;
    }

    if (!sorting)
    {
        sortingComplete = true;
        algorithmText.setString("Sorting Complete. Press ESC to return");
    }
}

void SortingMenu::draw()
{
    window.clear(Color(0, 26, 22)); // Dark green background

    // Draw title
    window.draw(titleText);

    window.draw(menuText);
    window.draw(promptText);
    window.draw(inputText);
    window.draw(algorithmText);

    if (sorting)
    {
        handleSortingAlgorithm();
    }
}

// Function to reset the menu state
void SortingMenu::reset()
{
    enteringNumberCount = true;
    sorting = false;
    sortingComplete = false;
    numberOfElements = 0;
    inputBuffer.clear();
    arr.clear();
    inputText.setString("");
    setState(ALGORITHM_SELECTION);
}

// Function to set the current state of the menu
void SortingMenu::setState(MenuState newState)
{
    currentState = newState;
    menuText.setString("");
    inputBuffer.clear();
    inputText.setString("");

    // Keep algorithm text during state transitions
    if (currentState == WAITING_FOR_COUNT)
    {
        string algorithmName;
        switch (currentAlgorithm)
        {
            case BUBBLE_SORT:
                algorithmName = "Bubble Sort Selected";
                break;
            case INSERTION_SORT:
                algorithmName = "Insertion Sort Selected";
                break;
            case SELECTION_SORT:
                algorithmName = "Selection Sort Selected";
                break;
            case QUICK_SORT:
                algorithmName = "Quick Sort Selected";
                break;
            case MERGE_SORT:
                algorithmName = "Merge Sort Selected";
                break;
        }
        algorithmText.setString(algorithmName);

        FloatRect algoBounds = algorithmText.getLocalBounds();
        algorithmText.setPosition(
                (window.getSize().x - algoBounds.width) / 2.0f,
                350.0f);
    }
    else
    {
        algorithmText.setString("");
    }

    updatePrompt();
}
