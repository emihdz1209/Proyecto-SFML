#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include "searchAlgorithms/LinearSearch.h"
#include "searchAlgorithms/BinarySearch.h"

class SearchMenu
{
private:
    enum MenuState
    {
        MAIN_MENU,
        WAITING_FOR_COUNT,
        WAITING_FOR_ELEMENTS,
        WAITING_FOR_TARGET,
        SEARCHING,
        SEARCH_COMPLETE
    };

    sf::RenderWindow &window;
    sf::Font &font;
    sf::Font &titleFont;

    // Text elements
    sf::Text titleText;    // Title text
    sf::Text menuText;
    sf::Text promptText;
    sf::Text inputText;
    sf::Text statusText;
    sf::Text backText;

    // State variables
    MenuState currentState;
    bool searching;
    bool searchComplete;
    int numberOfElements;
    int searchTarget;
    int selectedAlgorithm;
    int searchResult;
    std::string inputBuffer;
    std::vector<int> arr;

    // Helper functions
    std::vector<int> parseInput(const std::string &input);
    void initializeTexts();
    void updatePrompt();
    void processInput();

public:
    SearchMenu(sf::RenderWindow &window, sf::Font &font, sf::Font &titleFont);

    void handleEvents(sf::Event &event);
    void draw();
    void reset();
    bool isComplete() const { return searchComplete; }
};
