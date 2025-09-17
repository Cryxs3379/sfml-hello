#pragma once
#include <SFML/Graphics.hpp>

namespace GameConfig {
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;
    constexpr float CIRCLE_RADIUS = 80.0f;
    constexpr float BASE_SPEED = 250.0f;
    constexpr float TURBO_MULTIPLIER = 1.8f;
    constexpr unsigned int TARGET_FPS = 60;
    const sf::Color BACKGROUND_COLOR(30, 30, 30);
    const sf::Color CIRCLE_COLOR(100, 250, 50);
}
