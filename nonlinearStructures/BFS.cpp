#include "BFS.h"
#include "MazeSolver.h"
#include <thread>
#include <queue>

using namespace std;
using namespace sf;

bool BFS::solve(MazeSolver &maze, RenderWindow &window){
    queue<Position> q;
    q.push(maze.getStart());
    vector<vector<bool>> visited(maze.getGrid().size(), vector<bool>(maze.getGrid()[0].size(), false));
    visited[maze.getStart().x][maze.getStart().y] = true; // Mark the start position as visited

    vector<Position> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Possible movement directions

    while (!q.empty()){
        Position current = q.front();
        q.pop();

        // Check if we have reached the end position
        if (current.x == maze.getEnd().x && current.y == maze.getEnd().y)
        {
            maze.getGrid()[current.x][current.y] = SOLUTION;
            return true;
        }

        // Explore all possible directions
        for (const Position &direction : directions)
        {
            int nx =current.x + direction.x;
            int ny = current.y + direction.y;
            if (nx >= 0 && ny >= 0 && nx < maze.getGrid().size() && ny < maze.getGrid()[0].size() && !visited[nx][ny] && (maze.getGrid()[nx][ny] == PATH || maze.getGrid()[nx][ny] == END))
            {
                visited[nx][ny] = true; 
                q.push({nx, ny});
                maze.getGrid()[nx][ny] = VISITED;

                window.clear(Color(30, 30, 30));
                maze.draw(window);
                window.display();

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }

    return false;
}