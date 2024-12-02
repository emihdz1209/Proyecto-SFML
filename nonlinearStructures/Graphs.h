#ifndef GRAPHS_H
#define GRAPHS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;
using namespace sf;

const int INF = numeric_limits<int>::max();

struct Nodo{
    int nodo;
    int distancia;
    vector<int> ruta;
};

class Graphs{
    private:
        RenderWindow &window;
        Font &font;
        vector<int> nodes;
        vector<vector<pair<int, int>>> adjList;
        vector<Vector2f> nodePositions;

    public:
        Graphs(RenderWindow &window, Font &font);
        void generatePredefinedGraph();
        void draw();
        void reset();
        bool nodeExists(int node);
        vector<Nodo> dijkstra(int origen);
        void drawShortestPath(int startNode, int endNode);
    };

#endif // GRAPHS_H