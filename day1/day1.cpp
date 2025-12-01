#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("../day1/input"); // Open the file for reading
    std::string line;

    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }
    int pos = 50;
    int part1Count = 0;
    int part2Count = 0;
    while (std::getline(file, line)) {
        int value = std::stoi(line.substr(1));
        int rots = value / 100;
        int rem = value % 100;
        if (line[0] == 'L'){            
            int newpos = (pos + 100 - rem) % 100;
            if (newpos == 0){
                part1Count++;
                part2Count++;
            } else if (pos != 0 && newpos > pos){
                part2Count++;
            }
            pos = newpos;
        } else {
            int newpos = (pos + 100 + rem) % 100;
            if (newpos == 0){
                part1Count++;
                part2Count++;
            } else if (pos != 0 && newpos < pos){
                part2Count++;
            }
            pos = newpos;
        }
        part2Count += rots;
    }
    std::cout << "Part1: " << part1Count << std::endl;
    std::cout << "Part2: " << part2Count << std::endl;
    file.close(); 
    return 0;
}