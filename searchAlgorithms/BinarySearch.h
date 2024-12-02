// BinarySearch.h
#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

int BinarySearch(std::vector<int> &arr, int target,sf::RenderWindow &window, sf::Text &statusText,bool &searching, sf::Font &font);

#endif