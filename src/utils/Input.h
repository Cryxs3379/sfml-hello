#pragma once
#include <SFML/Graphics.hpp>

namespace Input {
    sf::Vector2f getMovementDirection();
    bool isTurboPressed();
    bool shouldClose(const sf::Event& event);
}
