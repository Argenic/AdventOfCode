#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include "day05.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <set>
#include <functional>

// Function to print the map
void printMap(const std::vector<std::vector<char>>& map) {
    for (const auto& row : map) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

// Initialize the map and starting location
void initializeMapAndLocation(const std::vector<std::string>& input, 
                              std::vector<std::vector<char>>& map, 
                              std::pair<int, int>& location) {
    for (int i = 0; i < input.size(); i++) {
        map.emplace_back(input[i].size(), 'x');
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '^') {
                location = {i, j};
                map[i][j] = 'X';
            } else {
                map[i][j] = input[i][j];
            }
        }
    }
}

// Get the next location based on the current direction
std::pair<int, int> getNextLocation(const std::pair<int, int>& location, int direction) {
    std::pair<int, int> nextLocation = location;
    switch (direction) {
        case 0: nextLocation.first--; break;  // North
        case 1: nextLocation.second++; break; // East
        case 2: nextLocation.first++; break;  // South
        case 3: nextLocation.second--; break; // West
    }
    return nextLocation;
}

// Common function to simulate the guard's path
std::vector<std::pair<int, int>> simulatePath(std::vector<std::vector<char>>& map, std::pair<int, int> location, 
                                              std::function<void(std::pair<int, int>&, int&, bool&)> onBlocked = nullptr) {
    std::vector<std::pair<int, int>> path;
    int direction = 0;
    bool patrolling = true;

    while (patrolling) {
        auto nextLocation = getNextLocation(location, direction);

        if (nextLocation.first < 0 || nextLocation.first >= map.size() || 
            nextLocation.second < 0 || nextLocation.second >= map[0].size()) {
            patrolling = false;
        } else if (map[nextLocation.first][nextLocation.second] == '#') {
            if (onBlocked) {
                onBlocked(location, direction, patrolling);
            } else {
                direction = (direction + 1) % 4;
            }
        } else {
            location = nextLocation;
            map[location.first][location.second] = 'X';
            path.push_back(location);
        }
    }
    return path;
}

// Part 1 of Day 6
void day06part01() {
    std::cout << "\nDay 6 Part 1:\nFollow the path of the guard\n";
    const auto input = utils::readLines("../2024/data/day06.txt");

    std::vector<std::vector<char>> map;
    std::pair<int, int> location;

    initializeMapAndLocation(input, map, location);
    auto path = simulatePath(map, location);

    std::set<std::pair<int, int>> uniquePath(path.begin(), path.end());
    std::cout << "Total: " << uniquePath.size() << std::endl;
}

// Part 2 of Day 6
void day06part02() {
    std::cout << "\nDay 6 Part 2:\nHow many loops can I force the guard to walk?\n";
    const auto input = utils::readLines("../2024/data/day06.txt");

    std::vector<std::vector<char>> map;
    std::pair<int, int> location;

    initializeMapAndLocation(input, map, location);
    auto startLocation = location;
    auto originalMap = map;
    auto path = simulatePath(map, location);

    std::set<std::pair<int, int>> uniquePath(path.begin(), path.end());
    int loops = 0;

    for (const auto& pos : uniquePath) {
        if (pos == startLocation) continue;

        auto copyMap = originalMap;
        copyMap[pos.first][pos.second] = '#';
        auto copyLocation = startLocation;
        std::unordered_map<std::string, std::vector<int>> blockers;

        auto onBlocked = [&](std::pair<int, int>& loc, int& dir, bool& patrol) {
            dir = (dir + 1) % 4;
            std::string coordinates = std::to_string(loc.first) + "," + std::to_string(loc.second);
            if (blockers[coordinates].end() != std::find(blockers[coordinates].begin(), blockers[coordinates].end(), dir)) {
                loops++;
                patrol = false;
            }
            blockers[coordinates].push_back(dir);
        };

        simulatePath(copyMap, copyLocation, onBlocked);
    }

    std::cout << "Possible loops: " << loops << std::endl;
}