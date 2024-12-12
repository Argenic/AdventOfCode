#include <iostream>
#include "day12.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

// Helper function to perform flood fill and mark groups
void floodFill(const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, 
               int i, int j, char target, std::vector<std::pair<int, int>>& group) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || 
        visited[i][j] || grid[i][j] != target) {
        return;
    }
    
    visited[i][j] = true;
    group.push_back({i, j});
    
    // Check all 4 adjacent cells
    floodFill(grid, visited, i+1, j, target, group); // down
    floodFill(grid, visited, i-1, j, target, group); // up
    floodFill(grid, visited, i, j+1, target, group); // right
    floodFill(grid, visited, i, j-1, target, group); // left
}

// Initialize the grid and get the unique letters
std::pair<std::vector<std::vector<char>>, std::vector<char>> initializeGrid(const std::string& filename) {
    auto input = utils::readLines(filename);
    // Trim spaces from each line
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }

    std::vector<char> unique_letters;
    std::vector<std::vector<char>> grid;
    for(int i = 0; i < input.size(); i++) {
        std::vector<char> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(input[i][j]);
            if(std::find(unique_letters.begin(), unique_letters.end(), input[i][j]) == unique_letters.end()) {
                unique_letters.push_back(input[i][j]);
            }
        }
        grid.push_back(row);
    }
    
    return {grid, unique_letters};
}

std::vector<std::vector<std::pair<int, int>>> findGroups(const std::vector<std::vector<char>>& grid) {
    std::vector<std::vector<std::pair<int, int>>> groups;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    // Find all groups
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if (!visited[i][j]) {
                std::vector<std::pair<int, int>> currentGroup;
                floodFill(grid, visited, i, j, grid[i][j], currentGroup);
                if (!currentGroup.empty()) {
                    groups.push_back(currentGroup);
                }
            }
        }
    }
    
    return groups;
}

// Part 1 of Day 12
void day12part01() {
    std::cout << "\nDay 12 Part 1:" << std::endl;
    std::cout << "Figure out the amount of fences needed to box all groups\n";
    
    auto [grid, unique_letters] = initializeGrid("../2024/data/day12.txt");
    auto groups = findGroups(grid);

    int total_fences = 0;

    for (int groupIdx = 0; groupIdx < groups.size(); groupIdx++) {
        int fences = 0;
        for (const auto& coord : groups[groupIdx]) {
            char current_char = grid[coord.first][coord.second];
            // Check all 4 adjacent cells
            if(coord.first - 1 < 0) {
                fences++;
            } else if(grid[coord.first - 1][coord.second] != current_char) {
                fences++;
            } // up
            if(coord.first + 1 >= grid.size()) {
                fences++;
            } else if(grid[coord.first + 1][coord.second] != current_char) {
                fences++;
            } // down
            if(coord.second - 1 < 0) {
                fences++;
            } else if(grid[coord.first][coord.second - 1] != current_char) {
                fences++;
            } // left
            if(coord.second + 1 >= grid[coord.first].size()) {
                fences++;
            } else if(grid[coord.first][coord.second + 1] != current_char) {
                fences++;
            } // right
        }
        total_fences += fences * groups[groupIdx].size();
    }

    std::cout << "Total fences: " << total_fences << std::endl;
}

// Part 2 of Day 12
void day12part02() {
    std::cout << "\nDay 12 Part 2:" << std::endl;
    std::cout << "Dont multiply it by the count of fields, but by the count of edges\n";    
    
    auto [grid, unique_letters] = initializeGrid("../2024/data/day12.txt");
    auto groups = findGroups(grid);

    int total_edges = 0;

    for(int i = 0; i < groups.size(); i++) {
        // Do stuff here...
    }

    std::cout << "Total edges: " << total_edges << std::endl;
}