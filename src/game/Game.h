#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
    
private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    sf::RenderWindow window;
    sf::CircleShape circle;
    sf::Clock clock;
    
    static constexpr unsigned int WINDOW_WIDTH = 800;
    static constexpr unsigned int WINDOW_HEIGHT = 600;
};
