#pragma once
#include <vector>
#include <string>

class DLLManager {
public:
    static bool setupSFMLPath();
    static bool setupLibrary(const std::vector<std::string>& dlls, 
                           const std::string& libraryName);
private:
    static const std::vector<std::string> possiblePaths;
    static bool findLibraryPath(const std::vector<std::string>& dlls, 
                               std::string& foundPath);
    static void updatePath(const std::string& path);
};
