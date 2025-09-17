#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace Math {
    void normalizeVector(sf::Vector2f& vector);
    void constrainToWindow(sf::CircleShape& circle, 
                          unsigned int width, unsigned int height);
}
