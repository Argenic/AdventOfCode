#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include "day02.hpp"
#include "utils.hpp"

void day03part01() {
    std::cout << "\nDay 3 Part 1:\n";
    std::cout << "Scan the lines and count the valid multiplications\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day03.txt");

    int multiplications = 0;
    std::regex marker_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch match;

    for (const std::string& line : input) {
        std::string::const_iterator search_start(line.cbegin());
        while (std::regex_search(search_start, line.cend(), match, marker_regex)) {
            int left = std::stoi(match[1]);
            int right = std::stoi(match[2]);
            multiplications += left * right;
            search_start = match.suffix().first;
        }
    }

    std::cout << "Total multiplications: " << multiplications << std::endl;
}

void day03part02() {
    std::cout << "\nDay 3 Part 2:\n";
    std::cout << "Including enabled/disabled instructions, how many multiplications are performed?\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day03.txt");

    int multiplications = 0;
    bool enabled = true;
    std::regex marker_regex(R"((do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)))");
    std::smatch match;

    for (const std::string& line : input) {
        std::string::const_iterator search_start(line.cbegin());
        while (std::regex_search(search_start, line.cend(), match, marker_regex)) {
            if (match[0] == "do()") {
                enabled = true;
            } else if (match[0] == "don't()") {
                enabled = false;
            } else if (enabled && match[1].matched && match[2].matched) {
                int left = std::stoi(match[2]);
                int right = std::stoi(match[3]);
                multiplications += left * right;
            }
            search_start = match.suffix().first;
        }
    }

    std::cout << "Total multiplications: " << multiplications << std::endl;
}

