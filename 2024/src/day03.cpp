#include <iostream>
#include "day02.hpp"
#include "utils.hpp"
#include <algorithm>
#include <sstream>

int parseAndMultiply(const std::string& line, int marker) {
    std::string left = "";
    std::string right = "";
    bool separator = false;
    
    for (int i = marker; i < line.size() && i < marker + 8; i++) {
        char c = line[i];
        bool is_digit = std::isdigit(c);
        if (is_digit) {
            if (!separator) {
                left += c;
            } else {
                right += c;
            }
        } else if (c == ',') {
            separator = true;
        } else if (c == ')') {
            // Guard against too large numbers and empty strings
            if (left.empty() || right.empty() || left.length() > 3 || right.length() > 3) {
                return 0;
            }
            return std::stoi(left) * std::stoi(right);
        } else {
            // If we get here, we have an invalid character
            return 0;
        }
    }
    return 0;
}

void day03part01() {
    // Output the header
    std::cout << "\nDay 3 Part 1:\n";
    std::cout << "Scan the lines and count the valid multiplications\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day03.txt");

    int multiplications = 0;
    for (const std::string& line : input) {
        std::vector<int> markers;
        std::string::size_type pos = 0;
        while ((pos = line.find("mul(", pos)) != std::string::npos) {
            pos += 4; 
            markers.push_back(pos);        
        }

        for (int marker : markers) {
            multiplications += parseAndMultiply(line, marker);
        }
    }

    std::cout << "Total multiplications: " << multiplications << std::endl;
}

void findMarkers(const std::string& line, const std::string& keyword, int offset, std::vector<int>& markers) {
    std::string::size_type pos = 0;
    while ((pos = line.find(keyword, pos)) != std::string::npos) {
        pos += offset;
        markers.push_back(pos);
    }
}

/**
 * @brief Find the similarity between 2 lists.
 */
void day03part02() {
    // Output the header
    std::cout << "\nDay 3 Part 2:\n";
    std::cout << "Including enabled/disabled instructions, how many multiplications are performed?\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day03.txt");

    int multiplications = 0;
    bool enabled = true;

    for (const std::string& line : input) {
        std::vector<int> markers;
        findMarkers(line, "mul(", 4, markers);
        findMarkers(line, "do()", 1, markers);
        findMarkers(line, "don't()", 1, markers);

        std::sort(markers.begin(), markers.end());

        for (int marker : markers) {
            if (line.compare(marker - 1, 4, "do()") == 0) {
                enabled = true;
            } else if (line.compare(marker - 1, 7, "don't()") == 0) {
                enabled = false;
            } else if (enabled) {
                multiplications += parseAndMultiply(line, marker);
            }
        }
    }

    // Output the total difference
    std::cout << "Total multiplications: " << multiplications << std::endl;
}

