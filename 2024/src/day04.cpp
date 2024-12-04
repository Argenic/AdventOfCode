#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include "day02.hpp"
#include "utils.hpp"

void printGrid(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}


std::vector<std::vector<char>> rotateMatrix45Degrees(const std::vector<std::vector<char>>& matrix, bool clockwise = true) {
    int n = matrix.size();
    int m = matrix[0].size();
    std::vector<std::vector<char>> result(n + m - 1);

    if (clockwise) {
        // Collect elements along diagonals (top-left to bottom-right)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result[i + j].push_back(matrix[i][j]);
            }
        }
    } else {
        // Collect elements along diagonals (bottom-left to top-right)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result[(m - 1 - j) + i].push_back(matrix[i][j]);
            }
        }
    }

    return result;
}

// Create a 90 degree rotation of the matrix
std::vector<std::vector<char>> rotateMatrix90Degrees(const std::vector<std::vector<char>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    std::vector<std::vector<char>> result(m, std::vector<char>(n));

    // Transpose and reverse each row
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[j][n - 1 - i] = matrix[i][j];
        }
    }

    return result;
}

int countOccurences(const std::vector<std::vector<char>>& grid) {
    int count = 0;
    for (const auto& row : grid) {
        std::string rowString(row.begin(), row.end());
        std::regex xmasRegex("XMAS");
        std::regex samxRegex("SAMX");

        // Use regex iterators to find all occurrences of "XMAS"
        for (std::sregex_iterator it(rowString.begin(), rowString.end(), xmasRegex), end; it != end; ++it) {
            count++;
        }

        // Use regex iterators to find all occurrences of "SAMX"
        for (std::sregex_iterator it(rowString.begin(), rowString.end(), samxRegex), end; it != end; ++it) {
            count++;
        }
    }
    return count;
}

std::vector<std::vector<char>> createGrid(std::vector<std::string> input) {
    std::vector<std::vector<char>> grid;
    for (const auto& line : input) {
        std::vector<char> row;
        for (const auto& c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    return grid;
}

void day04part01() {
    // Output the header
    std::cout << "\nDay 4 Part 1:\n";
    std::cout << "Find all occurrences of XMAS in the grid\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day04.txt");
    std::vector<std::vector<char>> grid = createGrid(input);
    int count = 0;
    count += countOccurences(grid);
    // Flip 45 degrees clockwise
    std::vector<std::vector<char>> rotatedGrid = rotateMatrix45Degrees(grid, true);
    count += countOccurences(rotatedGrid);

    // Flip 45 degrees counter clockwise
    rotatedGrid = rotateMatrix45Degrees(grid, false);
    count += countOccurences(rotatedGrid);

    // Rotate it 90 degrees,
    rotatedGrid = rotateMatrix90Degrees(grid);
    count += countOccurences(rotatedGrid);
    
    std::cout << "Total times XMAS appears: " << count << std::endl;
}

void day04part02() {
    // Output the header
    std::cout << "\nDay 4 Part 2:\n";
    std::cout << "We got it wrong, find the X-MAS pattern instead.\n";
    std::vector<std::string> input = utils::readLines("../2024/data/day04.txt");
    std::vector<std::vector<char>> grid = createGrid(input);
    int count = 0;

    // Setup iterators
    int n = grid.size();
    int m = grid[0].size();

    // Loop the matrix, skip the boundary
    for(int i = 1 ; i < n - 1; i++) {
        for(int j = 1; j < m - 2; j++) {
            // Find the 'a' values,
            if(grid[i][j] == 'A') {
                int checker = 0;
                // Go check diagonals,
                if( (grid[i-1][j-1] == 'M' && grid[i+1][j+1] == 'S') || (grid[i-1][j-1] == 'S' && grid[i+1][j+1] == 'M')) {
                    checker++;
                } 
                if( (grid[i+1][j-1] == 'M' && grid[i-1][j+1] == 'S') || (grid[i+1][j-1] == 'S' && grid[i-1][j+1] == 'M')) {
                    checker++;
                }
                if (checker == 2) {
                    count++;
                }
            }
        }
    }

    // Output the total multiplications
    std::cout << "Total times X-MAS " << count << std::endl;
}