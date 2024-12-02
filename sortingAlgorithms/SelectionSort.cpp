#include "SelectionSort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

void renderList(const vector<int> &arr, RenderWindow &window, Text &text, Font &font, int highlight1 = -1, int highlight2 = -1){
    window.clear(Color(0, 26, 22));
    window.draw(text);

    float tileWidth = 50.0f;
    float margins = 66.0f;
    float startX = (window.getSize().x - (arr.size() * margins)) / 2.0f;
    float baseY = 400.0f;
    float heightScale = 5.0f;

    for (size_t k = 0; k < arr.size(); ++k) {
        RectangleShape rectangle(Vector2f(tileWidth, arr[k] * heightScale)); // Scale the height
        rectangle.setPosition(startX + k * margins, baseY - arr[k] * heightScale); // Adjust position to match scaled height

        if (k == highlight1 || k == highlight2) {
            rectangle.setFillColor(Color(113, 198, 117));
        } else {
            rectangle.setFillColor(Color(83, 149, 92));
        }
        window.draw(rectangle);

        Text numberText(to_string(arr[k]), font, 15);
        numberText.setPosition(startX + k * margins, baseY - arr[k] * heightScale - 20); // Adjust text position to match scaled height
        window.draw(numberText);
    }
    window.display();
}

void SelectionSort(vector<int> &arr, RenderWindow &window, Text &text, bool &sorting, Font &font)
{
    int n = arr.size();
    sorting = true;

    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    auto start = chrono::high_resolution_clock::now();
    
    renderList(arr, window, text, font);
    this_thread::sleep_for(chrono::milliseconds(300));

    for (int i = 0; i < n - 1; i++){
        int minVal = i;

        for (int j = i + 1; j < n; j++){
            renderList(arr, window, text, font, minVal, j);
            this_thread::sleep_for(chrono::milliseconds(300));

            if (arr[j] < arr[minVal]){
                minVal = j;
            }
        }

        if (minVal != i){
            swap(arr[i], arr[minVal]);
            renderList(arr, window, text, font, i, minVal);
            this_thread::sleep_for(chrono::milliseconds(300));
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    ostringstream oss;
    oss << "Time Complexity: O(n^2)\n";
    oss << "Space Complexity: O(1)\n";
    oss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";

    Text complexityText(oss.str(), font, 20);
    complexityText.setPosition(
        (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
        450.0f);
    complexityText.setFillColor(Color::White);

    renderList(arr, window, text, font);
    window.draw(complexityText);
    window.display();

    this_thread::sleep_for(chrono::milliseconds(3000));
    sorting = false;
}