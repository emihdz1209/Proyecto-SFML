#include "BinarySearch.h"
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace sf;

void renderList(const vector<int> &arr, int left, int right, int mid, RenderWindow &window, Font &font){
    float divWidth = window.getSize().x;
    float divHeight = window.getSize().y;
    float arrayWidth = arr.size() * 50;
    float x = (divWidth - arrayWidth) / 2;
    float y = (divHeight - 40) / 2;

    for (size_t i = 0; i < arr.size(); i++){
        RectangleShape rect(Vector2f(40, 40));
        rect.setPosition(x + i * 50, y);
        if (i == mid){
            rect.setFillColor(Color(248, 194, 119)); // Highlight the middle element
        }
        else if (i >= left && i <= right){
            rect.setFillColor(Color(113, 198, 117)); // Highlight the current search range
        }
        else{
            rect.setFillColor(Color(83, 149, 92)); // Default color for other elements
        }

        rect.setOutlineThickness(3);
        rect.setOutlineColor(Color::White);

        Text text;
        text.setFont(font);
        text.setString(to_string(arr[i]));
        text.setFillColor(Color(15, 41, 35));
        text.setCharacterSize(20);
        text.setPosition(x + i * 50 + 12, y + 18);

        window.draw(rect);
        window.draw(text);
    }
}

int BinarySearch(vector<int> &arr, int target,RenderWindow &window, Text &statusText,bool &searching, Font &font){
    sort(arr.begin(), arr.end()); // Ensure the array is sorted

    static int left = 0;
    static int right = arr.size() - 1;
    static int mid = left + (right - left) / 2;
    static Clock clock;
    static auto start = chrono::high_resolution_clock::now();

    if (left == 0 && right == arr.size() - 1){
        start = chrono::high_resolution_clock::now(); 
    }

    if (clock.getElapsedTime().asSeconds() >= 0.5f){
        if (left <= right){
            mid = left + (right - left) / 2;
            if (arr[mid] == target){
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;

                stringstream ss;
                ss << "Found " << target << " at position " << mid << "\n";
                ss << "Time Complexity: O(log n)\n";
                ss << "Space Complexity: O(1)\n";
                ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
                statusText.setString(ss.str());
                searching = false;
                int foundPos = mid;
                left = 0;
                right = arr.size() - 1;
                return foundPos;
            }

            if (arr[mid] < target){
                left = mid + 1;
            }
            else{
                right = mid - 1; // Search in the left half
            }

            clock.restart(); // Restart the clock for the next step
        }
        else{
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;
            stringstream ss;
            ss << target << " not found in array\n";
            ss << "Time Complexity: O(log n)\n";
            ss << "Space Complexity: O(1)\n";
            ss << "Execution Time: " << fixed << setprecision(6) << elapsed.count() << " seconds";
            statusText.setString(ss.str());
            searching = false;
            right = arr.size() - 1;
            left = 0;
            return -1;
        }
    }

    renderList(arr, left, right, mid, window, font);
    window.draw(statusText); 
    return -1;
}