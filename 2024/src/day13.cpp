#include <iostream>
#include "day13.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
// Part 1 of Day 13
void day13part01() {
    std::cout << "\nDay 13 Part 1:" << std::endl;
    std::cout << "Fewest tokens required to win maximum prizes?\n";
    auto input = utils::readLines("../2024/data/day13.txt");
    int score = 0;

    // Clean input
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }
    
    // Split lines into groups
    std::vector<std::vector<std::string>> groups;
    std::vector<std::string> group;
    for (const auto& line : input) {
        if (line.empty()) {
            groups.push_back(group);
            group.clear();
        } else {
            group.push_back(line);
        }
    }
    groups.push_back(group);
    
    // Iterate over the groups
    for (const auto& group : groups) {
        // Split out the values we need
        std::regex regex("Button A: X\\+([0-9]+), Y\\+([0-9]+)");
        std::smatch match;
        std::regex_search(group[0], match, regex);
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        std::pair<int, int> buttonA(x, y);
        regex = "Button B: X\\+([0-9]+), Y\\+([0-9]+)";
        std::regex_search(group[1], match, regex);
        x = std::stoi(match[1].str());
        y = std::stoi(match[2].str());
        std::pair<int, int> buttonB(x, y);
        regex = "Prize: X\\=([0-9]+), Y\\=([0-9]+)";
        std::regex_search(group[2], match, regex);
        x = std::stoi(match[1].str());
        y = std::stoi(match[2].str());
        std::pair<int, int> prize(x, y);

        std::vector<std::pair<int, int>> validValues;
        for(int i = 100; i > 0; i--) {
            // Filter out values that are too high
            if(buttonA.first * i > prize.first || buttonA.second * i > prize.second) {
                continue;
            }


            for(int j = 1; j <= 100; j++) {
                // Get the current values
                std::pair<int, int> currentValue = std::make_pair(buttonA.first * i + buttonB.first * j, buttonA.second * i + buttonB.second * j);
                
                // Overshot the prize
                if(currentValue.first > prize.first || currentValue.second > prize.second) {
                    break;
                }

                // Check if we have a valid value
                if(currentValue.first == prize.first && currentValue.second == prize.second) {
                    validValues.push_back(std::make_pair(i, j));
                    break;
                }
            }
        }
        if(validValues.size() == 1) {
            score += validValues[0].first * 3 + validValues[0].second;
        }
    }
    
    std::cout << "Score: " << score << std::endl;
}

// Part 2 of Day 13
void day13part02() {
    std::cout << "\nDay 13 Part 2:" << std::endl;
    std::cout << "Dont multiply it by the count of fields, but by the count of edges\n";    
    

    std::cout << "" << std::endl;
}