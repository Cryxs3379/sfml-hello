#include <SFML/Graphics.hpp>
#include <cmath> // sqrt

int main() {
    const unsigned WIDTH = 800, HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Hello : circulo");
    window.setFramerateLimit(60);

    // Circulo
    sf::CircleShape circle(80.f); // radio
    circle.setFillColor(sf::Color(100, 250, 50));
    // centrar
    circle.setPosition(WIDTH/2.f - circle.getRadius(), HEIGHT/2.f - circle.getRadius());

    sf::Clock clock; // para deltaTime (movimiento suave, independiente de FPS)

    while (window.isOpen()) {
        // --- eventos de ventana/teclas (cerrar con X o ESC)
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();
        }

        // --- movimiento en tiempo real
        float dt = clock.restart().asSeconds();   // segundos desde el último frame
        float speed = 250.f;                      // pixeles por segundo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            speed *= 1.8f; // turbo con Shift
        }

        sf::Vector2f dir(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1.f;

        // velocidad constante en diagonales (normalizamos)
        if (dir.x != 0.f || dir.y != 0.f) {
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            dir.x /= len; dir.y /= len;
            circle.move(dir * speed * dt);
        }

        // --- limitar dentro de la ventana
        float r = circle.getRadius();
        sf::Vector2f p = circle.getPosition();
        if (p.x < 0) p.x = 0;
        if (p.y < 0) p.y = 0;
        if (p.x + 2*r > WIDTH)  p.x = WIDTH  - 2*r;
        if (p.y + 2*r > HEIGHT) p.y = HEIGHT - 2*r;
        circle.setPosition(p);

        // --- dibujado
        window.clear(sf::Color(30, 30, 30));
        window.draw(circle);
        window.display();
    }
}
