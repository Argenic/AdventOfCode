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

// Function to parse a line and update the map
void parseLineAndUpdateMap(const std::string& line, std::unordered_map<long, std::vector<int>>& map) {
    std::regex regex("(\\d+): (\\d+(?: \\d+)*)");
    std::smatch matches;
    if (std::regex_search(line, matches, regex)) {
        long key = std::stol(matches[1]);
        std::vector<int> values;
        std::stringstream ss(matches[2]);
        std::string value;
        while (std::getline(ss, value, ' ')) {
            values.push_back(std::stoi(value));
        }
        if(map.find(key) != map.end()) {
            std::cout << "WE GOT AN ISSUE WITH KEY: " << key << std::endl;
        }
        map[key] = values;
    }
}

// Recursive function to generate all possible results
void generateResults(const std::vector<int>& values, int index, long currentResult, std::vector<long>& results, std::function<long(long, int)> operation) {
    if (index == values.size()) {
        results.push_back(currentResult);
        return;
    }

    // Try adding the current value
    generateResults(values, index + 1, operation(currentResult, values[index]), results, std::plus<long>());

    // Try multiplying the current value
    generateResults(values, index + 1, operation(currentResult, values[index]), results, std::multiplies<long>());
}


// Wrapper function to initiate the recursive process
std::vector<long> generateAllResults(const std::vector<int>& values) {
    std::vector<long> results;
    if (!values.empty()) {
        generateResults(values, 1, static_cast<long>(values[0]), results, std::plus<long>());
        generateResults(values, 1, static_cast<long>(values[0]), results, std::multiplies<long>());
    }
    return results;
}
// Recursive function to generate all possible results
void generateResultsAdvanced(const std::vector<int>& values, int index, long currentResult, std::vector<long>& results, std::function<long(long, int)> operation) {
    if (index == values.size()) {
        results.push_back(currentResult);
        return;
    }

    // Try adding the current value
    generateResultsAdvanced(values, index + 1, operation(currentResult, values[index]), results, std::plus<long>());

    // Try multiplying the current value
    generateResultsAdvanced(values, index + 1, operation(currentResult, values[index]), results, std::multiplies<long>());

    // Try concatenating the current value with the next value
    if (index < values.size()) {
        std::string concat = std::to_string(currentResult) + std::to_string(values[index]);
        long concatenatedValue = std::stol(concat);
        generateResultsAdvanced(values, index + 1, concatenatedValue, results, std::plus<long>());
        generateResultsAdvanced(values, index + 1, concatenatedValue, results, std::multiplies<long>());
    }
}


// Wrapper function to initiate the recursive process
std::vector<long> generateAllResultsAdvanced(const std::vector<int>& values) {
    std::vector<long> results;
    if (!values.empty()) {
        generateResultsAdvanced(values, 1, static_cast<long>(values[0]), results, std::plus<long>());
        generateResultsAdvanced(values, 1, static_cast<long>(values[0]), results, std::multiplies<long>());
        // Can you add in a concatinate of both values?
        std::string concat = std::to_string(values[0]) + std::to_string(values[1]);
        generateResultsAdvanced(values, 2, std::stol(concat), results, std::plus<long>());
        generateResultsAdvanced(values, 2, std::stol(concat), results, std::multiplies<long>());
    }
    return results;
}


// Part 1 of Day 7
void day07part01() {
    std::cout << "\nDay 7 Part 1:" << std::endl;
    std::cout << "Find the sum of all numbers that can be generated from the input\n";
    const auto input = utils::readLines("../2024/data/day07.txt");
    std::unordered_map<long, std::vector<int>> map;

    long count = 0;
    for (const auto& line : input) {
        parseLineAndUpdateMap(line, map);
    }

    for (const auto& [key, value] : map) {
        std::vector<long> results = generateAllResults(value);

        for (long result : results) {
            if(result == key) {
                count += key;
                break;
            }
        }

    }

    std::cout << "Total: " << count << std::endl;
}

// Part 2 of Day 7
void day07part02() {
    std::cout << "\nDay 7 Part 2:"<< std::endl;
    std::cout << "Also concatinate the numbers and give the sum of all numbers that can be generated from the input\n";
    const auto input = utils::readLines("../2024/data/day07.txt");
    std::unordered_map<long, std::vector<int>> map;

    long count = 0;
    for (const auto& line : input) {
        parseLineAndUpdateMap(line, map);
    }

    for (const auto& [key, value] : map) {
        std::vector<long> results = generateAllResultsAdvanced(value);

        for (long result : results) {
            if(result == key) {
                count += key;
                break;
            }
        }
    }

    std::cout << "Total: " << count << std::endl;
}