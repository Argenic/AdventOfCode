#include <iostream>
#include "day14.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <regex>
#include <thread>
#include <chrono>

std::pair<int, int> calculateNewPosition(const std::string& line, int width, int height, int iterations) {
    std::pair<int, int> position;
    std::pair<int, int> velocity;
    std::regex regex("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
    std::smatch matches;
    if (std::regex_search(line, matches, regex)) {
        position.first = std::stoi(matches[1].str());
        position.second = std::stoi(matches[2].str());
        velocity.first = std::stoi(matches[3].str());
        velocity.second = std::stoi(matches[4].str());
    }
    int newX = (velocity.first * iterations + position.first) % width;
    int newY = (velocity.second * iterations + position.second) % height;
    if (newX < 0) {
        newX = width - abs(newX);
    }
    if (newY < 0) {
        newY = height - abs(newY);
    }
    return std::make_pair(newX, newY);
}

// Part 1 of Day 14
void day14part01() {
    std::cout << "\nDay 14 Part 1:" << std::endl;
    std::cout << "Figure out where the bots are after 100 rounds?\n";
    auto input = utils::readLines("../2024/data/day14.txt");
    int score = 0;

    // Clean input
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }

    int width = 101;
    int height = 103;
    std::vector<std::pair<int, int>> positions;
    int iterations = 100;
    for (const auto& line : input) {
        positions.push_back(calculateNewPosition(line, width, height, iterations));
    }

    int northEastCount = 0;
    int southEastCount = 0;
    int southWestCount = 0;
    int northWestCount = 0;

    for (const auto& position : positions) {
        if (position.first > width / 2 && position.second > height / 2) {
            northEastCount++;
        }
        if (position.first > width / 2 && position.second < height / 2) {
            southEastCount++;
        }
        if (position.first < width / 2 && position.second < height / 2) {
            southWestCount++;
        }
        if (position.first < width / 2 && position.second > height / 2) {
            northWestCount++;
        }
    }
    int count = northEastCount * southEastCount * southWestCount * northWestCount;

    std::cout << "Bot score: " << count << std::endl;
}

// Part 2 of Day 14
void day14part02() {
    std::cout << "\nDay 14 Part 2:" << std::endl;
    std::cout << "Dont multiply it by the count of fields, but by the count of edges\n";    
    const auto input = utils::readLines("../2024/data/day14.txt");
    int width = 101;
    int height = 103;

    int iterations = 65;    
    while(true) {
        // Ask for input of iterations  
        iterations += 103;
        std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));
        for (const auto& line : input) {
            std::pair<int, int> newPosition = calculateNewPosition(line, width, height, iterations);
            grid[newPosition.second][newPosition.first] = '#';
        }

        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[i].size(); j++) {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "Current Iteration: " << iterations << std::endl;
        // wait 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //wait on enter
        //std::cout << "Press Enter to continue...";
        //std::cin.ignore();
    }   


    std::cout << "" << std::endl;
}