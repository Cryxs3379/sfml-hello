#include "Math.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

void Math::normalizeVector(sf::Vector2f& vector) {
    const float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length > 0.0f) {
        vector.x /= length;
        vector.y /= length;
    }
}

void Math::constrainToWindow(sf::CircleShape& circle, 
                           unsigned int width, unsigned int height) {
    const float radius = circle.getRadius();
    sf::Vector2f position = circle.getPosition();
    
    position.x = std::max(0.0f, std::min(position.x, 
                    static_cast<float>(width) - 2.0f * radius));
    position.y = std::max(0.0f, std::min(position.y, 
                    static_cast<float>(height) - 2.0f * radius));
    
    circle.setPosition(position);
}
