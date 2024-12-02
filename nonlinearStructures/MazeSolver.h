#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Cell{
    WALLBORDER,
    PATH,
    VISITED,
    START,
    END,
    SOLUTION
};

struct Position{
    int x, y;
    Position(int x, int y) : x(x), y(y) {}
};

class MazeSolver{
    private:
        int mazeWidth, mazeHeight, tileSize;
        Position start, end;
        std::vector<std::vector<Cell>> grid;

        void generateDFS(Position pos);

    public:
        MazeSolver(int mazeWidth, int mazeHeight, int tileSize);
        void generateMaze();
        void draw(sf::RenderWindow &window);
        bool solveBFS(sf::RenderWindow &window);
        Position getStart() const { return start; }
        Position getEnd() const { return end; }
        std::vector<std::vector<Cell>>& getGrid() { return grid; }
};