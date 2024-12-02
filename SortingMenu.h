#pragma once
#include <SFML/Graphics.hpp>
#include "sortingAlgorithms/BubbleSort.h"
#include "sortingAlgorithms/InsertionSort.h"
#include "sortingAlgorithms/SelectionSort.h"
#include "sortingAlgorithms/QuickSort.h"
#include "sortingAlgorithms/Mergesort.h"
#include <vector>
#include <string>
#include <sstream>

class SortingMenu
{
private:

    enum SortingAlgorithm
    {
        BUBBLE_SORT,
        INSERTION_SORT,
        SELECTION_SORT,
        QUICK_SORT,
        MERGE_SORT
    };

    enum MenuState
    {
        ALGORITHM_SELECTION,
        WAITING_FOR_COUNT,
        WAITING_FOR_ELEMENTS,
        SORTING_VISUALIZATION
    };

    sf::RenderWindow &window;
    sf::Font &font;
    sf::Font &titleFont;

    // Text elements
    sf::Text titleText;     // Title text
    sf::Text menuText;
    sf::Text promptText;
    sf::Text inputText;
    sf::Text algorithmText;

    // State variables
    MenuState currentState;
    bool enteringNumberCount;
    bool sorting;
    bool sortingComplete;
    int numberOfElements;
    int currentAlgorithm;
    std::string inputBuffer;
    std::vector<int> arr;

    // Text positioning
    const float TITLE_Y_POSITION = 50.0f;
    const float MENU_SPACING = 40.0f;
    const float PROMPT_Y_POSITION = 200.0f;
    const float INPUT_Y_POSITION = 250.0f;
    const float ALGORITHM_Y_POSITION = 350.0f;

    // Helper functions
    std::vector<int> parseInput(const std::string &input);
    void initializeTexts();
    void handleSortingAlgorithm();
    void updatePrompt();
    void centerText(sf::Text &text, float yPosition);
    void setState(MenuState newState);

public:
    SortingMenu(sf::RenderWindow &window, sf::Font &font, sf::Font &titleFont);
    void handleEvents(sf::Event &event);
    void draw();
    void reset();
    bool isComplete() const { return sortingComplete; }
};
