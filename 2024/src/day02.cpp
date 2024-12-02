#include <iostream>
#include "day02.hpp"
#include "utils.hpp"
#include <algorithm>
#include <sstream>

std::vector<int> splitToInt(const std::string& line, char delimiter) {
    std::vector<int> numbers;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        numbers.push_back(std::stoi(token));
    }
    return numbers;
}

bool validateNumbers(std::vector<int> numbers) {
    // Check if the numbers are ascending or descending.
    if (!std::is_sorted(numbers.begin(), numbers.end()) && 
        !std::is_sorted(numbers.begin(), numbers.end(), std::greater<int>())) {
        return false;
    }

    // Check if unique.
    if (std::unique(numbers.begin(), numbers.end()) != numbers.end()) {
        return false;
    }

    // Check if the difference between each number is 1 - 3.
    for (int i = 1; i < numbers.size(); i++) {
        if (abs(numbers[i] - numbers[i - 1]) > 3) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Find the difference in 2 lists by sorting them Ascending.
 */
void day02part01() {
    // Output the header
    std::cout << "\nDay 2 Part 1:\n";
    std::cout << "Find only the safe reports, they have to be ascending or descending with 1 - 3 difference per step.\n";
    
    // Initialize the input values and setup the output param
    std::vector<std::string> input = utils::readLines("../2024/data/day02.txt");
    int safe_reports = 0;

    // Iterate every line and decide on safe or not
    for (const std::string& line : input) {
        // Split the line based on its spaces into integers and safeguard.
        std::vector<int> numbers = splitToInt(line, ' ');

        // Validate numbers
        if (validateNumbers(numbers)) {
            safe_reports++;
        }
    }

    // Output the total difference
    std::cout << "Amount of safe reports: " << safe_reports << std::endl;
}

/**
 * @brief Find the similarity between 2 lists.
 */
void day02part02() {
    // Output the header
    std::cout << "\nDay 2 Part 2:\n";
    std::cout << "Find the amount of reports given an error margin of 1\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day02.txt");

    // Collect end result
    int safe_reports = 0;

    // Iterate every line and decide on safe or not
    for (const std::string& line : input) {
        // Split the line based on its spaces into integers and safeguard.
        std::vector<int> numbers = splitToInt(line, ' ');
    
        // Validate numbers
        if (validateNumbers(numbers)) {
            safe_reports++;
            continue;
        }

        // Iterate every value in numbers and make a copy to validate the number again, if it is safe, increment the counter.
        for (int i = 0; i < numbers.size(); i++) {
            std::vector<int> copy = numbers;
            copy.erase(copy.begin() + i);
            if (validateNumbers(copy)) {
                safe_reports++;
                break;
            }
        }
    }

    // Output the total difference
    std::cout << "Amount of safe reports: " << safe_reports << std::endl;
}
