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
        if (numbers.size() < 2) continue;

        // Setup the first 2 values to compare
        int first_value = numbers[0];
        int second_value = numbers[1];
        
        // Validate the pair
        if (abs(first_value - second_value) > 3) continue;
        if (first_value == second_value) continue;

        // Setup the markers for later processing.
        bool going_up = first_value < second_value;
        bool safe = true;
        int previous_value = second_value;

        // Iterate the rest of the lines.
        for (int i = 2; i < numbers.size(); i++) {
            // Decide on a current number to compare
            int current_value = numbers[i];

            // Validate the current and previous value based on direction and difference. 
            if ((going_up && previous_value >= current_value) || 
                (!going_up && previous_value <= current_value) || 
                abs(previous_value - current_value) > 3) {
                // If invalid mark and exit the loop.
                safe = false;
                break;
            }

            // Replace prev with current for next cycle,
            previous_value = current_value;
        }

        // Increment if safe.
        if (safe) {
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

    // Iterate every input line to verify if safe
    for (const std::string& line : input) {
        // Setup Markers
        bool safe = true;
        bool last_try = false;

        // Split numbers in lines and guard against incorrect input
        std::vector<int> numbers = splitToInt(line, ' ');
        if (numbers.size() < 2) continue;

        // Extract the first 2 values to decide where to start
        int first_value = numbers[0];
        int second_value = numbers[1];
        int start = 2;

        // Validate first pair
        if (
            abs(first_value - second_value) > 3 ||
            first_value == second_value
        ) {
            std::cout << "Ah Oh" << std::endl;
            // Invalid first try, last chance
            last_try = true;

            first_value = numbers[1];
            second_value = numbers[2];
            // Validate again,  
            if (
                abs(first_value - second_value) > 3 ||
                first_value == second_value
            ) {
                // Where out.
                std::cout << "Double Start Fail " << line << std::endl;
                continue;
            }
            start = 3;
        }

        // Decide direction
        bool going_up = first_value < second_value;
        
        // Setup previous_value to start the loop
        int previous_value = second_value;

        // Iterate the remainder and decide
        for (int i = start; i < numbers.size(); i++) {
            // Set the current value to match against
            int current_value = numbers[i];

            // Validate the previous and current value chanin based on the direction
            if ((going_up && previous_value >= current_value) || 
                (!going_up && previous_value <= current_value) || 
                abs(previous_value - current_value) > 3) {
                    // Decide if we go for a last try,
                    if(!last_try) {
                        last_try = true;
                        // 
                        previous_value = numbers[i-2];
                        // Go back one and match it with current.
                        if ((going_up && previous_value >= current_value) || 
                            (!going_up && previous_value <= current_value) || 
                            abs(previous_value - current_value) > 3) 
                        {
                            // If, i is the last element, then we can ignore this error and call it safe,
                            if(i == numbers.size() - 1) {
                                // Last element is wrong, we can ignore this.
                                continue;
                            }

                            // Go Forward, check if the is legit.
                            previous_value = numbers[i-1];
                            int next_value = numbers[i+1];
                            if ((going_up && previous_value >= next_value) || 
                                (!going_up && previous_value <= next_value) || 
                                abs(previous_value - next_value) > 3) 
                            {
                                //std::cout << "Double Fail: " << line << " " << previous_value << "x" << current_value <<  std::endl;
                                std::cout << "Double Failure: " << line << std::endl;
                                safe = false;
                                break;
                            } else {
                                current_value = next_value;
                                i++;
                            }
                        }
                    } else {
                        std::cout << "Failed Last Try " << line << std::endl;
                        safe = false;
                        break;
                    }
            }
            previous_value = current_value;
        }

        if (safe) {
            safe_reports++;
        }
    }

    // Output the total difference
    std::cout << "Amount of safe reports: " << safe_reports << std::endl;
}
