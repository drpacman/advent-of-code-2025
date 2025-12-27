#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

class VisitedNode {
public:
    std::string name;
    bool visited_dac;
    bool visited_fft;
    VisitedNode(std::string n, bool vd, bool vf) : name(n), visited_dac(vd), visited_fft(vf) {}

    bool operator<(const VisitedNode& other) const {
        if (name != other.name) return name < other.name;
        if (visited_dac != other.visited_dac) return visited_dac < other.visited_dac;
        return visited_fft < other.visited_fft;
    }
};

void find_routes(std::string current_node,
                     std::map<std::string, std::vector<std::string>> &signal_map,                      
                     int &total_routes) {
    if (current_node == "out") {
        total_routes++;
        return;
    }
    std::vector<std::string> &next_nodes = signal_map.at(current_node);
    for (auto &node: next_nodes){
        find_routes(node, signal_map, total_routes); 
    }
    return;
}

void find_routes_part2(std::string current_node,
                       bool visited_dac,
                       bool visited_fft,
                       std::map<VisitedNode, long> &memo,
                       std::map<std::string, std::vector<std::string>> &signal_map) {
    if (current_node == "out") {
        if (visited_dac && visited_fft){
            memo[VisitedNode(current_node, visited_dac, visited_fft)] = 1;
        } else {
            memo[VisitedNode(current_node, visited_dac, visited_fft)] = 0;
        }
    } else {
        std::vector<std::string> &neighbours = signal_map.at(current_node);
        for (auto &neighbour: neighbours){
            bool next_visited_dac = visited_dac || (current_node == "dac");
            bool next_visited_fft = visited_fft || (current_node == "fft");
            VisitedNode next_visited_node(neighbour, next_visited_dac, next_visited_fft);
            if (memo.find(next_visited_node) == memo.end()){
                find_routes_part2(neighbour, next_visited_dac, next_visited_fft, memo, signal_map);
            }
            memo[VisitedNode(current_node, visited_dac, visited_fft)] += memo.at(next_visited_node);
        }
    }
}

void load_signal_map(std::string filepath, std::map<std::string, std::vector<std::string>> &signal_map) {
    std::ifstream file(filepath); 
    std::string line;
    while (std::getline(file, line)) {
        std::array<char, 3> in = {line[0], line[1], line[2]};
        std::vector<std::string> outputs;
        for (int i = 5; i < line.size(); i += 4) {
            std::array<char, 3> out = {line[i], line[i+1], line[i+2]};
            outputs.push_back(std::string(out.data(), 3));
        }
        signal_map.emplace(std::string(in.data(), 3), outputs);
    }
    file.close();
}

int main(){
    std::map<std::string, std::vector<std::string>> signal_map;
    load_signal_map("../day11/input", signal_map);
    int total_routes = 0;
    std::set<std::string> required;
    find_routes("you", signal_map, total_routes);
    std::cout << "Part 1: " << total_routes << "\n";

    std::map<VisitedNode, long> memo;
    find_routes_part2("svr", false, false, memo, signal_map);
    std::cout << "Part 2: " << memo.at(VisitedNode("svr", false, false)) << "\n";
}