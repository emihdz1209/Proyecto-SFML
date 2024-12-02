// LinearSearch.h
#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include <SFML/Graphics.hpp>
#include <vector>

int LinearSearch(const std::vector<int> &arr, int target,sf::RenderWindow &window, sf::Text &statusText,bool &searching, sf::Font &font);
#endif