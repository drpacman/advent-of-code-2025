#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

int find_shortest_sequence(int target, 
          std::vector<int> &button_sets, 
          std::set<int> all_lights,
          int depth) {
    std::set<int> next_lights;
    for (auto l : all_lights){
        for (auto &button_set: button_sets){
            for (auto &button: button_sets){
                int lights = l ^ button;
                if (lights == target){
                    return depth;
                }
                next_lights.emplace(lights);
            }
        }
    }
    return find_shortest_sequence(target, button_sets, next_lights, depth + 1);
}

long find_min_matching_sequence(std::vector<int> joltage, std::vector<int> &button_sets, std::map<std::vector<int>, long> &memo){
    int target = 0;
    long MISS = 1 << 15;
    for (int j = joltage.size(); j > 0; j--){
        target = target << 1 | ((joltage[j-1] % 2) == 1);        
    }
    int total_buttons = joltage.size();
    int button_combinations = 1 << button_sets.size(); 
    long min_sequence = MISS;
    for (int i = 0; i < button_combinations; ++i){
        int result = 0;
        long sequence_length = 0;
        int size = button_sets.size();
        std::vector<int> active_sets;
        for (int j = 0; j < size; ++j){
            if (i & (1 << j)){
                result ^= button_sets[j];
                active_sets.push_back(j);
                sequence_length++;
            }
        }
        if (result == target){
            std::vector<int> joltage_next = joltage;
            bool all_zeros = true;
            for (auto j : active_sets){
                int buttons = button_sets[j];
                for (int n = 0; n < total_buttons; ++n){
                    if (buttons & (1 << n)){
                        joltage_next[n] = joltage_next[n] - 1;
                        if (joltage_next[n] > 0) {
                            all_zeros = false;
                        }
                        if (joltage_next[n] < 0){
                            sequence_length = MISS;
                        }
                    }            
                }
            }
            for (int n = 0; n < joltage_next.size(); ++n){
                joltage_next[n] = joltage_next[n] / 2;
                if (joltage_next[n] != 0) {
                    all_zeros = false;
                }
            }
            if (all_zeros) {
                min_sequence = std::min(min_sequence, sequence_length);
            } else {
                if (sequence_length == MISS){
                    continue;
                } else {
                    if (memo.find(joltage_next) == memo.end()) {
                        long next_sequence_length = find_min_matching_sequence(joltage_next, button_sets, memo);
                        memo.emplace(joltage_next, next_sequence_length);
                    } 
                    long next_sequence_length =  memo.at(joltage_next);
                    sequence_length = sequence_length + (2 * next_sequence_length);
                    min_sequence = std::min(min_sequence, sequence_length);
                }
            }
        } 
        active_sets.clear();
    } 
    return min_sequence;
}   

int main(){

    std::ifstream file("../day10/input"); 
    std::string line;
    long part1 = 0;
    long part2 = 0;
    while (std::getline(file, line)) {
        int target = 0;
        std::vector<int> button_sets;
        std::vector<int> buttons;
        std::vector<int> joltage;
        std::vector<int>* vec;
        int number = 0;
        int button = 0;
        int n = 0;

        for (size_t i=0; i<line.size(); ++i){
            switch (line[i]){
                case '[':
                    n = 0;
                    break;
                case ']':
                    break;
                case '(':
                    vec = &buttons;
                    break;
                case '{':
                    vec = &joltage;
                    break;
                case ')':
                    buttons.emplace_back(number);
                    number = 0;
                    button = 0;
                    for (auto &b: buttons){
                        button += std::pow(2, b);
                    }                  
                    button_sets.emplace_back(button);
                    buttons.clear();
                    break;
                case '}':
                case ',':
                    (*vec).emplace_back(number);
                    number = 0;
                    break;
                case ' ':
                    break;
                case '#':
                    target += (1 << n);
                    n++;
                    break;
                case '.':
                    n++;
                    break;
                default:
                    number = (number*10) + line[i] - '0';
            }
        }
        
        
        std::set<int> all_lights{0};
        part1 += find_shortest_sequence(target, button_sets, all_lights, 1);
        std::map<std::vector<int>, long> memo;
        part2 += find_min_matching_sequence(joltage, button_sets, memo);
        memo.clear();
    }
    std::cout << "Part 1 - " << part1 << "\n";      
    std::cout << "Part 2 - " << part2 << "\n";
    file.close();
    return 0;
}