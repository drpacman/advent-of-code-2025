#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::vector<std::pair<long, long>> parse_ranges(const std::string &range_str) {
    std::vector<std::pair<long, long>> ranges;
    size_t start = 0;
    size_t end = 0;

    while (end != std::string::npos) {
        end = range_str.find(',', start);
        std::string token = range_str.substr(start, (end == std::string::npos) ? std::string::npos : end - start);
        size_t dash_pos = token.find('-');
        if (dash_pos != std::string::npos) {
            long range_start = std::stol(token.substr(0, dash_pos));
            long range_end = std::stol(token.substr(dash_pos + 1));
            ranges.emplace_back(range_start, range_end);
        } else {
            long single_value = std::stol(token);
            ranges.emplace_back(single_value, single_value);
        }
        start = (end == std::string::npos) ? end : end + 1;
    }

    return ranges;
}

long check_ranges(std::vector<std::pair<long, long>> ranges, bool part1) {
    long total = 0;
    for (const auto &range : ranges) {
        for (long i = range.first; i <= range.second; ++i) {
            std::string num_str = std::to_string(i);
            int len = num_str.length();
            int end = 1;
            if (part1){
                if (len % 2 != 0){
                    continue;
                } else {
                    end = len/2;
                }
            }
            for (int n = end; n <= (len/2); ++n){
                if (len % n == 0){            
                    std::string first = num_str.substr(0, n);
                    std::string repeated;
                    for (int r = 0; r < len/n; ++r){
                        repeated += first;
                    }
                    if (num_str == repeated){
                        total += i;
                        break;
                    }   
                }             
            }
        }
    }
    return total;
}

int main() {
    std::ifstream file("../day2/input"); 
    std::string line;
    std::getline(file, line);
    std::vector<std::pair<long, long>> ranges = parse_ranges(line);
    std::cout << "Part 1 - " << check_ranges(ranges, true) << "\n";
    std::cout << "Part 2 - " << check_ranges(ranges, false) << "\n";
    return 0;
}