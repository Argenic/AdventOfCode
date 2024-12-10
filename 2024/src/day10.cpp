#include <iostream>
#include "day09.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>

// Function to create the mountain from input
std::vector<std::vector<int>> createMountain(const std::vector<std::string>& input) {
    std::vector<std::vector<int>> mountain;
    for (std::string line : input) {
        line.erase(line.find_last_not_of("\n\r") + 1);
        std::vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        mountain.push_back(row);
    }
    return mountain;
}

// Function to print the mountain
void printMountain(const std::vector<std::vector<int>>& mountain) {
    for (int i = 0; i < mountain.size(); i++) {
        for (int j = 0; j < mountain[i].size(); j++) {
            std::cout << mountain[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Recursive function to find amount of trails
void findTrails(std::vector<std::vector<int>> mountain, int x, int y, int valid_trails, std::vector<std::pair<int, int>>& visited) {
    int value = mountain[x][y];
   
    if (value == 9) {
        valid_trails++;
        visited.push_back({x, y}); // Mark this position as visited
        return;
    }
    
    // Look up, if +1 is smaller than current, continue
    if (x > 0 && mountain[x-1][y] == value + 1) {
        findTrails(mountain, x-1, y, valid_trails, visited);
    }
    
    // Look down, if +1 is smaller than current, continue
    if (x < mountain.size() - 1 && mountain[x+1][y] == value + 1) {
        findTrails(mountain, x+1, y, valid_trails, visited);
    }

    // Look left, if +1 is smaller than current, continue
    if (y > 0 && mountain[x][y-1] == value + 1) {
        findTrails(mountain, x, y-1, valid_trails, visited);
    }

    // Look right, if +1 is smaller than current, continue
    if (y < mountain[x].size() - 1 && mountain[x][y+1] == value + 1) {
        findTrails(mountain, x, y+1, valid_trails, visited);
    }

    return;
}

// Part 1 of Day 10
void day10part01() {
    std::cout << "\nDay 10 Part 1:" << std::endl;
    std::cout << "Find the count of all possible trails up the mountain\n";
    const auto input = utils::readLines("../2024/data/day10.txt");
    std::vector<std::vector<int>> mountain = createMountain(input);
    int trail_heads = 0;


    // Start of a recursive function for every 0,
    for (int i = 0; i < mountain.size(); i++) {
        for (int j = 0; j < mountain[i].size(); j++) {
            if (mountain[i][j] == 0) {
                std::vector<std::pair<int, int>> visited;
                findTrails(mountain, i, j, 0, visited);
                // get unique values from visited
                std::set<std::pair<int, int>> unique_visited(visited.begin(), visited.end());
                trail_heads += unique_visited.size();
            }
        }
    }

    std::cout << "Amount of valid paths: " << trail_heads << std::endl;
}

// Part 2 of Day 10
void day10part02() {
    std::cout << "\nDay 10 Part 2:" << std::endl;
    std::cout << "Find all possible paths to the outcome\n";    
    const auto input = utils::readLines("../2024/data/day10.txt");
    std::vector<std::vector<int>> mountain = createMountain(input);
    int trail_heads = 0;


    // Start of a recursive function for every 0,
    for (int i = 0; i < mountain.size(); i++) {
        for (int j = 0; j < mountain[i].size(); j++) {
            if (mountain[i][j] == 0) {
                std::vector<std::pair<int, int>> visited;
                findTrails(mountain, i, j, 0, visited);
                // get unique values from visited
                trail_heads += visited.size();
            }
        }
    }

    std::cout << "Amount of valid paths: " << trail_heads << std::endl;
}