#include "LinearSearch.h"
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace sf;

void renderList(const vector<int> &arr, int currentPos, RenderWindow &window, Font &font){
    float divWidth = window.getSize().x;
    float tileWidth = 40.0f;
    float margins = 50.0f;
    float totalWidth = arr.size() * margins;
    float x = (divWidth - totalWidth) / 2.0f;
    float y = 300.0f;

    for (size_t i = 0; i < arr.size(); i++){
        RectangleShape rect(Vector2f(tileWidth, tileWidth));
        rect.setPosition(x + i * margins, y);
        rect.setFillColor(i == currentPos ? Color(113, 198, 117) : Color(83, 149, 92));
        rect.setOutlineThickness(2);
        rect.setOutlineColor(Color::White);

        Text text;
        text.setFont(font);
        text.setString(to_string(arr[i]));
        text.setCharacterSize(20);
        text.setFillColor(Color(15, 41, 35));
        text.setPosition(x + i * 50 + 12, y + 18);

        window.draw(rect);
        window.draw(text);
    }
}

// Function to perform linear search on the array
int LinearSearch(const vector<int> &arr, int target,RenderWindow &window, Text &statusText,bool &searching, Font &font){
    static int currentPos = 0;
    static Clock clock;
    static auto start = chrono::high_resolution_clock::now();

    if (currentPos == 0){
        start = chrono::high_resolution_clock::now();
    }

    if (clock.getElapsedTime().asSeconds() >= 0.5f){
        if (currentPos < arr.size()){
            if (arr[currentPos] == target){
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;
                stringstream ss;
                ss << "Found " << target << " at position " << currentPos << "\n\n";
                ss << "Time Complexity: O(n)\n";
                ss << "Space Complexity: O(1)\n";
                ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
                statusText.setString(ss.str());
                searching = false;
                int foundPos = currentPos;
                currentPos = 0;
                return foundPos;
            }
            currentPos++;
            clock.restart(); // Restart the clock for the next step
        }
        else{
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            stringstream ss;
            ss << target << " not found in array\n";
            ss << "Time Complexity: O(n)\n";
            ss << "Space Complexity: O(1)\n";
            ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
            statusText.setString(ss.str());
            searching = false;
            currentPos = 0;
            return -1;
        }
    }

    renderList(arr, currentPos - 1, window, font);
    window.draw(statusText);
    return -1;
}