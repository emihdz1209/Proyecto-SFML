#ifndef BFS_H
#define BFS_H

#include <SFML/Graphics.hpp>
#include "MazeSolver.h"

class BFS{
    private:

    public:
        static bool solve(MazeSolver &maze, sf::RenderWindow &window);
};

#endif