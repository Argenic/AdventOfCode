#include <iostream>
#include "day15.hpp"
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

std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> processInput(const std::string& filePath) {
    auto input = utils::readLines(filePath);
    
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }

    std::vector<std::vector<char>> map;
    std::string instructions;
    bool map_toggle = true;
    std::pair<int, int> bot_location;

    for (int i = 0; i < input.size(); i++) {
        if(input[i].empty()) {
            map_toggle = false;
            continue;
        }
        if(map_toggle) {
            std::vector<char> row;
            for (int j = 0; j < input[i].size(); j++) {
                if(input[i][j] == '@') {
                    bot_location = std::make_pair(i, j);
                } 
                row.push_back(input[i][j]);
            }
            map.push_back(row);
        } else {
            instructions += input[i];
        }
    }

    return {map, instructions, bot_location};
}

std::pair<int, int> getVelocity(char instruction) {
    std::pair<int, int> velocity;
    if(instruction == '>') {
        velocity = {0, 1};
    } else if(instruction == '<') {
        velocity = {0, -1};
    } else if(instruction == '^') {
        velocity = {-1, 0};
    } else if(instruction == 'v') {
        velocity = {1, 0};
    }
    return velocity;
}

bool checkOptions(std::vector<std::vector<char>>& map, std::pair<int, int> location, std::pair<int, int>& velocity) {
    bool moving = true;
    bool holding = false;
    bool vertical = velocity.first != 0;

    while(true) {
        char next_char = map[location.first + velocity.first][location.second + velocity.second];
        if(next_char == '#') {
            return false;
        } else if(next_char == '.') {
            return true;
        } else if(next_char == '[' && vertical) {
            if(
                checkOptions(map, std::make_pair(location.first + velocity.first, location.second + velocity.second), velocity) &&
                checkOptions(map, std::make_pair(location.first + velocity.first, location.second + velocity.second + 1), velocity)
            ) {
                return true;
            } else {
                return false;
            }
        } else if(next_char == ']' && vertical) {
            if(
                checkOptions(map, std::make_pair(location.first + velocity.first, location.second + velocity.second), velocity) &&
                checkOptions(map, std::make_pair(location.first + velocity.first, location.second + velocity.second - 1), velocity)
            ) {
                return true;
            } else {
                return false;
            }
        }
        location.first += velocity.first;
        location.second += velocity.second;
    }
}

void moveBot(std::vector<std::vector<char>>& map, std::pair<int, int>& velocity, std::pair<int, int> location, char replacement) {
    char current_char = map[location.first][location.second];
    map[location.first][location.second] = replacement;
    bool vertical = velocity.first != 0;
    
    while(true) {
        char next_char = map[location.first + velocity.first][location.second + velocity.second];
        
        if(next_char == '[' && vertical) {
            moveBot(map, velocity, std::make_pair(location.first + velocity.first, location.second + velocity.second + 1), '.');
            //moveBot(map, velocity, std::make_pair(location.first, location.second - 1), '.');
        } else if(next_char == ']' && vertical) {
            moveBot(map, velocity, std::make_pair(location.first + velocity.first, location.second + velocity.second - 1), '.');
        }
        map[location.first + velocity.first][location.second + velocity.second] = current_char;
        
        current_char = next_char;
        location.first += velocity.first;
        location.second += velocity.second;
        
        if(current_char == '.') {
            return;
        }
    }

}

// Part 1 of Day 15
void day15part01() {
    std::cout << "\nDay 15 Part 1:" << std::endl;
    std::cout << "Find the coordinates score for all the bots?\n";

    auto [map, instructions, bot_location] = processInput("../2024/data/day15.txt");
    int score = 0;
    
    for (int i = 0; i < instructions.size(); i++) {
        std::pair<int, int> checker = bot_location;
        
        std::pair<int, int> velocity = getVelocity(instructions[i]);

        bool moving = true;
        bool holding = false;
        while(moving) {
            if(map[checker.first + velocity.first][checker.second + velocity.second] == '#') {
                moving = false;
            } else if(map[checker.first + velocity.first][checker.second + velocity.second] == 'O') {
                holding = true;
                checker.first += velocity.first;
                checker.second += velocity.second;
            } else if(map[checker.first + velocity.first][checker.second + velocity.second] == '.') {
                map[bot_location.first][bot_location.second] = '.';
                bot_location.first += velocity.first;
                bot_location.second += velocity.second;
                map[bot_location.first][bot_location.second] = '@';
                if(holding) {
                    map[checker.first + velocity.first][checker.second + velocity.second] = 'O';
                } 

                moving = false;
            } else {
                std::cout << "Error: " << map[checker.first + velocity.first][checker.second + velocity.second] << std::endl;
            }
        }
        
    }
    
    //std::cout << std::endl;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            //std::cout << map[i][j];
            if(map[i][j] == 'O') {
                score += i * 100 + j;
            }
        }
        //std::cout << std::endl;
    }


    std::cout << "Bot score: " << score << std::endl;
}

// Part 2 of Day 15
void day15part02() {
    std::cout << "\nDay 15 Part 2:" << std::endl;
    std::cout << "Dont multiply it by the count of fields, but by the count of edges\n";
    
    auto [map, instructions, bot_location] = processInput("../2024/data/day15.txt");
    std::vector<std::vector<char>> upgraded_map;
    for (int i = 0; i < map.size(); i++) {
        std::vector<char> row;
        for (int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == 'O') {
                row.push_back('[');
                row.push_back(']');
            } else if(map[i][j] == '@') {
                bot_location.second = j * 2;
                row.push_back('@');
                row.push_back('.');
            } else if(map[i][j] == '.') {
                row.push_back('.');
                row.push_back('.');
            } else if(map[i][j] == '#') {
                row.push_back('#');
                row.push_back('#');
            } else {
                std::cout << "Error: " << map[i][j] << std::endl;
            }
        }
        upgraded_map.push_back(row);
    }
    int score = 0;
    
    for (int i = 0; i < instructions.size(); i++) {
        std::pair<int, int> velocity = getVelocity(instructions[i]);
        bool result = checkOptions(upgraded_map, bot_location, velocity);
        if(result) {
            moveBot(upgraded_map, velocity, bot_location, '.');
            bot_location.first += velocity.first;
            bot_location.second += velocity.second;
        } 
    }
    
    for (int i = 0; i < upgraded_map.size(); i++) {
        for (int j = 0; j < upgraded_map[i].size(); j++) {
            std::cout << upgraded_map[i][j];
            if(upgraded_map[i][j] == '[') {
                score += i * 100 + j;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    

    std::cout << "Bot score: " << score << std::endl;
}