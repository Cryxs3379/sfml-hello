// ========================================
// INCLUSIÓN DE LIBRERÍAS NECESARIAS
// ========================================

// Incluimos la librería principal de SFML que contiene todas las funciones gráficas
// Graphics.hpp incluye automáticamente: ventanas, formas, colores, eventos, etc.
#include <SFML/Graphics.hpp>

// Incluimos la librería matemática para usar la función sqrt (raíz cuadrada)
// La necesitamos para normalizar el movimiento diagonal
#include <cmath>

// Incluimos librerías para manejo de archivos y directorios
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <vector>
#include <string>

// ========================================
// FUNCIÓN PARA BUSCAR DLLs DE SFML AUTOMÁTICAMENTE
// ========================================

// Esta función busca las DLLs de SFML en las rutas comunes de MSYS2
// y las agrega al PATH del proceso actual
void setupSFMLPath() {
    // Rutas comunes donde MSYS2 instala las DLLs de SFML
    std::vector<std::string> possiblePaths = {
        "C:\\msys64\\ucrt64\\bin",           // UCRT64 (más común)
        "C:\\msys64\\mingw64\\bin",          // MINGW64
        "C:\\msys64\\clang64\\bin",          // CLANG64
        "C:\\msys64\\mingw32\\bin",          // MINGW32
        "C:\\msys64\\usr\\bin"               // MSYS2 general
    };
    
    // Nombre de las DLLs que necesitamos (SFML + dependencias)
    std::vector<std::string> requiredDLLs = {
        "libsfml-system-2.dll",
        "libsfml-graphics-2.dll", 
        "libsfml-window-2.dll",
        "libfreetype-6.dll",
        "libbrotlidec.dll",
        "libbz2-1.dll",
        "libharfbuzz-0.dll",
        "libpng16-16.dll",
        "libgcc_s_seh-1.dll",
        "libstdc++-6.dll",
        "libwinpthread-1.dll"
    };
    
    std::string foundPath = "";
    
    // Buscamos en cada ruta posible
    for (const auto& path : possiblePaths) {
        // Verificamos si al menos las DLLs básicas de SFML están en esta ruta
        bool basicSFMLFound = true;
        std::vector<std::string> basicSFML = {
            "libsfml-system-2.dll",
            "libsfml-graphics-2.dll", 
            "libsfml-window-2.dll"
        };
        
        for (const auto& dll : basicSFML) {
            std::string fullPath = path + "\\" + dll;
            if (!std::filesystem::exists(fullPath)) {
                basicSFMLFound = false;
                break;
            }
        }
        
        // Si encontramos las DLLs básicas de SFML, usamos esta ruta
        if (basicSFMLFound) {
            foundPath = path;
            break;
        }
    }
    
    // Si encontramos una ruta válida, la agregamos al PATH
    if (!foundPath.empty()) {
        // Obtenemos el PATH actual
        char* currentPath = nullptr;
        size_t pathSize = 0;
        _dupenv_s(&currentPath, &pathSize, "PATH");
        
        if (currentPath) {
            // Creamos el nuevo PATH con la ruta de SFML al principio
            std::string newPath = foundPath + ";" + std::string(currentPath);
            
            // Establecemos el nuevo PATH para este proceso
            SetEnvironmentVariableA("PATH", newPath.c_str());
            
            std::cout << "=== CONFIGURACION AUTOMATICA DE SFML ===" << std::endl;
            std::cout << "SFML DLLs encontradas en: " << foundPath << std::endl;
            std::cout << "PATH actualizado correctamente." << std::endl;
            std::cout << "El programa deberia funcionar ahora desde cualquier ubicacion." << std::endl;
            std::cout << "=========================================" << std::endl;
            
            free(currentPath);
        }
    } else {
        std::cout << "ERROR: No se encontraron las DLLs de SFML en las rutas comunes." << std::endl;
        std::cout << "Asegúrate de tener MSYS2 instalado correctamente." << std::endl;
    }
}

// ========================================
// FUNCIÓN PRINCIPAL DEL PROGRAMA
// ========================================

