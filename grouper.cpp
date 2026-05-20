#include "grouper.h"

std::vector<Group> GroupByDistance(const std::vector<Object>& objs) {
    std::map<std::string, std::vector<Object>> groupMap;

    for (const auto& item : objs) {
        auto dist = item.Dist();
        std::string groupName = u8"далеко";

        if (dist <= 100.0)
            groupName = u8"до 100 ед.";
        else if (dist <= 1000.0)
            groupName = u8"до 1000 ед.";
        else if (dist <= 10000.0)
            groupName = u8"до 10000 ед.";

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

std::vector<Group> GroupByTime(const std::vector<Object>& objs) {
    std::map<std::string, std::vector<Object>> groupMap;

    auto now = std::chrono::system_clock::now();
    time_t curTime = std::chrono::system_clock::to_time_t(now);

    struct tm* now_tm = std::localtime(&curTime);
    int curYear = now_tm->tm_year + 1900;
    int curMonth = now_tm->tm_mon + 1;
    int curDay = now_tm->tm_mday;

    for (const auto& obj : objs)
    {
        time_t objTime = static_cast<time_t>(obj.timestamp);
        struct tm* obj_tm = std::localtime(&objTime);

        std::cout << obj_tm->tm_year + 1900 << " " << obj_tm->tm_mon + 1 << " " << obj_tm->tm_mday << "\n";

        std::string groupName = u8"Ранее";

        if (obj_tm->tm_year + 1900 == curYear &&
            obj_tm->tm_mon + 1 == curMonth &&
            obj_tm->tm_mday == curDay)
        {
            groupName = u8"Сегодня";
        }
        else if (obj_tm->tm_year + 1900 == curYear &&
            obj_tm->tm_mon + 1 == curMonth &&
            obj_tm->tm_mday == curDay - 1)
        {
            groupName = u8"Вчера";
        }
        else if (std::difftime(curTime, objTime) <= 7 * 24 * 3600)
        {
            groupName = u8"На этой неделе";
        }
        else if (obj_tm->tm_year + 1900 == curYear &&
            obj_tm->tm_mon + 1 == curMonth)
        {
            groupName = u8"В этом месяце";
        }
        else if (obj_tm->tm_year + 1900 == curYear)
        {
            groupName = u8"В этом году";
        }

        groupMap[groupName].push_back(obj);
    }

    for (auto& [name, vec] : groupMap)
    {
        std::sort(vec.begin(), vec.end(), [](const Object& a, const Object& b) {
            return a.timestamp > b.timestamp;
            });
    }

    std::vector<Group> res;
    for (auto& [name, vec] : groupMap) {
        res.push_back({ name, std::move(vec) });
    }

    return res;
}

std::vector<Group> GroupByName(const std::vector<Object>& objs) {
    std::map<std::string, std::vector<Object>> groupMap;

    for (const auto& item : objs) {
        std::string firstLetter;

        if (item.name.size() >= 2 && (unsigned char)item.name[0] == 0xD0 || (unsigned char)item.name[0] == 0xD1){
            firstLetter = item.name.substr(0, 2);
        }
        else{
            firstLetter = item.name[0];
        }

        std::string groupName = "#";
        if (firstLetter.size() == 2){
            groupName = firstLetter;
        }

        groupMap[groupName].push_back(item);
    }

    for (auto& [name, vec] : groupMap) {
        std::sort(vec.begin(), vec.end(), [](const Object& a, const Object& b) {
            return a.name < b.name;
        });
    }

    std::vector<Group> res;
    for (auto& [name, vec] : groupMap) {
        res.push_back({ name, std::move(vec) });
    }

    return res;
}

std::vector<Group> GroupByType(const std::vector<Object>& objs) {
    std::map<std::string, std::vector<Object>> groupMap;

    for (const auto& item : objs) {
        std::string groupName;
        
        auto typeCount = std::count_if(objs.begin(), objs.end(), [&item](const Object& a) {
            return a.type == item.type;
        });

        if (typeCount > 1)
            groupName = item.type;
        else
            groupName = u8"Разное";

        groupMap[groupName].push_back(item);
    }

    for (auto& [name, vec] : groupMap) {
        std::sort(vec.begin(), vec.end(), [](const Object& a, const Object& b) {
            return a.name < b.name;
        });
    }

    std::vector<Group> res;
    for (auto& [name, vec] : groupMap) {
        res.push_back({ name, std::move(vec) });
    }

    return res;
}