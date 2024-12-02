#pragma once
#include <SFML/Graphics.hpp>
#include "nonlinearStructures/AVLTree.h"
#include "nonlinearStructures/Graphs.h"
#include "nonlinearStructures/MazeSolver.h"
#include "nonlinearStructures/BFS.h"
#include "nonlinearStructures/DFS.h"

class NonLinearDataStructureMenu
{
private:
    sf::RenderWindow &window; 
    sf::Font &font;
    sf::Font &titleFont;
    sf::Text titleText;
    sf::Text promptText;     
    sf::Text backText;        
    sf::Text inputText;       
    sf::Text complexityText;  
    std::string inputString;  
    AVLTree avlTree;         
    Graphs graphs;            
    MazeSolver mazeSolver;    

    // Enumerations for submenus
    enum SubMenu
    {
        MAIN_MENU,
        AVL_TREE_MENU,
        GRAPH_MENU,
        MAZE_MENU
    } currentSubMenu; 

    // Enumerations for input modes
    enum InputMode
    {
        NONE,
        INSERT,
        DELETE,
        SOLVE_BFS,
        SOLVE_DFS
    } inputMode; 

    void initializeTexts();       
    void updatePrompt();          
    void updateComplexityText(); 

public:
    NonLinearDataStructureMenu(sf::RenderWindow &window, sf::Font &font, sf::Font &titleFont);
    void handleEvents(sf::Event &event); 
    void draw(); 
    void reset(); 
};