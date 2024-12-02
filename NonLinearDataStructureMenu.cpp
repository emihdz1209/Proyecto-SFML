#include "NonLinearDataStructureMenu.h"
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace sf;
using namespace std::chrono;

// Constructor for the NonLinearDataStructureMenu class
NonLinearDataStructureMenu::NonLinearDataStructureMenu(RenderWindow &window, Font &font, Font &titleFont)
        : window(window), font(font), titleFont(titleFont),
          avlTree(window, font), graphs(window, font),
          mazeSolver(21, 21, 20), currentSubMenu(MAIN_MENU), inputMode(NONE) {
    initializeTexts();
}

// Initialize text elements
void NonLinearDataStructureMenu::initializeTexts() {
    // Title text
    titleText.setFont(titleFont);
    titleText.setCharacterSize(26);
    titleText.setString("NON LINEAR D.S.");
    titleText.setFillColor(sf::Color(113, 199, 117)); // Light green
    FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(
            (window.getSize().x - titleBounds.width) / 2.0f, 20.0f
    );

    // Prompt text
    promptText.setFont(font);
    promptText.setCharacterSize(24);
    promptText.setPosition(
            (window.getSize().x - promptText.getLocalBounds().width) / 2.0f, 100.0f
    );

    // Back text
    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setString("Input number for your selection\n-Press ESC to return-");
    FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition(
            (window.getSize().x - backBounds.width) / 2.0f,
            window.getSize().y - 50.0f
    );

    // Input text
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(Color::White);
    inputText.setPosition(
            (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
            window.getSize().y - 200.0f
    );

    // Complexity text
    complexityText.setFont(font);
    complexityText.setCharacterSize(18);
    complexityText.setFillColor(Color::White);

    // Set initial position of complexity text
    FloatRect backTextBounds = backText.getLocalBounds();
    complexityText.setPosition(
            (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
            backText.getPosition().y - 60.0f
    );

    updatePrompt();
    updateComplexityText();
}

// Function to update the prompt text based on the current submenu
void NonLinearDataStructureMenu::updatePrompt() {
    switch (currentSubMenu) {
        case MAIN_MENU:
            promptText.setString(
                    "Non-Linear Data Structures:\n\n"
                    "1. AVL Tree\n"
                    "2. Graph\n"
                    "3. Maze Solver\n\n"
            );
            break;
        case AVL_TREE_MENU:
            promptText.setString(
                    "AVL Tree Operations\n"
                    "1. Insert Node 2. Delete Node\n\n"
            );
            break;
        case GRAPH_MENU:
            promptText.setString(
                    "Graph Operations\n\n"
                    "1. Generate Graph\n"
                    "2. Find Shortest Path\n\n"
            );
            break;
        case MAZE_MENU:
            promptText.setString(
                    "Maze Solver Operations\n\n"
                    "1. Solve Maze with BFS\t2. Solve Maze with DFS\n\n"
            );
            break;
    }

    FloatRect promptBounds = promptText.getLocalBounds();
    promptText.setPosition(
            (window.getSize().x - promptBounds.width) / 2.0f, 100.0f
    );
}

// Function to update the complexity text based on the current submenu and input mode
void NonLinearDataStructureMenu::updateComplexityText() {
    switch (currentSubMenu) {
        case AVL_TREE_MENU:
            complexityText.setString(
                    "Time Complexity: O(log n)\n"
                    "Space Complexity: O(n)"
            );
            break;
        case GRAPH_MENU:
            complexityText.setString(
                    "Time Complexity: O(V + E)\n"
                    "Space Complexity: O(V + E)"
            );
            break;
        default:
            complexityText.setString("");
            break;
    }

    FloatRect complexityBounds = complexityText.getLocalBounds();
    complexityText.setPosition(
            (window.getSize().x - complexityBounds.width) / 2.0f,
            backText.getPosition().y - 60.0f
    );
}

// Function to handle events
void NonLinearDataStructureMenu::handleEvents(Event &event)
{
    if (event.type == Event::KeyPressed)
    {
        if (inputMode == NONE)
        {
            if (event.key.code == Keyboard::Escape)
            {
                if (currentSubMenu != MAIN_MENU)
                {
                    currentSubMenu = MAIN_MENU;
                    inputMode = NONE;
                    inputText.setString("");
                    inputString.clear();
                    updatePrompt();
                    updateComplexityText();
                }
            }
            else if (currentSubMenu == MAIN_MENU)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    currentSubMenu = AVL_TREE_MENU;
                    updatePrompt();
                    updateComplexityText();
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    currentSubMenu = GRAPH_MENU;
                    updatePrompt();
                    updateComplexityText();
                }
                else if (event.key.code == Keyboard::Num3)
                {
                    currentSubMenu = MAZE_MENU;
                    updatePrompt();
                    updateComplexityText();
                }
            }
            else if (currentSubMenu == AVL_TREE_MENU)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    inputMode = INSERT;
                    inputString.clear();
                    inputText.setString("Number to insert: ");
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    inputMode = DELETE;
                    inputString.clear();
                    inputText.setString("Number to delete: ");
                }
            }
            else if (currentSubMenu == GRAPH_MENU)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    graphs.generatePredefinedGraph();
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    inputMode = INSERT;
                    inputString.clear();
                    inputText.setString("Enter Start and End node: ");
                }
            }
            else if (currentSubMenu == MAZE_MENU)
            {
                if (event.key.code == Keyboard::Num1)
                {
                    inputMode = SOLVE_BFS;
                    inputString.clear();
                    auto start = high_resolution_clock::now();
                    mazeSolver.solveBFS(window);
                    auto end = high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
                    complexityText.setString(
                        "Time Complexity for BFS: O(V + E)\n"
                        "Space Complexity for BFS: O(V)\n"
                        "Execution Time: " + to_string(duration) + " seconds");
                    inputMode = NONE;
                }
                else if (event.key.code == Keyboard::Num2)
                {
                    inputMode = SOLVE_DFS;
                    inputString.clear();
                    auto start = high_resolution_clock::now();
                    DFS::solve(mazeSolver, window);
                    auto end = high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
                    complexityText.setString(
                        "Time Complexity for DSF: O(V + E)\n"
                        "Space Complexity for DFS : O(V)\n"
                        "Execution Time: " + to_string(duration) + " seconds");
                    inputMode = NONE;
                }
            }
            FloatRect complexityBounds = complexityText.getLocalBounds();
            complexityText.setPosition(
                    (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
                    backText.getPosition().y - 100.0f
            );
        }
    }
    else if (event.type == Event::TextEntered)
    {
        if (inputMode != NONE)
        {
            if (event.text.unicode == '\b')
            {
                if (!inputString.empty())
                {
                    inputString.pop_back();
                }
            }
            else if (event.text.unicode == '\r')
            {
                if (!inputString.empty())
                {
                    if (inputMode == INSERT && currentSubMenu == GRAPH_MENU)
                    {
                        istringstream iss(inputString);
                        int startNode, endNode;
                        if (iss >> startNode >> endNode)
                        {
                            vector<Nodo> resultado = graphs.dijkstra(startNode);

                            string distances = "Calculating the shortest path from node " + to_string(startNode) + " to node " + to_string(endNode) + ":\n";

                            if (resultado[endNode].distancia == INF) {
                                distances += "No path available from node " + to_string(startNode) + " to node " + to_string(endNode) + "\n";
                            } else {
                                distances += "Best available path: ";
                                for (size_t i = 0; i < resultado[endNode].ruta.size(); ++i) {
                                    distances += to_string(resultado[endNode].ruta[i]);
                                    if (i < resultado[endNode].ruta.size() - 1) {
                                        distances += " -> ";
                                    }
                                }
                                distances += "\n";

                                distances += "Total distance: " + to_string(resultado[endNode].distancia) + " meters (" + to_string(resultado[endNode].distancia / 1000.0) + " km)\n";
                                distances += "Steps taken: " + to_string(resultado[endNode].ruta.size() - 1) + " steps\n";
                            }

                            inputText.setString(distances);
                            inputText.setPosition(
                                (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
                                window.getSize().y - 200.0f);
                        }
                        else
                        {
                            inputText.setString("Invalid input. Please enter two numbers separated by space.");
                            inputText.setPosition(
                                (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
                                window.getSize().y - 200.0f);
                        }
                        inputMode = NONE;
                        inputString.clear();
                    }
                    else
                    {
                        int key = stoi(inputString);
                        if (inputMode == INSERT)
                        {
                            if (currentSubMenu == AVL_TREE_MENU)
                            {
                                avlTree.insert(key);
                                inputText.setString("");
                            }
                        }
                        else if (inputMode == DELETE)
                        {
                            if (currentSubMenu == AVL_TREE_MENU)
                            {
                                avlTree.deleteKey(key);
                                inputText.setString("");
                            }
                        }
                        inputMode = NONE;
                        inputString.clear();
                    }
                }
            }
            else if (event.text.unicode < 128 && (isdigit(static_cast<char>(event.text.unicode)) || event.text.unicode == ' '))
            {
                inputString += static_cast<char>(event.text.unicode);
            }
            if (currentSubMenu == AVL_TREE_MENU)
            {
                inputText.setString("Define number to " + string(inputMode == INSERT ? "insert: " : "delete: ") + inputString);
            }
            else if (currentSubMenu == GRAPH_MENU && inputMode == INSERT)
            {
                inputText.setString("Start node and Final\nnode: " + inputString);
            }
            inputText.setPosition(
                (window.getSize().x - inputText.getLocalBounds().width) / 2.0f,
                window.getSize().y - 210.0f);
        }
    }
}

// Function to draw the current menu
void NonLinearDataStructureMenu::draw() {
    // Set the background color to match main.cpp
    window.clear(Color(0, 26, 22)); // Dark green

    // Draw title
    window.draw(titleText);

    // Draw other elements
    window.draw(promptText);
    window.draw(backText);
    window.draw(complexityText);
    if (currentSubMenu == AVL_TREE_MENU) {
        avlTree.draw();
    } else if (currentSubMenu == GRAPH_MENU) {
        View originalView = window.getView();
        View graphView = originalView;
        graphView.setViewport(FloatRect(0, 0.1f, 1, 0.8f));
        window.setView(graphView);
        graphs.draw();
        window.setView(originalView);
    } else if (currentSubMenu == MAZE_MENU) {
        mazeSolver.draw(window);
    }
    if (inputMode != NONE || !inputText.getString().isEmpty()) {
        window.draw(inputText);
    }
}

// Reset menu state
void NonLinearDataStructureMenu::reset() {
    currentSubMenu = MAIN_MENU;
    avlTree.reset();
    graphs.reset();
    mazeSolver.generateMaze();
    inputText.setString("");
    inputString.clear();
    updatePrompt();
    updateComplexityText();
}
