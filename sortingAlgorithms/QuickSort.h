#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <SFML/Graphics.hpp>

void QuickSort(std::vector<int> &arr, int left, int right, sf::RenderWindow &window, sf::Text &text, bool &sorting, sf::Font &font);

#endif // QUICKSORT_H