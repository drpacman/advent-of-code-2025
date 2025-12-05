#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main(){
    std::ifstream file("../day5/input");
    std::string line;
    std::regex line_regex("(\\d+)\\-(\\d+)");
    std::vector<std::pair<long, long>> ranges;
    while (std::getline(file, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, line_regex)) {
            long a = std::stol(matches[1]);
            long b = std::stol(matches[2]);
            ranges.emplace_back(a, b);
        } else {
            break;
        }         
    }
    std::getline(file, line);
    int total = 0;
    while (std::getline(file, line)) {
        long value = std::stol(line);
        for (auto &range: ranges){
            if (value >= range.first && value <= range.second){
                total++;
                break;
            }
        }
    }
    std::cout << "Part 1 - " << total << "\n";
    std::sort(ranges.begin(), ranges.end(), [](const std::pair<long, long>& a, const std::pair<long, long>& b) {
        return a.first < b.first;
    });
    long part2 = 0;
    long current_max = 0;
    for (auto &range: ranges){
        if (range.first > current_max + 1){
            part2 += (range.second - range.first) + 1;
        } else if (range.second > current_max){
            part2 += range.second - current_max;
        } 
        current_max = std::max(current_max, range.second);
    }
    std::cout << "Part 2 - " << part2 << "\n";
    file.close();
    return 0;
}