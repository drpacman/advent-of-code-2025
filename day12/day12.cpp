#include<iostream>
#include<fstream>
#include<string>
#include<map>

int main(){
    std::ifstream file("../day12/input"); 
    std::string line;
    std::map<int, int> pieces;
    bool grids = false;
    int total = 0;
    while (std::getline(file, line)) {
        // read first line, split on :
        size_t colon_pos = line.find(':');
        if (line.substr(0, colon_pos).find('x') != std::string::npos) {
            grids = true;
        }
        if (!grids){
            int node = std::stoi(line.substr(0, colon_pos));
            
            // read next 3 lines, count #s in those lines
            int block_count = 0;
            for (int i = 0; i < 3; ++i){
                std::getline(file, line);
                for (char c : line){
                    if (c == '#'){
                        block_count++;
                    }
                }
            }
            pieces.emplace(node, block_count);
            std::getline(file, line); // read blank line
        } else {
            std::string grid = line.substr(0, colon_pos);
            int x_pos = grid.find('x');
            int w = std::stoi(grid.substr(0, x_pos));
            int h = std::stoi(grid.substr(x_pos + 1));
            int max_area = w * h;
            std::string counts = line.substr(colon_pos + 2);
            int area = 0;
            int block_number = 0;
            auto next = counts.find(' ');
            while (next != std::string::npos){
                int count = std::stoi(counts.substr(0, next));
                area += count * (pieces.at(block_number));
                counts = counts.substr(next + 1);
                next = counts.find(' ');
                block_number++;
            }
            int count = std::stoi(counts);
            area += count * (pieces.at(block_number));
                
            if (max_area >= area){
                total++;
            }
        }        
    }
    std::cout << "Total grids that can be formed: " << total << "\n";
    return 0;
}