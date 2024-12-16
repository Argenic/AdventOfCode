#include <iostream>
#include "day16.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <regex>
#include <vector>
#include <thread>
#include <chrono>

std::string createKey(int i, int j) {
    std::stringstream ss;
    ss << i << "," << j;
    return ss.str();
}

void printInput(const std::vector<std::string>& input) {
    for (const auto& line : input) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
}

void printLocations(const std::unordered_map<std::string, int>& locations) {
    for (const auto& location : locations) {
        std::cout << location.first << ": " << location.second << std::endl;
    }
}

std::pair<int, int> get_velocity(int direction) {
    // Up
    if (direction == 0) {
        return std::make_pair(-1, 0);
    }

    // Right
    if (direction == 1) {
        return std::make_pair(0, 1);
    }

    // Down
    if (direction == 2) {
        return std::make_pair(1, 0);
    }

    // Left
    if (direction == 3) {
        return std::make_pair(0, -1);
    }

    std::cout << "Invalid direction: " << direction << std::endl;
    return std::make_pair(0, 0);
}

int get_reversed_direction(std::pair<int, int> velocity) {
    if (velocity.first == -1 && velocity.second == 0) {
        return 0;
    }
    if (velocity.first == 0 && velocity.second == 1) {
        return 1;
    }
    if (velocity.first == 1 && velocity.second == 0) {
        return 2;
    }
    return 3;
}

std::vector<std::pair<std::pair<int, int>, std::string>> check_open_locations(std::unordered_map<std::string, int>& locations, std::pair<int, int> coordinate, int direction) {
    // Forward, left, right
    std::vector<std::pair<int, int>> velocities = {get_velocity(direction), get_velocity((direction + 3) % 4), get_velocity((direction + 1) % 4)};
    std::vector<std::pair<std::pair<int, int>, std::string>> open_locations;

    for (std::pair<int, int> velocity : velocities) {
        std::pair<int, int> new_coordinate = std::make_pair(coordinate.first + velocity.first, coordinate.second + velocity.second);
        std::string new_key = createKey(new_coordinate.first, new_coordinate.second);
        if (locations.find(new_key) != locations.end()) {
            open_locations.push_back(std::make_pair(velocity, new_key));
        }
    }
    
    return open_locations;
}

void traverse_map(std::vector<std::string>& input, std::unordered_map<std::string, int>& locations, std::pair<int, int> coordinate, std::pair<int, int>& end, int cost, int direction) {
    locations[createKey(coordinate.first, coordinate.second)] = cost;
    
    std::vector<std::pair<std::pair<int, int>, std::string>> open_locations = check_open_locations(locations, coordinate, direction);

    if (open_locations.size() == 1) {
        if(direction == 0) {
            input[coordinate.first][coordinate.second] = '^';
        } else if (direction == 1) {
            input[coordinate.first][coordinate.second] = '>';
        } else if (direction == 2) {
            input[coordinate.first][coordinate.second] = 'v';
        } else if (direction == 3) {
            input[coordinate.first][coordinate.second] = '<';
        }
    } else if (open_locations.size() == 2) {
        input[coordinate.first][coordinate.second] = '+';
    } else if (open_locations.size() == 3) {
        input[coordinate.first][coordinate.second] = 'x';
    }

    for (std::pair<std::pair<int, int>, std::string> location : open_locations) {
        int new_direction = get_reversed_direction(location.first);
        int new_cost = 1 + cost;
        if (new_direction != direction) {
            new_cost += 1000;
        }
        if(locations[location.second] == -1 || cost - 999 < locations[location.second]) {
            traverse_map(input, locations, std::make_pair(coordinate.first + location.first.first, coordinate.second + location.first.second), end, new_cost, new_direction);
        }
    }

}


// Part 1 of Day 16
void day16part01() {
    std::cout << "\nDay 16 Part 1:" << std::endl;
    std::cout << "Cheapest route from S to E:\n";
    
    int cost = 0;

    auto input = utils::readLines("../2024/data/day16.txt");
    
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }
    
    std::unordered_map<std::string, int> locations;
    std::pair<int, int> start;
    std::pair<int, int> end;

    //printInput(input);
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            // Find start
            if (input[i][j] == 'S') {
                start = std::make_pair(i, j);
                locations[createKey(i, j)] = -1;
                input[i][j] = '.';
            }
            // Find end
            if (input[i][j] == 'E') {
                end = std::make_pair(i, j);
                locations[createKey(i, j)] = -1;
                input[i][j] = '.';
            }
            // Find open locations
            if (input[i][j] == '.') {
                locations[createKey(i, j)] = -1;
            }
        }
    }

    int starting_cost = 0;
    int starting_direction = 1; // 0 is up, 1 is right, 2 is down, 3 is left

    traverse_map(input, locations, start, end, starting_cost, starting_direction);

    //printLocations(locations);

    std::string end_key = createKey(end.first, end.second);
    std::cout << "The shortest route costs us : " << locations[end_key] << std::endl;
}

// Part 2 of Day 16
void day16part02() {
    std::cout << "\nDay 16 Part 2:" << std::endl;
    std::cout << "\n";
    
    auto input = utils::readLines("../2024/data/day16.txt");
    
    std::cout << "" << std::endl;
}