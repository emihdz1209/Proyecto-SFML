#include "QuickSort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

void QuickSort(vector<int> &array, int left, int right, RenderWindow &window, Text &text, bool &sorting, Font &font)
{
    static auto start = chrono::high_resolution_clock::now();

    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    int i = left;
    int j = right;
    int pivot = array[(left + right) / 2];
    auto drawState = [&]()
    {
        window.clear(Color(0, 26, 22));
        window.draw(text);

        float tileWidth = 25.0f;
        float margins = 28.0f;
        float startX = (window.getSize().x - (array.size() * margins)) / 2.0f;
        float baseY = 400.0f;
        float heightScale = 5.0f;

        for (size_t k = 0; k < array.size(); ++k){
            RectangleShape rectangle(Vector2f(tileWidth, array[k]*heightScale));
            rectangle.setPosition(startX + k * margins, baseY - array[k]*heightScale);
            if (k == i || k == j){
                rectangle.setFillColor(Color(113, 198, 117));
            }
            else if (k == (left + right) / 2){
                rectangle.setFillColor(Color(144, 238, 144));
            }
            else{
                rectangle.setFillColor(Color(83, 149, 92));
            }
            window.draw(rectangle);

            Text numberText(to_string(array[k]), font, 15);
            numberText.setPosition(startX + k * margins, baseY - array[k]*heightScale - 20);
            window.draw(numberText);
        }

        window.display();
    };

    drawState();
    this_thread::sleep_for(chrono::milliseconds(500));
    while (i <= j){
        while (i <= right && array[i] < pivot){
            i++;
            drawState();
        }
        while (j >= left && array[j] > pivot){
            j--;
            drawState();
        }
        if (i <= j){
            swap(array[i], array[j]);
            i++;
            j--;
            drawState();
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    if (left < j)
    {
        QuickSort(array, left, j, window, text, sorting, font);
    }
    if (i < right)
    {
        QuickSort(array, i, right, window, text, sorting, font);
    }

    // Final State handler
    if (left == 0 && right == array.size() - 1){
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        // Draw complexity text at bottom
        ostringstream oss;
        oss << "Time Complexity: O(n log n)\n";
        oss << "Space Complexity: O(log n)\n";
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
}