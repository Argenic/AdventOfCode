#include <iostream>
#include "day01.hpp"
#include "utils.hpp"
#include <sstream>
#include <algorithm>
#include <unordered_map>

/**
 * @brief Parse the input file and return 2 vectors of integers.
 * @param filePath The path to the input file.
 * @return A pair of vectors of integers.
 */
std::pair<std::vector<int>, std::vector<int>> parseInputFile(const std::string& filePath) {
    // Read the input file into a vector of strings
    const std::vector<std::string> input = utils::readLines(filePath);
    
    // Initialize the output lists
    std::vector<int> left;
    std::vector<int> right;
    left.reserve(input.size());
    right.reserve(input.size());

    // Iterate over each line in the input file
    for (const auto& line : input) {
        // Split the line into tokens
        std::istringstream iss(line);
        int token;
        std::vector<int> values;

        // Split out values from spaces
        while (iss >> token) {
            values.push_back(token);
        }

        // Add the values to the output lists
        if (values.size() >= 2) {
            left.push_back(values[0]);
            right.push_back(values[1]);
        }
    }

    // Return the output lists
    return {left, right};
}

/**
 * @brief Find the difference in 2 lists by sorting them Ascending.
 */
void day01part01() {
    // Output the header
    std::cout << "\nDay 1 Part 1:\n";
    std::cout << "Find the difference in 2 lists by sorting them Ascending.\n";

    // Parse the input file
    const auto [left, right] = parseInputFile("../2024/data/day01.txt");

    // Initialize the total difference
    int total_diff = 0;

    // Sort the lists
    std::vector<int> sorted_left = left;
    std::vector<int> sorted_right = right;
    std::sort(sorted_left.begin(), sorted_left.end());
    std::sort(sorted_right.begin(), sorted_right.end());

    // Calculate the total difference
    for (size_t i = 0; i < sorted_left.size(); ++i) {
        total_diff += std::abs(sorted_left[i] - sorted_right[i]);
    }

    // Output the total difference
    std::cout << "Total difference: " << total_diff << std::endl;
}

/**
 * @brief Find the similarity between 2 lists.
 */
void day01part02() {
    // Output the header
    std::cout << "\nDay 1 Part 2:\n";
    std::cout << "Find the similarity between 2 lists.\n";

    // Parse the input file
    const auto [left, right] = parseInputFile("../2024/data/day01.txt");

    // Initialize the total similarity
    int total_similarity = 0;

    // Count the occurrences of each value in the right list
    std::unordered_map<int, int> right_count;
    for (const auto& value : right) {
        ++right_count[value];
    }

    // Calculate the total similarity
    for (const auto& value : left) {
        total_similarity += value * right_count[value];
    }

    // Output the total similarity
    std::cout << "Total similarity: " << total_similarity << std::endl;
}
