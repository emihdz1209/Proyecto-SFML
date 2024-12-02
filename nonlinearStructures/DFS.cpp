#include "DFS.h"
#include "MazeSolver.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace sf;

bool DFS::solve(MazeSolver &maze, RenderWindow &window){
    return solveDFS(maze, maze.getStart(), window);
}

bool DFS::solveDFS(MazeSolver &maze, Position pos, RenderWindow &window){
    if (pos.x == maze.getEnd().x && pos.y == maze.getEnd().y)
    {
        maze.getGrid()[pos.x][pos.y] = SOLUTION;
        return true;
    }

    maze.getGrid()[pos.x][pos.y] = VISITED;

    vector<Position> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    for (const Position &dir : directions)
    {
        Position newPos(pos.x + dir.x, pos.y + dir.y);
        if (newPos.x >= 0 && newPos.y >= 0 && newPos.x < maze.getGrid().size() && newPos.y < maze.getGrid()[0].size() && (maze.getGrid()[newPos.x][newPos.y] == PATH || maze.getGrid()[newPos.x][newPos.y] == END))
        {
            window.clear(Color(30, 30, 30));
            maze.draw(window);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // errrrm chat, is this recursion?
            if (solveDFS(maze, newPos, window))
            {
                maze.getGrid()[newPos.x][newPos.y] = SOLUTION;
                return true;
            }
        }
    }

    maze.getGrid()[pos.x][pos.y] = PATH;

    window.clear(Color(30, 30, 30));
    maze.draw(window);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    return false;
}