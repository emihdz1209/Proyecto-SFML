#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SortingMenu.h"
#include "SearchMenu.h"
#include "LinearDataStructureMenu.h"
#include "NonLinearDataStructureMenu.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    // Initialize window and fonts
    RenderWindow window(VideoMode(800, 600), "Algorithm Visualizer");
    Font font;
    if (!font.loadFromFile("C:\\Users\\emili\\OneDrive\\Desktop\\ProyectoSFML\\static\\Minecraftia-Regular.ttf"))
    {
        cerr << "Failed to load Minecraftia-Regular.ttf" << endl;
        return EXIT_FAILURE;
    }
    

    Font TitleFont;
    if (!TitleFont.loadFromFile("C:\\Users\\emili\\OneDrive\\Desktop\\ProyectoSFML\\static\\Pixelmania.ttf"))
    {
        cerr << "Failed to load Pixelmania.ttf" << endl;
        return EXIT_FAILURE;
    }

    // Initialize menus
    SortingMenu sortingMenu(window, font, TitleFont);
    SearchMenu searchMenu(window, font, TitleFont);
    LinearDataStructureMenu linearMenu(window, font, TitleFont);
    NonLinearDataStructureMenu nonLinearMenu(window, font, TitleFont);


    // Create text objects with different fonts
    Text mainMenuTitle;
    mainMenuTitle.setFont(TitleFont); // Use the TitleFont
    mainMenuTitle.setCharacterSize(26);
    mainMenuTitle.setString("ALGORITHM VISUALIZER");
    mainMenuTitle.setFillColor(sf::Color(113, 199, 117));
    mainMenuTitle.setPosition(50, 50); // Center it manually or use bounds

    Text mainMenuText;
    mainMenuText.setFont(font); // Use the default font
    mainMenuText.setCharacterSize(24);
    mainMenuText.setString(
            "Main Menu:\n\n"
            "\t> 1. Sorting Algorithms\n\n"
            "\t> 2. Search Algorithms\n\n"
            "\t> 3. Linear Data Structures\n\n"
            "\t> 4. Non-Linear Data Structures\n\n"
            "\n--Enter Number to Continue--"
    );
    mainMenuText.setFillColor(sf::Color::White);
    mainMenuText.setPosition(100, 140); // Adjust position

    // Menu state tracking
    enum MainState
    {
        MAIN,
        SORTING,
        LINEAR,
        SEARCH,
        NONLINEAR
    };
    MainState currentState = MAIN;

    // Set background color
    Color backgroundColor(0, 26, 22);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            // Main menu navigation
            if (currentState == MAIN && event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Num1:
                        currentState = SORTING;
                        sortingMenu.reset();
                        window.pollEvent(event);
                        break;
                    case Keyboard::Num2:
                        currentState = SEARCH;
                        searchMenu.reset();
                        window.pollEvent(event);
                        break;
                    case Keyboard::Num3:
                        currentState = LINEAR;
                        linearMenu.reset();
                        window.pollEvent(event);
                        break;
                    case Keyboard::Num4:
                        currentState = NONLINEAR;
                        nonLinearMenu.reset();
                        window.pollEvent(event);
                        break;
                }
            }
            else if (event.key.code == Keyboard::Escape)
            {
                currentState = MAIN;
            }
            else
            {
                switch (currentState)
                {
                    case SORTING:
                        sortingMenu.handleEvents(event);
                        break;
                    case LINEAR:
                        linearMenu.handleEvents(event);
                        break;
                    case SEARCH:
                        searchMenu.handleEvents(event);
                        break;
                    case NONLINEAR:
                        nonLinearMenu.handleEvents(event);
                        break;
                }
            }
        }

        // Render both fonts
        window.clear(backgroundColor);

        switch (currentState)
        {
            case MAIN:
                window.draw(mainMenuTitle); // Draw title with TitleFont
                window.draw(mainMenuText); // Draw menu with font
                break;
            case SORTING:
                sortingMenu.draw();
                break;
            case LINEAR:
                linearMenu.draw();
                break;
            case SEARCH:
                searchMenu.draw();
                break;
            case NONLINEAR:
                nonLinearMenu.draw();
                break;
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
