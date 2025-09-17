#include "system/DLLManager.h"
#include "game/Game.h"
#include <iostream>

int main() {
    // Configurar DLLs automáticamente
    if (!DLLManager::setupSFMLPath()) {
        std::cerr << "Error: No se pudieron configurar las DLLs de SFML" << std::endl;
        return -1;
    }
    
    // Crear y ejecutar el juego
    Game game;
    game.run();
    
    return 0;
}