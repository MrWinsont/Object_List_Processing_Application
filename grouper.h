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

template<typename GroupFunc, typename SortFunc>
std::vector<Group> GroupObject(const std::vector<Object>& objs, GroupFunc groupFunction, SortFunc sortFunction) {
    std::map<std::string, std::vector<Object>> groupMap;

    for (const auto& item : objs) {
        groupMap[groupFunction(item)].push_back(item);
    }

    for (auto& [name, vec] : groupMap) {
        std::sort(vec.begin(), vec.end(), sortFunction);
    }

    std::vector<Group> res;
    for (auto& [name, vec] : groupMap) {
        res.push_back({ name, std::move(vec) });
    }

    return res;
}

std::vector<Group> GroupByDistance(const std::vector<Object>& objs);

std::vector<Group> GroupByTime(const std::vector<Object>& objs);

std::vector<Group> GroupByName(const std::vector<Object>& objs);

std::vector<Group> GroupByType(const std::vector<Object>& objs);