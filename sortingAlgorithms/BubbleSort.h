#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

void BubbleSort(std::vector<int> &arr, RenderWindow &window, Text &text, bool &sorting, Font &font);

#endif // BUBBLESORT_H