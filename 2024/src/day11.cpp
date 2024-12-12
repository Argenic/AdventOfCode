#include <iostream>
#include "day09.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Part 1 of Day 11
void day11part01() {
    std::cout << "\nDay 11 Part 1:" << std::endl;
    int max_level = 40;
    std::cout << "How many moving stones do we end up with after " << max_level << " moves?\n";
    const auto input = utils::readLines("../2024/data/day11.txt");
    // Split input by spaces
    std::vector<std::string> input_split = splitString(input[0], ' ');
    
    for (int i = 0; i < max_level; i++) {
        std::vector<std::string> new_split;
        for(int j = 0; j < input_split.size(); j++) {
            if(input_split[j] == "0") {
                new_split.push_back("1");
            } else if(input_split[j].size()  % 2 == 0) {
                std::string first_half = input_split[j].substr(0, input_split[j].size() / 2);
                std::string second_half = input_split[j].substr(input_split[j].size() / 2);
                first_half = std::to_string(std::stol(first_half));
                second_half = std::to_string(std::stol(second_half));
                new_split.push_back(first_half);
                new_split.push_back(second_half);
            } else {
                new_split.push_back(std::to_string(std::stol(input_split[j]) * 2024));
            }
        }
        input_split = new_split;
    }
    
    std::cout << "Stones: " << input_split.size() << std::endl;
}

// Part 2 of Day 10
void day11part02() {
    int max_level = 40;
    std::cout << "\nDay 11 Part 2:" << std::endl;
    std::cout << "How many moving stones do we end up with after " << max_level << " moves?\n";    
    const auto input = utils::readLines("../2024/data/day11.txt");
    

    // Split input by spaces
    std::vector<std::string> input_split = splitString(input[0], ' ');
    std::vector<int> size_per_level;
    std::vector<int> zero_count_per_level;
    for (int i = 0; i < max_level; i++) {
        std::vector<std::string> new_split;
        int zero_count = 0;
        for(int j = 0; j < input_split.size(); j++) {
            if(input_split[j] == "0" && i == 0) {
                zero_count++;
                new_split.push_back("1");
            } else if(input_split[j] == "0") {
                zero_count++;
            } else if(input_split[j].size()  % 2 == 0) {
                std::string first_half = input_split[j].substr(0, input_split[j].size() / 2);
                std::string second_half = input_split[j].substr(input_split[j].size() / 2);
                first_half = std::to_string(std::stol(first_half));
                second_half = std::to_string(std::stol(second_half));
                new_split.push_back(first_half);
                new_split.push_back(second_half);
            } else {
                new_split.push_back(std::to_string(std::stol(input_split[j]) * 2024));
            }
        }
        int current_size = new_split.size();
        
        input_split = new_split;
        zero_count_per_level.push_back(zero_count);
        
        for(int j = 1; j < zero_count_per_level.size(); j++) {
            if(zero_count_per_level[j] > 0) {
                current_size += size_per_level[i-j] * zero_count_per_level[j];
            }
        }
        //std::cout << "Level " << i << " Stones: " << current_size << " Zeroes: " << zero_count << std::endl;
                
        size_per_level.push_back(current_size);
        //std::cout << "Iteration " << i << " Stones: " << input_split.size() << " Zeroes: " << zero_count << std::endl;
    }
    
    std::cout << "Stones: " << size_per_level[max_level-1] << std::endl;

}