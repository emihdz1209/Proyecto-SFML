#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

void InsertionSort(std::vector<int>& arr, RenderWindow& window, Text& text, bool& sorting, Font& font);

#endif // INSERTIONSORT_H