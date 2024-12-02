#include "MazeSolver.h"
#include <random>
#include <algorithm>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;
using namespace sf;

MazeSolver::MazeSolver(int mazeWidth, int mazeHeight, int tileSize)
    : mazeWidth(mazeHeight), mazeHeight(mazeHeight), tileSize(tileSize), start(1, 1), end(mazeWidth - 2, mazeHeight - 2)
{
    grid.resize(mazeWidth, vector<Cell>(mazeHeight, WALLBORDER));
    generateMaze();
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void MazeSolver::generateMaze()
{
    for (int x = 0; x < mazeWidth; x++)
    {
        for (int y = 0; y < mazeHeight; y++)
        {
            grid[x][y] = WALLBORDER;
        }
    }
    generateDFS(start);
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void MazeSolver::generateDFS(Position pos)
{
    grid[pos.x][pos.y] = PATH;
    vector<Position> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    shuffle(directions.begin(), directions.end(), mt19937(random_device()()));

    for (const Position &direction : directions)
    {
        int nx = pos.x + direction.x;
        int ny = pos.y + direction.y;

        if (nx > 0 && ny > 0 && nx < mazeWidth - 1 && ny < mazeHeight - 1 && grid[nx][ny] == WALLBORDER)
        {
            grid[nx][ny] = PATH;
            grid[pos.x + direction.x / 2][pos.y + direction.y / 2] = PATH;
            generateDFS({nx, ny});
        }
    }
}

bool MazeSolver::solveBFS(sf::RenderWindow &window)
{
    queue<Position> q;
    q.push(start);
    vector<vector<bool>> visited(mazeWidth, vector<bool>(mazeHeight, false));
    visited[start.x][start.y] = true;
    vector<Position> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    while (!q.empty())
    {
        Position current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y)
        {
            grid[current.x][current.y] = SOLUTION;
            return true;
        }

        for (const Position &direction : directions)
        {
            int nx = current.x + direction.x;
            int ny = current.y + direction.y;

            if (nx >= 0 && ny >= 0 && nx < mazeWidth && ny < mazeHeight && !visited[nx][ny] && (grid[nx][ny] == PATH || grid[nx][ny] == END))
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                grid[nx][ny] = VISITED;

                // Draw the maze at each step
                window.clear(Color(30, 30, 30));
                draw(window);
                window.display();

                // Add a small delay for the animation
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }

    return false;
}

void MazeSolver::draw(RenderWindow &window){
    float scale = 0.4f;
    float offsetX = (window.getSize().x - mazeWidth * tileSize * scale) / 2.0f;
    float offsetY = 200.0f;
    for (int x = 0; x < mazeWidth; x++){
        for (int y = 0; y < mazeHeight; y++){
            RectangleShape cell(Vector2f(tileSize * scale, tileSize * scale));
            cell.setPosition(offsetX + x * tileSize * scale, offsetY + y * tileSize * scale);

            switch (grid[x][y]){
                case START:
                    cell.setFillColor(Color::Green);
                    break;
                case WALLBORDER:
                    cell.setFillColor(Color(39,22,24));
                    break;
                case PATH:
                    cell.setFillColor(Color(220,241,221));
                    break;
                case VISITED:
                    cell.setFillColor(Color(241, 220, 240));
                    break;
                case END:
                    cell.setFillColor(Color::Red);
                    break;
                case SOLUTION:
                    cell.setFillColor(Color::Yellow);
                    break;
            }

            window.draw(cell);
        }
    }
}