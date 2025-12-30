#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Point {
  public:
    Point(long x, long y) : x_(x), y_(y) {}
    long GetX() const { return x_; }
    long GetY() const { return y_; }
    bool operator<(const Point& other) const {
        return (x_ < other.x_) || (x_ == other.x_ && y_ < other.y_);
    }   
  private:
    long x_;
    long y_;
};

bool on_vertical_line(const long x, const long y, const long x1, const long y1, const long y2){
    if (x == x1 && y >= y1 && y <= y2){
        return true;
    }
    return false;
}

bool intersects_vertical_line(const long x, const long y, const long x1, const long y1, const long y2){
    double gradient = (double)y / x;
    double potential_y = gradient * x1;
    if (potential_y < y)  return false;
    if (potential_y > y1 && potential_y < y2){
        return true;
    }
    return false;
}

bool on_horizontal_line(const long x, const long y, const long y1, const long x1, const long x2){
    if (y == y1 && x >= x1 && x <= x2){
        return true;
    }
    return false;
}

bool intersects_horizontal_line(const long x, const long y, const long y1, const long x1, const long x2){
    double gradient = (double)x / y;
    double potential_x = gradient * y1;
    if (potential_x < x)  return false;
    if (potential_x > x1 && potential_x < x2){
        return true;
    }
    return false;
}

bool is_inside(long x, long y, const std::vector<std::pair<int, std::pair<int, int>>>& vlines,
                          const std::vector<std::pair<int, std::pair<int, int>>>& hlines){
    int intersects = 0;
    for (const auto& vline : vlines){
        if (on_vertical_line(x, y, vline.first, vline.second.first, vline.second.second)){
            return true;
        }
        if (intersects_vertical_line(x, y, vline.first, vline.second.first, vline.second.second)){
            intersects++;
        }
    }
    for (const auto& hline : hlines){
        if (on_horizontal_line(x, y, hline.first, hline.second.first, hline.second.second)){
            return true;
        }
        
        if (intersects_horizontal_line(x, y, hline.first, hline.second.first, hline.second.second)){
            intersects++;
        }
    }
    if (intersects % 2 == 0){
        return false; 
    }
    return true;
}

class Area {
  public:
    Area(Point a, Point b) : a_(a), b_(b) {
        area = (1 +abs(a_.GetX() - b_.GetX())) *
               (1 + abs(a_.GetY() - b_.GetY()));
    }

    long GetArea() const {
        return area;
    }

    bool is_internal_area(const std::vector<std::pair<int, std::pair<int, int>>>& vlines,
                          const std::vector<std::pair<int, std::pair<int, int>>>& hlines) const {
        
        long min_x = a_.GetX() < b_.GetX() ? a_.GetX() : b_.GetX();
        long max_x = a_.GetX() > b_.GetX() ? a_.GetX() : b_.GetX();
        long min_y = a_.GetY() < b_.GetY() ? a_.GetY() : b_.GetY();
        long max_y = a_.GetY() > b_.GetY() ? a_.GetY() : b_.GetY();    
        // check the corners first to avoid big scans
        if (!is_inside(min_x,min_y,vlines, hlines)  || 
            !is_inside(max_x,min_y,vlines, hlines)  || 
            !is_inside(min_x,max_y,vlines, hlines)  ||
            !is_inside(max_x,max_y,vlines, hlines)){
                return false;
            }
        // check the edges only
        for (long x = min_x; x <= max_x; x++){
            if (!is_inside(x,min_y,vlines, hlines)  || !is_inside(x,max_y,vlines, hlines)){
                return false;
            }
        }
        for (long y = min_y; y <= max_y; y++){
            if (!is_inside(min_x,y,vlines, hlines)  || !is_inside(max_x,y,vlines, hlines)){
                return false;
            }
        }
        
        return true; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Area& area) {
        os << "Area " << area.area << " (" << area.a_.GetX() << ", " << area.a_.GetY() << ") to (" << area.b_.GetX() << ", " << area.b_.GetY() << ")";
        return os;
    }
  private:
    Point a_;
    Point b_;
    long area;
};

int main(){
    std::ifstream file("../day9/input"); 
    std::string line;
    std::vector<Point> points;
    std::vector<Area> areas;
    while (std::getline(file, line)) {
        auto pos = line.find(',');
        int x = std::stoi(line.substr(0, pos));
        int y = std::stoi(line.substr(pos+1));
        points.emplace_back(Point(x, y));
    }
    long max_area = 0;
    for (auto it = points.begin(); it != points.end();){
        auto it2 = std::next(it, 1);
        while (it2 != points.end()){
            Area area(*it, *it2);
            areas.emplace_back(area);
            it2++;
        }
        it++;
    }
    std::sort(areas.begin(), areas.end(), [](const Area &a, const Area &b) {
        return a.GetArea() < b.GetArea();
    });
    
    std::cout << "Part 1: " << areas.rbegin()->GetArea() << "\n";
    
    std::sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return (a.GetX() < b.GetX()) || (a.GetX() == b.GetX() && a.GetY() < b.GetY());
    });
    std::vector<std::pair<int, std::pair<int, int>>> vlines;
    for (auto it = points.begin(); it != points.end();){
        auto p1 = * it;
        auto p2 = *(++it);
        vlines.emplace_back(p1.GetX(), std::make_pair(p1.GetY(), p2.GetY()));
        ++it;
    }
    
    std::sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return (a.GetY() < b.GetY()) || (a.GetY() == b.GetY() && a.GetX() < b.GetX());
    });
    std::vector<std::pair<int, std::pair<int, int>>> hlines;    
    for (auto it = points.begin(); it != points.end();){
        auto p1 = * it;
        auto p2 = *(++it);
        hlines.emplace_back(p1.GetY(), std::make_pair(p1.GetX(), p2.GetX()));
        ++it;
    }
    
    std::cout << "Number of vertical lines: " << vlines.size() << ", horizontal lines: " << hlines.size() << " and number of areas: " << areas.size() << "\n";
    long count = 0;
    for (auto area_it = areas.rbegin(); area_it != areas.rend(); ++area_it){
        if (area_it->is_internal_area(vlines, hlines)){
            std::cout << (*area_it) << " is internal area \n";
            max_area = area_it->GetArea();
            break;
        }  
        if (count++ % 1000 == 0){
            std::cout << "Checked " << count << " areas so far, still looking...\n";
        }
    }

    std::cout << "Part 2: " << max_area << "\n";

    file.close();
    return 0;
}