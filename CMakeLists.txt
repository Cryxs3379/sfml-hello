# ========================================
# CONFIGURACIÓN BÁSICA DE CMAKE
# ========================================

# Le decimos a CMake que necesitamos la versión 3.16 o superior para funcionar
# CMake es una herramienta que nos ayuda a compilar proyectos de C++
cmake_minimum_required(VERSION 3.16)

# Definimos el nombre de nuestro proyecto y que usaremos C++
# Esto crea variables internas que CMake usará durante la compilación
project(SFMLHello CXX)

# ========================================
# CONFIGURACIÓN DEL COMPILADOR DE C++
# ========================================

# Le decimos al compilador que use el estándar C++17
# C++17 incluye características modernas como auto, constexpr, etc.
set(CMAKE_CXX_STANDARD 17)

# Hacemos que C++17 sea OBLIGATORIO, no opcional
# Si el compilador no soporta C++17, dará error
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================================
# BÚSQUEDA Y CONFIGURACIÓN DE SFML
# ========================================

# Buscamos la librería SFML en el sistema
# SFML es una librería que nos permite crear ventanas, dibujar gráficos, etc.
# REQUIRED significa que si no encuentra SFML, la compilación fallará
# COMPONENTS especifica qué partes de SFML necesitamos:
#   - graphics: para dibujar formas, texturas, etc.
#   - window: para crear y manejar ventanas
#   - system: para funciones básicas como relojes, vectores, etc.
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# ========================================
# CREACIÓN DEL EJECUTABLE
# ========================================

# Creamos un ejecutable llamado "sfml_hello" usando el archivo src/main.cpp
# Un ejecutable es el archivo .exe que podrás ejecutar
add_executable(sfml_hello src/main.cpp)

# ========================================
# ENLACE DE LIBRERÍAS
# ========================================

# Le decimos a CMake que nuestro ejecutable necesita usar las librerías de SFML
# PRIVATE significa que solo nuestro ejecutable usa estas librerías
# Sin esto, el compilador no sabría dónde encontrar las funciones de SFML
target_link_libraries(sfml_hello PRIVATE sfml-graphics sfml-window sfml-system)
