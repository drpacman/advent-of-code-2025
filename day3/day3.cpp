#include <iostream>
#include <fstream>
#include <string>

long calculate(const std::vector<int>& bank, int digits, long total) {
    auto max_it = std::max_element(bank.begin(), bank.end() - (digits - 1));
    long result = total*10 + *max_it;
    int max_index = std::distance(bank.begin(), max_it);
    if (digits > 1){
        return calculate(std::vector<int>(bank.begin() + max_index + 1, bank.end()), digits - 1, result);
    } 
    return result;
}

long do_part(std::vector<std::vector<int>> &banks, int digits){
    long total = 0;
    for (auto bank: banks) {
        total += calculate(bank, digits, 0);
    }
    return total;
}

int main() {
    std::ifstream file("../day3/input"); 
    std::string line;

    if (!file) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }
    std::vector<std::vector<int>> banks;
    while (std::getline(file, line)) {
        std::vector<int> bank;
        for (char c : line) {
            bank.push_back(c - '0');
        }
        banks.push_back(bank);
    }
    std::cout << "Part1: " << do_part(banks, 2) << std::endl;
    std::cout << "Part2: " << do_part(banks, 12) << std::endl;
    file.close();
    return 0;
}