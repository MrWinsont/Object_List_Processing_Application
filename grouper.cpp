#include "grouper.h"

std::vector<Group> GroupByDistance(const std::vector<Object>& objs) {
    std::map<std::string, std::vector<Object>> groupMap;

    for (const auto& item : objs) {
        auto dist = item.Dist();
        std::string groupName;

        if (dist <= 100.0)
            groupName = "до 100 ед.";
        else if (dist <= 1000.0)
            groupName = "до 1000 ед.";
        else if (dist <= 10000.0)
            groupName = "до 10000 ед.";
        else
            groupName = "далеко";

        groupMap[groupName].push_back(item);
    }

    for (auto& [name, vec] : groupMap) {
        std::sort(vec.begin(), vec.end(), [](const Object& a, const Object& b) {
            return a.Dist() < b.Dist();
            });
    }

    std::vector<Group> res;
    for (auto& [name, vec] : groupMap) {
        res.push_back({ name, std::move(vec) });
    }

    return res;
}