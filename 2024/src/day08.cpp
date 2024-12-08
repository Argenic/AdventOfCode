#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include "day05.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <set>
#include <functional>
#include <climits>

// Part 1 of Day 8
void day08part01() {
    std::cout << "\nDay 8 Part 1:" << std::endl;
    std::cout << "Find the amount of visible anti nodes\n";
    const auto input = utils::readLines("../2024/data/day08.txt");
    std::unordered_map<char, std::vector<std::pair<int, int>>> map;

    for (int i = 0 ; i < input.size() ; ++i) {
        std::string line = input[i];
        line.erase(line.find_last_not_of("\n\r") + 1);

        // remove whitespace
        for (int j = 0 ; j < line.size() ; ++j) {
            if (line[j] != '.' && line[j] != '\n') {
                map[input[i][j]].push_back({i, j});
            }
        }
    }

    int width = input[0].size() - 1;
    int height = input.size();

    int count = 0;
    std::vector<std::pair<int, int>> nodes;

    for (const auto& [key, value] : map) {
        for (int i = 0 ; i < value.size() - 1 ; ++i) {
            std::pair<int, int> first = value[i];
            for (int j = i+1 ; j < value.size() ; ++j) {
                std::pair<int, int> second = value[j];
                int vertical = abs(first.first - second.first);
                int horizontal = abs(first.second - second.second);

                std::pair<int, int> node1 = {0, 0};
                std::pair<int, int> node2 = {0, 0};
                
                if(first.first < second.first) {
                    node1.first = first.first - vertical;
                    node2.first = second.first + vertical;
                } else {
                    node1.first = first.first + vertical;
                    node2.first = second.first - vertical;
                }

                if(first.second < second.second) {
                    node1.second = first.second - horizontal;
                    node2.second = second.second + horizontal;
                } else {
                    node1.second = first.second + horizontal;
                    node2.second = second.second - horizontal;
                }

                nodes.push_back(node1);
                nodes.push_back(node2);
            }
        }
    }

    // Filter out unique nodes
    std::set<std::pair<int, int>> uniqueNodes(nodes.begin(), nodes.end());

    for (const auto& node : uniqueNodes) {
        if (node.first >= 0 && node.first < height && node.second >= 0 && node.second < width) {
            ++count;
        }
    }

    std::cout << "Total: " << count << std::endl;
}

// Part 2 of Day 8
void day08part02() {
    std::cout << "\nDay 8 Part 2:"<< std::endl;
    std::cout << "Now consider the velocity of the nodes\n";
    const auto input = utils::readLines("../2024/data/day08.txt");
    std::unordered_map<char, std::vector<std::pair<int, int>>> map;
    std::vector<std::pair<int, int>> filteredNodes;

    for (int i = 0 ; i < input.size() ; ++i) {
        std::string line = input[i];
        line.erase(line.find_last_not_of("\n\r") + 1);

        // remove whitespace
        for (int j = 0 ; j < line.size() ; ++j) {
            if (line[j] != '.' && line[j] != '\n') {
                map[input[i][j]].push_back({i, j});
                filteredNodes.push_back({i, j});
            }
        }
    }

    int width = input[0].size() - 1;
    int height = input.size();

    int count = 0;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> nodes;

    for (const auto& [key, value] : map) {
        for (int i = 0 ; i < value.size() - 1 ; ++i) {
            std::pair<int, int> first = value[i];
            for (int j = i+1 ; j < value.size() ; ++j) {
                std::pair<int, int> second = value[j];
                int vertical = abs(first.first - second.first);
                int horizontal = abs(first.second - second.second);

                std::pair<int, int> node1 = {0, 0};
                std::pair<int, int> velocity1 = {0, 0};
                std::pair<int, int> node2 = {0, 0};
                std::pair<int, int> velocity2 = {0, 0};
                
                if(first.first < second.first) {
                    node1.first = first.first - vertical;
                    node2.first = second.first + vertical;
                    velocity1.first = -vertical;
                    velocity2.first = vertical;
                } else {
                    node1.first = first.first + vertical;
                    node2.first = second.first - vertical;
                    velocity1.first = vertical;
                    velocity2.first = -vertical;
                }

                if(first.second < second.second) {
                    node1.second = first.second - horizontal;
                    node2.second = second.second + horizontal;
                    velocity1.second = -horizontal;
                    velocity2.second = horizontal;
                } else {
                    node1.second = first.second + horizontal;
                    node2.second = second.second - horizontal;
                    velocity1.second = horizontal;
                    velocity2.second = -horizontal;
                }

                nodes.push_back({node1, velocity1});
                nodes.push_back({node2, velocity2});
            }
        }
    }

    // Filter out unique nodes
    for (std::pair<std::pair<int, int>, std::pair<int, int>> node : nodes) {
        while (node.first.first >= 0 && node.first.first < height && node.first.second >= 0 && node.first.second < width) { 
            filteredNodes.push_back(node.first);

            node.first.first += node.second.first;
            node.first.second += node.second.second;
        }
    }

    
    // Filter out unique nodes
    std::set<std::pair<int, int>> uniqueNodes(filteredNodes.begin(), filteredNodes.end());

    for (const auto& node : uniqueNodes) {
        if (node.first >= 0 && node.first < height && node.second >= 0 && node.second < width) {
            ++count;
        }
    }

    std::cout << "Total: " << count << std::endl;
}