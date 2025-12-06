#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){
    std::ifstream file("../day6/input"); 
    std::string line;
    std::vector<char> action;
    std::vector<std::string> items;
    while (std::getline(file, line)) {
        std::vector<std::string> rows;
        if (line[0] == '*' || line[0] == '+'){
            for (int i=0;i<line.size();++i){
                if (line[i] == '*' || line[i] == '+'){
                    action.emplace_back(line[i]);
                }
            }
            break;
        }
        items.emplace_back(line);
    }
    int height = items.size();
    int width = items[0].size();
    
    long part1 = 0;
    std::vector<std::vector<int>> rows;
    for (int y=0; y<height;++y){
        int n = 0;
        std::vector<int> row;
        for (int x=0; x<width; ++x){
            if (items[y][x] != ' '){
                n = (10 * n) + (items[y][x] - '0');
            } else {
                if (n > 0)row.emplace_back(n);
                n = 0;
            }
        }
        if (n != 0){
            row.emplace_back(n);
        }
        rows.emplace_back(row);
    }
    for (int a=0; a<action.size(); ++a){
        char act = action[a];
        long result = rows[0][a];
        for (int r=1; r<rows.size(); ++r){
            if (act == '*'){
                result = result * rows[r][a];
            } else {
                result = result + rows[r][a];
            }
        }
        part1 += result;
    }
    std::cout << "Part1: " << part1 << "\n";
        
    long part2 = 0;
    int actionIndex = action.size() - 1;
    char act = action[actionIndex];
    std::vector<int> numbers;
    for (int x = width; x > 0; --x){
        int n = 0;
        for (int y=0; y < height; ++y){
            if (items[y][x-1] != ' '){
                n = 10*n + (items[y][x-1] - '0'); 
            }
        }
        if (n != 0){
            numbers.emplace_back(n);
            if (x > 1){
                continue;
            }
        }
        long result = numbers[0];
        for (int r=1; r<numbers.size(); ++r){
            if (act == '*'){
                result = result * numbers[r];
            } else {
                result = result + numbers[r];
            }
        }
        numbers.clear();
        act = action[--actionIndex];     
        part2 += result;
    }
    std::cout << "part2: " << part2 << "\n";
    file.close(); 
    return 0;
}