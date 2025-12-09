#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

class Point {
  public:
    Point(long x, long y, long z) : x_(x), y_(y), z_(z) {}
    long GetX() const { return x_; }
    long GetY() const { return y_; }
    long GetZ() const { return z_; }
    long distance(const Point &other) const {
        return (x_ - other.x_)*(x_ - other.x_) + (y_ - other.y_)*(y_ - other.y_) + (z_ - other.z_)*(z_ - other.z_);
    }
    bool operator==(const Point &other) const {
        return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }
    bool operator<(const Point &other) const {
        if (x_ != other.x_) return x_ < other.x_;
        if (y_ != other.y_) return y_ < other.y_;
        return z_ < other.z_;
    }
  private:
    long  x_;
    long y_;
    long z_;
};

void handle_point_pair(std::vector<std::set<Point>> &constellations, Point p1, Point p2){
    int set_index_p1 = -1;
    int set_index_p2 = -1;
    for (int i=0; i< constellations.size();++i){
        if (set_index_p1 == -1){
            if (constellations[i].find(p1) != constellations[i].end()){
                set_index_p1 = i;
            }
        }
        if (set_index_p2 == -1){
            if (constellations[i].find(p2) != constellations[i].end()){
                set_index_p2 = i;
            }
        }            
    }
    if (set_index_p1 == -1 && set_index_p2 == -1){
        std::set<Point> new_set;
        new_set.insert(p1);
        new_set.insert(p2);
        constellations.push_back(new_set);
    } else if (set_index_p1 != -1 && set_index_p2 != -1){
        if (set_index_p1 != set_index_p2){
            for (auto &p: constellations[set_index_p2]){
                constellations[set_index_p1].insert(p);
            }
            constellations.erase(constellations.begin() + set_index_p2);
        }
    } else if (set_index_p1 != -1){
        constellations[set_index_p1].insert(p2);
    } else if (set_index_p2 != -1){
        constellations[set_index_p2].insert(p1);
    } 
}

int part1(const std::vector<std::pair<std::pair<Point, Point>, long>> &distances, int entries) {
    std::vector<std::set<Point>> constellations;
    for (int i=0; i < entries;i++){
        auto &pair_dist = distances[i];
        Point p1 = pair_dist.first.first;
        Point p2 = pair_dist.first.second;
        handle_point_pair(constellations, p1, p2);        
    }
    // sort by constellation size
    std::sort(constellations.begin(), constellations.end(), [](const auto &a, const auto &b){
        return a.size() > b.size();
    });
    return constellations[0].size() * constellations[1].size() * constellations[2].size();
}

long part2(const std::vector<std::pair<std::pair<Point, Point>, long>> &distances, std::vector<Point> &points) {
    std::vector<std::set<Point>> constellations;
    for (int i=0; i < distances.size(); i++){
        auto &pair_dist = distances[i];
        Point p1 = pair_dist.first.first;
        Point p2 = pair_dist.first.second;
        handle_point_pair(constellations, p1, p2);
        points.erase(std::remove_if(points.begin(), points.end(), [&](Point p){
            return (p == p1) || (p == p2);
        }), points.end());
        if (points.size() == 0 && constellations.size() == 1){
            return p1.GetX() * p2.GetX();
        }
    }
    return 0;
}

int main(){
    std::ifstream file("../day8/input"); 
    std::string line;
    std::vector<Point> points;
    while (std::getline(file, line)) {
        // split line on commas into integers
        std::vector<int> coords;
        auto pos = line.find(',');
        long x = std::stol(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(',');
        long y = std::stol(line.substr(0, pos));
        line.erase(0, pos + 1);
        long z = std::stol(line.substr(0));
        points.emplace_back(Point(x, y, z));        
    }
    std::vector<std::pair<std::pair<Point, Point>, long>> distances;
    for (size_t i=0; i<points.size() - 1; ++i){
        for (size_t j=i+1; j<points.size(); ++j){
            long dist = points[i].distance(points[j]);
            distances.emplace_back(std::make_pair(points[i], points[j]), dist);
        }
    }
    std::sort(distances.begin(), distances.end(), [](const auto &a, const auto &b){
        return a.second < b.second;
    });
    int part1_result = part1(distances, 1000);
    std::cout << "Part1: " << part1_result << "\n";

    long part2_result = part2(distances, points);
    std::cout << "Part2: " << part2_result << "\n";

    file.close();
    return 0;
}