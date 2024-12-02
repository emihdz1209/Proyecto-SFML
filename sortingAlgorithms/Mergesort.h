#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <SFML/Graphics.hpp>

void MergeSort(std::vector<int> &arr, int left, int right, sf::RenderWindow &window, sf::Text &text, bool &sorting, sf::Font &font);

#endif // MERGESORT_H