#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

struct Object
{
    std::string name;
    double x = 0.0;
    double y = 0.0;
    std::string type;
    double timestamp = 0.0;

    double Dist() const {
        return std::sqrt(x * x + y * y);
    }

    void Info() {
        std::cout << "name: " << name <<
            "; X: " << x <<
            "; Y: " << y <<
            "; type: " << type <<
            "; timestamp: " << timestamp << "\n";
    }
};

struct Group
{
    std::string name;
    std::vector<Object> objGroup;
};

std::vector<Group> GroupByDistance(const std::vector<Object>& objs);

std::vector<Group> GroupByTime(const std::vector<Object>& objs) {
    
}