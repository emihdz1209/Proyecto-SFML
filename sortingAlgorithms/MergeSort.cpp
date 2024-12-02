#include "Mergesort.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace sf;

void drawState(vector<int> &arr, RenderWindow &window, Text &text, Font &font,int left, int right, int activeLeft = -1, int activeRight = -1){
    window.clear(Color(0, 26, 22));
    window.draw(text);
    float tileWidth = 25.0f;
    float margins = 28.0f;
    float startX = (window.getSize().x - (arr.size() * margins)) / 2.0f;
    float baseY = 400.0f;
    float heightScale = 5.0f;

    for (size_t k = 0; k < arr.size(); ++k){
        RectangleShape rectangle(Vector2f(tileWidth, arr[k]*heightScale));
        rectangle.setPosition(startX + k * margins, baseY - arr[k]*heightScale);
        if (k == activeLeft || k == activeRight){
            rectangle.setFillColor(Color(113, 198, 117));
        }
        else if (k == (left + right) / 2 && left != right){
            rectangle.setFillColor(Color(144, 238, 144));
        }
        else{
            rectangle.setFillColor(Color(83, 149, 92));
        }
        window.draw(rectangle);

        Text numberText(to_string(arr[k]), font, 15);
        numberText.setPosition(startX + k * margins, baseY - arr[k]*heightScale - 20);
        window.draw(numberText);
    }
    window.display();
}

void merge(vector<int> &arr, int left, int mid, int right, RenderWindow &window, Text &text, bool &sorting, Font &font){
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right){
        drawState(arr, window, text, font, left, right, i, j);
        this_thread::sleep_for(chrono::milliseconds(300));
        if (arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid){
        drawState(arr, window, text, font, left, right, i, -1);
        this_thread::sleep_for(chrono::milliseconds(300));
        temp[k++] = arr[i++];
    }
    while (j <= right){
        drawState(arr, window, text, font, left, right, -1, j);
        this_thread::sleep_for(chrono::milliseconds(300));
        temp[k++] = arr[j++];
    }
    for (i = 0; i < k; i++){
        arr[left + i] = temp[i];
    }

    drawState(arr, window, text, font, left, right);
    this_thread::sleep_for(chrono::milliseconds(300));
}

void MergeSort(vector<int> &arr, int left, int right, RenderWindow &window, Text &text, bool &sorting, Font &font){
    static auto start = chrono::high_resolution_clock::now();

    text.setPosition(
        (window.getSize().x - text.getLocalBounds().width) / 2.0f,
        50.0f);

    if (left < right){
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid, window, text, sorting, font);
        MergeSort(arr, mid + 1, right, window, text, sorting, font);
        merge(arr, left, mid, right, window, text, sorting, font);
    }
    if (left == 0 && right == arr.size() - 1){
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        ostringstream oss;
        oss << "Time Complexity: O(n log n)\n";
        oss << "Space Complexity: O(n)\n";
        oss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";

        Text complexityText(oss.str(), font, 20);
        complexityText.setPosition(
            (window.getSize().x - complexityText.getLocalBounds().width) / 2.0f,
            450.0f);
        complexityText.setFillColor(Color::White);

        drawState(arr, window, text, font, 0, arr.size() - 1);
        window.draw(complexityText);
        window.display();

        this_thread::sleep_for(chrono::milliseconds(3000));
        sorting = false;
    }
}