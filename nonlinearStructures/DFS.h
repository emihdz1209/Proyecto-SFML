#pragma once
#include "MazeSolver.h"
#include <SFML/Graphics.hpp>

class DFS{
    private:

    public:
        static bool solve(MazeSolver &maze, sf::RenderWindow &window);
        static bool solveDFS(MazeSolver &maze, Position pos, sf::RenderWindow &window);
};