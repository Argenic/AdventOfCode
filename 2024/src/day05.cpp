#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include "day05.hpp"
#include "utils.hpp"
#include <unordered_map>

void splitLinesIntoMarkersAndSamples(const std::vector<std::string>& input, 
                                     std::vector<std::string>& markers, 
                                     std::vector<std::string>& samples) {
    bool toggle = true;

    for (const std::string& line : input) {
        std::string trimmedLine = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

        if(trimmedLine.empty()) {
            toggle = false;
            continue;
        }

        if(toggle) {
            markers.push_back(trimmedLine);
        } else {
            samples.push_back(trimmedLine);
        }
    }
}

void createLookupTable(const std::vector<std::string>& markers, 
                       std::unordered_map<int, std::vector<std::pair<int, int>>>& keyValues) {
    for(const std::string& marker : markers) {
        // Split marker by |
        int left = std::stoi(marker.substr(0, marker.find('|')));
        int right = std::stoi(marker.substr(marker.find('|') + 1));
        std::pair<int, int> pair = std::make_pair(left, right);

        // Setup the key values
        keyValues[left].push_back(pair);
        keyValues[right].push_back(pair);
    }
}

std::vector<int> processSample(const std::string& sample) {
    // Break up the sample per comma
    std::vector<int> sampleNumbers;
    std::stringstream ss(sample);
    std::string number;
    while(std::getline(ss, number, ',')) {
        sampleNumbers.push_back(std::stoi(number));
    }
    return sampleNumbers;
}

bool validateSample(const std::string& sample, 
                    const std::vector<int>& sampleNumbers, 
                    const std::unordered_map<int, std::vector<std::pair<int, int>>>& keyValues) {
    for(int i = 0; i < sampleNumbers.size(); i++) {
        int currentNumber = sampleNumbers[i];
        // Compare to other values
        for(int j = 0; j < sampleNumbers.size(); j++) {
            if(i != j) {
                std::vector<std::pair<int, int>> currentMarkers = keyValues.at(currentNumber);
                if(j < i) {
                    // Should be on the right side of things
                    for(const std::pair<int, int>& marker : currentMarkers) {
                        if(marker.second == sampleNumbers[j]) {
                            return false;
                        }
                    }
                } else {
                    // Should be on the left side of things
                    for(const std::pair<int, int>& marker : currentMarkers) {
                        if(marker.first == sampleNumbers[j]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void day05part01() {
    // Output the header
    std::cout << "\nDay 5 Part 1:\n";
    std::cout << "Find all valid lines and add up the middle value\n";
    const std::vector<std::string> input = utils::readLines("../2024/data/day05.txt");

    int total = 0;
    
    std::vector<std::string> markers;
    std::vector<std::string> samples;

    // Call the function to split lines
    splitLinesIntoMarkersAndSamples(input, markers, samples);
    
    // Create a vector of pairs out of this in C++ standards
    std::unordered_map<int, std::vector<std::pair<int, int>>> keyValues;

    // Call the function to create the lookup table
    createLookupTable(markers, keyValues);

    for(const std::string& sample : samples) {
        // Process each sample
        std::vector<int> sampleNumbers = processSample(sample);
        
        // Validate the sample
        if(validateSample(sample, sampleNumbers, keyValues)) {
            total += sampleNumbers[(sampleNumbers.size() - 1) / 2];
        } 
    }

    std::cout << "Total: " << total << std::endl;
}

void day05part02() {
    // Output the header
    std::cout << "\nDay 5 Part 2:\n";
    std::cout << "Fix all corrupted lines, find the middle value of the fixed lines\n";
    const std::vector<std::string> input = utils::readLines("../2024/data/day05.txt");
    
    
    int total = 0;
    
    std::vector<std::string> markers;
    std::vector<std::string> samples;

    // Call the function to split lines
    splitLinesIntoMarkersAndSamples(input, markers, samples);
    
    // Create a vector of pairs out of this in C++ standards
    std::unordered_map<int, std::vector<std::pair<int, int>>> keyValues;

    // Call the function to create the lookup table
    createLookupTable(markers, keyValues);
    std::vector<std::vector<int>> brokenSamples;

    // Find all broken samples,
    for(const std::string& sample : samples) {
        // Process each sample
        std::vector<int> sampleNumbers = processSample(sample);
        
        // Validate the sample
        if(!validateSample(sample, sampleNumbers, keyValues)) {
            brokenSamples.push_back(sampleNumbers);
        } 
    }

    // Fix the samples
    for(const std::vector<int>& sample : brokenSamples) {
        std::vector<int> fixed;
        for (int i = 0; i < sample.size(); i++) {
            int currentNumber = sample[i];

            if (fixed.empty()) {
                fixed.push_back(currentNumber);
            } else {
                const auto& currentMarkers = keyValues.at(currentNumber);
                bool inserted = false;

                for (int j = 0; j < fixed.size(); j++) {
                    int previousNumber = fixed[j];

                    for (const auto& marker : currentMarkers) {
                        if (marker.second == previousNumber) {
                            fixed.insert(fixed.begin() + j, currentNumber);
                            inserted = true;
                            
                            break;
                        }
                    }

                    if (inserted) {
                        break;
                    }
                }

                if (!inserted) {
                    fixed.push_back(currentNumber);
                }
            }
        }

        total += fixed[(fixed.size() - 1) / 2];
    }

    std::cout << "Total : " << total << std::endl;
}