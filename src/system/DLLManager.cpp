#include "DLLManager.h"
#include <iostream>
#include <filesystem>
#include <windows.h>

const std::vector<std::string> DLLManager::possiblePaths = {
    "C:\\msys64\\ucrt64\\bin",
    "C:\\msys64\\mingw64\\bin",
    "C:\\msys64\\clang64\\bin",
    "C:\\msys64\\mingw32\\bin",
    "C:\\msys64\\usr\\bin"
};

bool DLLManager::setupSFMLPath() {
    const std::vector<std::string> sfmlDLLs = {
        "libsfml-system-2.dll",
        "libsfml-graphics-2.dll",
        "libsfml-window-2.dll"
    };
    return setupLibrary(sfmlDLLs, "SFML");
}

bool DLLManager::setupLibrary(const std::vector<std::string>& dlls, 
                             const std::string& libraryName) {
    std::string foundPath;
    if (findLibraryPath(dlls, foundPath)) {
        updatePath(foundPath);
        std::cout << "=== CONFIGURACION AUTOMATICA DE " << libraryName << " ===" << std::endl;
        std::cout << libraryName << " DLLs encontradas en: " << foundPath << std::endl;
        std::cout << "PATH actualizado correctamente." << std::endl;
        std::cout << "=========================================" << std::endl;
        return true;
    }
    
    std::cout << "ERROR: No se encontraron las DLLs de " << libraryName << std::endl;
    std::cout << "Asegúrate de tener MSYS2 instalado correctamente." << std::endl;
    return false;
}

bool DLLManager::findLibraryPath(const std::vector<std::string>& dlls, 
                                std::string& foundPath) {
    for (const auto& path : possiblePaths) {
        bool allFound = true;
        for (const auto& dll : dlls) {
            if (!std::filesystem::exists(path + "\\" + dll)) {
                allFound = false;
                break;
            }
        }
        if (allFound) {
            foundPath = path;
            return true;
        }
    }
    return false;
}

void DLLManager::updatePath(const std::string& path) {
    char* currentPath = nullptr;
    size_t pathSize = 0;
    _dupenv_s(&currentPath, &pathSize, "PATH");
    
    if (currentPath) {
        std::string newPath = path + ";" + std::string(currentPath);
        SetEnvironmentVariableA("PATH", newPath.c_str());
        free(currentPath);
    }
}
