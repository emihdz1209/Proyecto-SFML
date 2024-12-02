#include "Graphs.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;

Graphs::Graphs(RenderWindow &window, Font &font): window(window), font(font){}

void Graphs::generatePredefinedGraph(){
    reset();

    int nodeCount = 9;
    for (int i = 0; i < nodeCount; ++i) {
        nodes.push_back(i);
    }

    adjList.resize(nodes.size());
    std::srand(std::time(0));


    auto addEdge = [&](int u, int v) {
        int weight = rand() % 91 + 10;
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});  // Bidirectional
    };

    // Randomly add edges
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = i + 1; j < nodeCount; ++j) {
            if (rand() % 2 == 0) {
                addEdge(i, j);
            }
        }
    }

    nodePositions = {
            {100, 100},  // Node 0
            {250, 100},  // Node 1
            {400, 100},  // Node 2
            {600, 100},  // Node 3
            {750, 150},  // Node 4
            {900, 250},  // Node 5
            {1050, 300}, // Node 6
            {1200, 250}, // Node 7
            {1350, 150}  // Node 8
    };

    nodePositions[4] = {750, 200};
    nodePositions[5] = {900, 300};
    nodePositions[6] = {1050, 350};
}

void Graphs::draw(){
    View originalView = window.getView();

    View graphView(FloatRect(0, 0, window.getSize().x *2, window.getSize().y));
    graphView.setViewport(FloatRect(0, 0.3f, 1, 0.6f));
    window.setView(graphView);

    for (size_t i = 0; i < nodes.size(); ++i){
        for (const auto &edge : adjList[i]){
            int neighbor = edge.first;
            int weight = edge.second;
            Vertex line[] = {
                Vertex(nodePositions[i], Color::White),
                Vertex(nodePositions[neighbor], Color::White)};
            window.draw(line, 2, Lines);
            if (weight != INF){
                Text weightText;
                weightText.setFont(font);
                weightText.setFillColor(Color::Yellow);
                weightText.setCharacterSize(16);
                weightText.setString(to_string(weight));



                Vector2f midPoint = (nodePositions[i] + nodePositions[neighbor]) / 2.0f;
                midPoint.y -= 10;
                weightText.setPosition(midPoint);
                window.draw(weightText);
            }
        }
    }

    for (size_t i = 0; i < nodes.size(); ++i){
        CircleShape circle(25);
        circle.setPosition(nodePositions[i] - Vector2f(20, 20));
        circle.setFillColor(Color(113, 198, 117));
        window.draw(circle);

        Text nodeText;
        nodeText.setFont(font);
        nodeText.setString(to_string(nodes[i]));
        nodeText.setCharacterSize(22);
        nodeText.setFillColor(Color(15, 41, 35));
        nodeText.setPosition(nodePositions[i] - Vector2f(2, -2));
        window.draw(nodeText);
    }

    window.setView(originalView);
}

void Graphs::reset()
{
    nodes.clear();
    adjList.clear();
    nodePositions.clear();
}

// Function to perform Dijkstra's algorithm
vector<Nodo> Graphs::dijkstra(int origen)
{
    int n = nodes.size();
    vector<int> distancias(n, INF);
    vector<vector<int>> rutas(n);
    distancias[origen] = 0;
    rutas[origen] = {origen};

    // Priority queue: (accumulated distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, origen});

    while (!pq.empty())
    {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (distancia_actual > distancias[nodo_actual])
            continue;

        // Explore neighbors
        for (const auto &vecino : adjList[nodo_actual])
        {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;

            int nueva_distancia = distancia_actual + peso_arista;

            if (nueva_distancia < distancias[nodo_vecino])
            {
                distancias[nodo_vecino] = nueva_distancia;
                rutas[nodo_vecino] = rutas[nodo_actual];
                rutas[nodo_vecino].push_back(nodo_vecino);
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }

    vector<Nodo> resultado;
    for (int i = 0; i < n; ++i)
    {
        if (distancias[i] == INF)
        {
            distancias[i] = -1; // Mark as unreachable
            rutas[i].clear();
        }
        resultado.push_back({i, distancias[i], rutas[i]});
    }
    return resultado;
}

bool Graphs::nodeExists(int node)
{
    return find(nodes.begin(), nodes.end(), node) != nodes.end();
}

// Function to draw the shortest path
void Graphs::drawShortestPath(int startNode, int endNode)
{
    if (!nodeExists(startNode) || !nodeExists(endNode))
    {
        return;
    }

    vector<Nodo> dijkstraResult = dijkstra(startNode);
    vector<int> path = dijkstraResult[endNode].ruta;

    if (path.empty())
    {
        return;
    }

    // Draw the shortest path
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        int currentNode = path[i];
        int nextNode = path[i + 1];

        // Line between nodes
        Vertex line[] = {
            Vertex(nodePositions[currentNode], Color::Red),
            Vertex(nodePositions[nextNode], Color::Red)};
        window.draw(line, 2, Lines);
    }
}