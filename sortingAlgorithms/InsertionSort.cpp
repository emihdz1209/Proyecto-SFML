#include "InsertionSort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

void InsertionSort(vector<int> &arr, RenderWindow &window, Text &text, bool &sorting, Font &font){
    int n = arr.size();
    sorting = true;
    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);
    auto start = chrono::high_resolution_clock::now();

    auto drawState = [&](int current = -1,int referenced = -1){
        window.clear(Color(0, 26, 22));
        window.draw(text);

        float tileWidth = 25.0f;
        float margins = 28.0f;
        float startX = (window.getSize().x - (arr.size() * margins)) / 2.0f;
        float baseY = 400.0f;
        float heightScale = 5.0f;


        // Draw bars
        for (size_t k = 0; k < arr.size(); ++k)
        {

            RectangleShape rectangle(Vector2f(tileWidth, arr[k]*heightScale));
            rectangle.setPosition(startX + k * margins, baseY - arr[k]*heightScale);

            if (k == current || k == referenced)
            {
                rectangle.setFillColor(Color(113, 198, 117));
            }
            else
            {
                rectangle.setFillColor(Color(83, 149, 92));
            }
            window.draw(rectangle);

            Text numberText(to_string(arr[k]), font, 15);
            numberText.setPosition(startX + k * margins, baseY - arr[k]*heightScale - 20);
            window.draw(numberText);
        }

        window.display();
    };
    drawState();
    this_thread::sleep_for(chrono::milliseconds(400));

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            drawState(j + 1, i);
            this_thread::sleep_for(chrono::milliseconds(400));
        }
        arr[j + 1] = key;
        drawState(j + 1, i);
        this_thread::sleep_for(chrono::milliseconds(400));
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    window.clear(Color(0, 26, 22));
    window.draw(text);
    ostringstream oss;
    oss << "Time Complexity: O(n^2)\n";
    oss << "Space Complexity: O(1)\n";
    oss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";

    Text complexityText(oss.str(), font, 20);
    complexityText.setPosition(
        (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
        450.0f);
    complexityText.setFillColor(Color::White);

    drawState();
    window.draw(complexityText);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(3000));
    sorting = false;
}