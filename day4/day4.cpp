#include <iostream>
#include <fstream>
#include <string>

std::vector<std::string> parse_input(std::ifstream &file) {
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.emplace_back(line);
    }
    return grid;
}

int main() {
    std::ifstream file("../day4/input"); 
    auto grid = parse_input(file);
    int width = grid[0].size();
    int height = grid.size();
    int part2 = 0;
    std::vector<std::pair<int, int>> remove_list;
    while (true){
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x] != '@') continue;
                int count = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;
                        if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
                            if (grid[y + dy][x + dx] == '@') {
                                count++;
                            }
                        }
                    }
                }
                if (count < 4){
                    remove_list.emplace_back(x, y);
                }
            }
        }
        if (remove_list.size() == 0){
            break;
        } else if (part2 == 0){
            std::cout << "Part1: " << remove_list.size() << std::endl;
        }
        part2 += remove_list.size();
        for (auto &p: remove_list){
            grid[p.second][p.first] = 'x';
        }
        remove_list.clear();
    }
    std::cout << "Part2: " << part2 << std::endl;
    file.close();
    
    return 0;
}