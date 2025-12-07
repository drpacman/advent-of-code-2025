#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("../day7/input");
    std::string line;
    std::vector<std::vector<long>> lines;
    while (std::getline(file, line)) {
        std::vector<long> row;
        for (char c : line) {
            if (c == 'S') {
                row.emplace_back(1);
            } else if (c == '^') {
                row.emplace_back(-1);
            } else {
                row.emplace_back(0);
            }
        }
        lines.push_back(row);
    }
    file.close();

    long part1 = 0;
    long part2 = 0;
    for (size_t y = 1; y < lines.size(); ++y){
        for (size_t x = 0; x < lines[y].size(); ++x){
            if (lines[y-1][x] > 0){
                if (lines[y][x] == -1) {
                    lines[y][x-1] += lines[y-1][x];
                    lines[y][x+1] += lines[y-1][x];
                    part1++;
                } else {
                    lines[y][x] += lines[y-1][x];
                }
            }
        }
    }
    for (size_t x = 0; x <lines.back().size();++x){
        if (lines.back()[x] > 0){
            part2 += lines.back()[x];
        }
    }

    std::cout << "Part1: " << part1 << "\n";
    std::cout << "Part2: " << part2 << "\n";
    return 0;
}