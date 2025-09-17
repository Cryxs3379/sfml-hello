#include "Input.h"
#include <SFML/Graphics.hpp>

sf::Vector2f Input::getMovementDirection() {
    sf::Vector2f direction(0.0f, 0.0f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.0f;
    }
    
    return direction;
}

bool Input::isTurboPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
}

bool Input::shouldClose(const sf::Event& event) {
    return event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && 
            event.key.code == sf::Keyboard::Escape);
}