int main() {
    // ========================================
    // CONFIGURACIÓN AUTOMÁTICA DE SFML
    // ========================================
    
    // Buscamos y configuramos automáticamente las DLLs de SFML
    // Esto evita tener que copiar manualmente las DLLs o configurar el PATH
    setupSFMLPath();
    
    // ========================================
    // CONFIGURACIÓN DE LA VENTANA
    // ========================================
    
    // Definimos el tamaño de nuestra ventana en píxeles
    // const significa que estos valores no cambiarán durante la ejecución
    const unsigned WIDTH = 800, HEIGHT = 600;
    
    // Creamos la ventana principal del programa
    // VideoMode define el tamaño (800x600)
    // El segundo parámetro es el título que aparece en la barra de la ventana
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Hello : circulo");
    
    // Limitamos los FPS (Frames Per Second) a 60
    // Esto hace que el juego vaya a velocidad constante en cualquier computadora
    window.setFramerateLimit(60);

    // ========================================
    // CREACIÓN DEL CÍRCULO
    // ========================================
    
    // Creamos un círculo con radio de 80 píxeles
    // El .f al final indica que es un número decimal (float)
    sf::CircleShape circle(80.f);
    
    // Le damos color al círculo (R, G, B)
    // 100 = rojo, 250 = verde, 50 = azul (resultado: verde brillante)
    circle.setFillColor(sf::Color(100, 250, 50));
    
    // Centramos el círculo en la ventana
    // getRadius() nos da el radio del círculo
    // Restamos el radio para que el centro del círculo esté en el centro de la ventana
    circle.setPosition(WIDTH/2.f - circle.getRadius(), HEIGHT/2.f - circle.getRadius());

    // ========================================
    // RELOJ PARA MOVIMIENTO SUAVE
    // ========================================
    
    // Creamos un reloj que nos ayudará a medir el tiempo entre frames
    // Esto es crucial para que el movimiento sea suave independientemente de los FPS
    sf::Clock clock;

    // ========================================
    // BUCLE PRINCIPAL DEL JUEGO
    // ========================================
    
    // Este es el corazón del programa, se ejecuta mientras la ventana esté abierta
    while (window.isOpen()) {
        
        // ========================================
        // MANEJO DE EVENTOS (TECLADO, MOUSE, ETC.)
        // ========================================
        
        // Creamos una variable para almacenar eventos
        sf::Event e;
        
        // pollEvent() revisa si hay algún evento pendiente (tecla presionada, mouse, etc.)
        // Este bucle procesa TODOS los eventos que estén en la cola
        while (window.pollEvent(e)) {
            // Si el usuario hace clic en la X de la ventana, la cerramos
            if (e.type == sf::Event::Closed) window.close();
            
            // Si el usuario presiona la tecla ESC, cerramos la ventana
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window.close();
        }

        // ========================================
        // CÁLCULO DEL MOVIMIENTO
        // ========================================
        
        // Calculamos cuánto tiempo pasó desde el último frame
        // restart() reinicia el reloj y devuelve el tiempo transcurrido
        // asSeconds() convierte ese tiempo a segundos
        float dt = clock.restart().asSeconds();
        
        // Definimos la velocidad base del círculo en píxeles por segundo
        float speed = 250.f;
        
        // Si el usuario mantiene presionado Shift, aumentamos la velocidad (modo turbo)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            speed *= 1.8f; // Multiplicamos por 1.8 (80% más rápido)
        }

        // ========================================
        // DETECCIÓN DE TECLAS DE MOVIMIENTO
        // ========================================
        
        // Creamos un vector para almacenar la dirección del movimiento
        // Vector2f es un vector de 2 componentes (x, y) con números decimales
        sf::Vector2f dir(0.f, 0.f);
        
        // Detectamos si el usuario presiona las teclas de movimiento
        // isKeyPressed() devuelve true si la tecla está siendo presionada AHORA
        // Soporta tanto flechas como WASD para mayor comodidad
        
        // Movimiento hacia la izquierda
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
            dir.x -= 1.f; // Restamos 1 en el eje X (izquierda)
        
        // Movimiento hacia la derecha
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
            dir.x += 1.f; // Sumamos 1 en el eje X (derecha)
        
        // Movimiento hacia arriba
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
            dir.y -= 1.f; // Restamos 1 en el eje Y (arriba, porque Y crece hacia abajo)
        
        // Movimiento hacia abajo
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
            dir.y += 1.f; // Sumamos 1 en el eje Y (abajo)

        // ========================================
        // NORMALIZACIÓN DEL MOVIMIENTO DIAGONAL
        // ========================================
        
        // Si el usuario se está moviendo (en cualquier dirección)
        if (dir.x != 0.f || dir.y != 0.f) {
            // Calculamos la longitud del vector dirección usando el teorema de Pitágoras
            // Esto evita que el movimiento diagonal sea más rápido que el movimiento en ejes
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            
            // Normalizamos el vector (lo hacemos de longitud 1)
            dir.x /= len; 
            dir.y /= len;
            
            // Movemos el círculo en la dirección calculada
            // La fórmula es: posición = dirección × velocidad × tiempo
            circle.move(dir * speed * dt);
        }

        // ========================================
        // DETECCIÓN DE COLISIONES CON BORDES
        // ========================================
        
        // Obtenemos el radio y la posición actual del círculo
        float r = circle.getRadius();
        sf::Vector2f p = circle.getPosition();
        
        // Verificamos y corregimos si el círculo se sale por la izquierda
        if (p.x < 0) p.x = 0;
        
        // Verificamos y corregimos si el círculo se sale por arriba
        if (p.y < 0) p.y = 0;
        
        // Verificamos y corregimos si el círculo se sale por la derecha
        // 2*r es el diámetro del círculo
        if (p.x + 2*r > WIDTH)  p.x = WIDTH  - 2*r;
        
        // Verificamos y corregimos si el círculo se sale por abajo
        if (p.y + 2*r > HEIGHT) p.y = HEIGHT - 2*r;
        
        // Aplicamos la nueva posición (corregida) al círculo
        circle.setPosition(p);

        // ========================================
        // DIBUJADO EN PANTALLA
        // ========================================
        
        // Limpiamos la ventana con un color de fondo oscuro (gris muy oscuro)
        // Esto borra todo lo que se dibujó en el frame anterior
        window.clear(sf::Color(30, 30, 30));
        
        // Dibujamos el círculo en la ventana
        // draw() no muestra nada aún, solo lo prepara para mostrar
        window.draw(circle);
        
        // display() muestra todo lo que se dibujó en pantalla
        // Es como "actualizar" la pantalla
        window.display();
    }
    
    // Cuando el bucle termina (ventana cerrada), el programa termina automáticamente
    return 0;
}