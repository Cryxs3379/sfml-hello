#include "Game.h"
#include "../utils/Input.h"
#include "../utils/Math.h"
#include "../utils/Config.h"
#include <SFML/Graphics.hpp>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Hello : circulo") {
    window.setFramerateLimit(GameConfig::TARGET_FPS);
    
    circle.setRadius(GameConfig::CIRCLE_RADIUS);
    circle.setFillColor(GameConfig::CIRCLE_COLOR);
    
    const float centerX = (WINDOW_WIDTH - 2.0f * GameConfig::CIRCLE_RADIUS) / 2.0f;
    const float centerY = (WINDOW_HEIGHT - 2.0f * GameConfig::CIRCLE_RADIUS) / 2.0f;
    circle.setPosition(centerX, centerY);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (Input::shouldClose(event)) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    float currentSpeed = GameConfig::BASE_SPEED;
    if (Input::isTurboPressed()) {
        currentSpeed *= GameConfig::TURBO_MULTIPLIER;
    }
    
    sf::Vector2f direction = Input::getMovementDirection();
    if (direction.x != 0.0f || direction.y != 0.0f) {
        Math::normalizeVector(direction);
        circle.move(direction * currentSpeed * deltaTime);
    }
    
    Math::constrainToWindow(circle, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::render() {
    window.clear(GameConfig::BACKGROUND_COLOR);
    window.draw(circle);
    window.display();
}
