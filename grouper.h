#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

#include "Objects.h"

template<typename GroupFunc, typename SortFunc>
std::vector<Group> GroupObject(const std::vector<ListObject>& objs, GroupFunc groupFunction, SortFunc sortFunction) {
    std::map<std::string, std::vector<ListObject>> groupMap;

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

namespace Grouper
{
    std::vector<Group> ByDistance(const std::vector<ListObject>& objs);

    std::vector<Group> ByTime(const std::vector<ListObject>& objs);

    std::vector<Group> ByName(const std::vector<ListObject>& objs);

    std::vector<Group> ByType(const std::vector<ListObject>& objs);
}
