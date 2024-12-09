#include <iostream>
#include "day09.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <map>

// Part 1 of Day 9
void day09part01() {
    std::cout << "\nDay 9 Part 1:" << std::endl;
    std::cout << "Checksum the files and directories\n";
    const auto input = utils::readLines("../2024/data/day09.txt");

    int file_id = 0;
    
    std::map<int, std::string> mapped_input;
    bool is_file = true;
    int idx = 0;
    for(int i = 0; i < input[0].size(); i++) {
        if(is_file) {
            int amount = input[0][i] - '0';
            for (int j = 0; j < amount; j++) {
                mapped_input[idx] += std::to_string(file_id);
                idx++;
            }
            file_id++;
        } else {
            int amount = input[0][i] - '0';
            for (int j = 0; j < amount; j++) {
                mapped_input[idx] = ".";
                idx++;
            }
        }
        is_file = !is_file;
    }
    

    std::map<int, int> processed_input;
    int reversed_index = mapped_input.size() - 1;
    idx = 0;

    for(int i = 0; i < mapped_input.size(); i++) {
        if(mapped_input[i] == ".") {
            while(mapped_input[reversed_index] == ".") {
                reversed_index--;
            }
            if(reversed_index > i) {
                processed_input[idx] = std::stoi(mapped_input[reversed_index]);
                reversed_index--;
                idx++;
            } else {
                break;
            }
        } else {
            if(i > reversed_index) {
                break;
            }
            processed_input[idx] = std::stoi(mapped_input[i]);
            idx++;
        }
    }

    long count = 0;
    for(long i = 0; i < processed_input.size(); i++) {
        count += processed_input[i] * i;
    }

    std::cout << "File checksum: " << count << std::endl;
}

// Part 2 of Day 9
void day09part02() {
    std::cout << "\nDay 9 Part 2:"<< std::endl;
    std::cout << "Checksum the files and directories\n";    
    const auto input = utils::readLines("../2024/data/day09.txt");

    int file_id = 0;
    
    std::map<int, std::string> mapped_input;
    bool is_file = true;
    int idx = 0;
    for(int i = 0; i < input[0].size(); i++) {
        if(is_file) {
            int amount = input[0][i] - '0';
            for (int j = 0; j < amount; j++) {
                mapped_input[idx] += std::to_string(file_id);
                idx++;
            }
            file_id++;
        } else {
            int amount = input[0][i] - '0';
            for (int j = 0; j < amount; j++) {
                mapped_input[idx] = ".";
                idx++;
            }
        }
        is_file = !is_file;
    }
    

    std::map<int, int> processed_input;
    int reversed_index = mapped_input.size() - 1;
    idx = 0;

    // Initialize variables
    std::string current_marker = mapped_input[mapped_input.size() - 1];
    bool is_marker = true;
    int marker_count = 0;
    
    // Loop backwards through mapped_input
    for(int right = mapped_input.size() - 1; right >= 0; right--) {
        // Possible reset check.
        if(!is_marker && mapped_input[right] != ".") {
            is_marker = true;
            marker_count = 0;
            current_marker = mapped_input[right];
        }

        // If we are collecting a marker, try to find matches to count the size required.
        if(is_marker) {
            // If we find a different character then our current marker, then start to find a spot for it.
            if(mapped_input[right] != current_marker) {
                
                // Define outise of loop variables
                is_marker = false;
                int space_count = 0;

                // Look forwards and try to find a gap of dots.
                for (int left = 0; left < right; left++) {

                    // If we find a dot, then count it.
                    if(mapped_input[left] == ".") {
                        space_count++;
                    } else {
                        // If we find a different character, then check if we have a gap of dots.
                        if(space_count > 0) {
                            // If we have a gap of dots, then we can squeeze in the marker.
                            if(space_count >= marker_count) {
                                // Shuffle values to the left.
                                for(int i = 0; i < marker_count; i++) {
                                    mapped_input[left - space_count + i] = current_marker;
                                    mapped_input[right + i + 1] = ".";
                                }
                                break; // Exit loop after shuffling
                            } else {
                                space_count = 0;
                            }
                        }
                    }
                }
                right++; // Adjust right index
            } else if(mapped_input[right] != "." && is_marker) {
                // Keep on counting the markers.
                marker_count++;
            }
        }
    }
    
    long count = 0;

    for(auto i : mapped_input) {
        if(i.second != ".") {
            count += std::stoi(i.second) * i.first;
        }
    }
    
    std::cout << "File checksum: " << count << std::endl;
}