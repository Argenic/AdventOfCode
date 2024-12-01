#include "utils.hpp"
#include <fstream>
#include <iostream>

namespace utils {
    std::vector<std::string> readLines(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
}
