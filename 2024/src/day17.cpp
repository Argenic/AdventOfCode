#include <iostream>
#include "day17.hpp"
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
#include <unordered_set>
#include <bitset>
#include <cmath>

std::tuple<long, long, long, std::vector<int>> processInput(const std::vector<std::string>& input) {
    long a_register = std::stol(input[0].substr(input[0].find_last_of(' ') + 1));
    int b_register = std::stoi(input[1].substr(input[1].find_last_of(' ') + 1));
    int c_register = std::stoi(input[2].substr(input[2].find_last_of(' ') + 1));

    std::string program_string = input[4].substr(input[4].find_last_of(' ') + 1);
    std::vector<int> program;

    std::stringstream ss(program_string);
    std::string token;
    while (std::getline(ss, token, ',')) {
        program.push_back(std::stoi(token));
    }

    return std::make_tuple(a_register, b_register, c_register, program);
}

int resolveCombo(int operand, int a_register, int b_register, int c_register) {
    int value = 0;
    switch (operand) {
        case 0:
        case 1:
        case 2:
        case 3:
            value = operand;
            break;
        case 4:
            value = a_register;
            break;
        case 5:
            value = b_register;
            break;
        case 6:
            value = c_register;
            break;
        case 7:
            std::cout << "Illegal combo" << std::endl;
            break;
    }
    return value;
}

void executeInstruction(int opcode, int operand, long& a_register, long& b_register, long& c_register, std::vector<int>& output, int& needle) {
    int value;
    int demominator;
    switch (opcode) {
        case 0: // adv << FINISHED!!!
            a_register = a_register / std::pow(2, resolveCombo(operand, a_register, b_register, c_register));
            break;
        case 1: // bxl << FINISHED!!!
            b_register = b_register ^ operand;
            break;
        case 2: // bst << FINISHED!!!
            b_register = resolveCombo(operand, a_register, b_register, c_register) % 8;
            break;
        case 3: // jnz << FINISHED!!!
            if(a_register != 0) {
                needle = operand - 2;
            }
            break;
        case 4: // bxc << FINISHED!!!
            b_register = b_register ^ c_register;
            break;
        case 5: // out << FINISHED!!!
            output.push_back(resolveCombo(operand, a_register, b_register, c_register) % 8);
            break;
        case 6: // bdv
            std::cout << "bdv " << operand << std::endl;
            break;
        case 7: // cdv << FINISHED!!!
            c_register = a_register / std::pow(2, resolveCombo(operand, a_register, b_register, c_register));
            break;
    }
}

std::string vectorToString(const std::vector<int>& vec) {
    if (vec.empty()) return "";

    std::ostringstream oss;
    oss << vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        oss << "," << vec[i];
    }
    return oss.str();
}

// Part 1 of Day 17
void day17part01() {
    std::cout << "\nDay 17 Part 1:" << std::endl;
    std::cout << "Find the debug code\n";
    
    // Clean up input
    auto input = utils::readLines("../2024/data/day17.txt");
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }
    
    // Process input
    auto [a_register, b_register, c_register, program] = processInput(input);

    // Run program
    std::vector<int> output;
    int needle = 0;

    for(needle = 0; needle < program.size(); needle += 2) {
        
        int opcode = program[needle];
        int operand = program[needle + 1];

        executeInstruction(opcode, operand, a_register, b_register, c_register, output, needle);
    }

    std::cout << "Code: " << vectorToString(output) << std::endl;
}

// Part 2 of Day 17
void day17part02() {
    std::cout << "\nDay 17 Part 2:" << std::endl;
    std::cout << "Value of register A to get full circle\n";
    
    // Clean up input
    auto input = utils::readLines("../2024/data/day17.txt");
    for (auto& line : input) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
    }
    
    // Process input
    auto [a_register, b_register, c_register, program] = processInput(input);
    std::string match = vectorToString(program);
    
    // Run program
    std::vector<int> output;
    int needle = 0;
    long counter = 35100000000000;
    int size_score = 0;
    while(vectorToString(output) != match) {
        if(counter % 100000000 == 0) {
            std::cout << "Iteration: " << counter << std::endl;
        }

        if(output.size() > size_score) {
            size_score = output.size();
            std::cout << "Size: " << size_score << " at " << counter << std::endl;
        }

        a_register = counter;
        output.clear();
        for(needle = 0; needle < program.size(); needle += 2) {
            int opcode = program[needle];
            int operand = program[needle + 1];

            executeInstruction(opcode, operand, a_register, b_register, c_register, output, needle);
        }

        counter++;
    }

    
    std::cout << "Iteration: " << counter - 1    << std::endl;
}