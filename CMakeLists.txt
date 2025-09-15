cmake_minimum_required(VERSION 3.16)
project(SFMLHello CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML: gráficos + ventana + sistema
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(sfml_hello src/main.cpp)
target_link_libraries(sfml_hello PRIVATE sfml-graphics sfml-window sfml-system)
