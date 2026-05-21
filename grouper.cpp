#include "grouper.h"

static std::string ProcessDist(const ListObject& obj) {
    auto dist = obj.Dist();

    if (dist <= 100.0)
        return u8"до 100 ед.";
    else if (dist <= 1000.0)
        return u8"до 1000 ед.";
    else if (dist <= 10000.0)
        return u8"до 10000 ед.";

    return u8"далеко";
}

std::vector<Group> Grouper::ByDistance(const std::vector<ListObject>& objs) {
    auto sortFunc = [](const ListObject& a, const ListObject& b) {
        return a.Dist() < b.Dist();
        };

    return GroupObject(objs, ProcessDist, sortFunc);
}

static std::string ProcessTime(const ListObject& obj) {
    auto now = std::chrono::system_clock::now();
    time_t curTime = std::chrono::system_clock::to_time_t(now);

    struct tm* now_tm = std::localtime(&curTime);
    int curYear = now_tm->tm_year + 1900;
    int curMonth = now_tm->tm_mon + 1;
    int curDay = now_tm->tm_mday;

    time_t objTime = static_cast<time_t>(obj.timestamp);
    struct tm* obj_tm = std::localtime(&objTime);

    if (obj_tm->tm_year + 1900 == curYear &&
        obj_tm->tm_mon + 1 == curMonth &&
        obj_tm->tm_mday == curDay)
    {
        return u8"Сегодня";
    }
    else if (obj_tm->tm_year + 1900 == curYear &&
        obj_tm->tm_mon + 1 == curMonth &&
        obj_tm->tm_mday == curDay - 1)
    {
        return u8"Вчера";
    }
    else if (std::difftime(curTime, objTime) <= 7 * 24 * 3600){
        return u8"На этой неделе";
    }
    else if (obj_tm->tm_year + 1900 == curYear &&
        obj_tm->tm_mon + 1 == curMonth)
    {
        return u8"В этом месяце";
    }
    else if (obj_tm->tm_year + 1900 == curYear){
        return u8"В этом году";
    }

    return u8"Ранее";
}

std::vector<Group> Grouper::ByTime(const std::vector<ListObject>& objs) {
    auto sortFunc = [](const ListObject& a, const ListObject& b) {
        return a.timestamp > b.timestamp;
    };

    return GroupObject(objs, ProcessTime, sortFunc);
}

static bool IsFirstRusLetter(const std::string& str) {
    if (str.size() < 2) 
        return false;
    unsigned char ch = static_cast<unsigned char>(str[0]);
    return (ch == 0xD0 || ch == 0xD1);
}

static std::string ProcessName(const ListObject& obj) {
    if (obj.name.empty())
        return "#";

    std::string firstLetter;
    if (IsFirstRusLetter(obj.name))
        firstLetter = obj.name.substr(0, 2);
    else 
        firstLetter = obj.name[0];

    if (firstLetter.size() == 2)
        return firstLetter;

    return  "#";
}

std::vector<Group> Grouper::ByName(const std::vector<ListObject>& objs) {
    auto sortFunc = [](const ListObject& a, const ListObject& b) {
        return a.name < b.name;
    };

    return GroupObject(objs, ProcessName, sortFunc);
}

std::vector<Group> Grouper::ByType(const std::vector<ListObject>& objs) {
    auto ProcessType = [&objs](const ListObject& obj) {
        std::string groupName;

        auto typeCount = std::count_if(objs.begin(), objs.end(), [&obj](const ListObject& a) {
            return a.type == obj.type;
        });

        if (typeCount > 1)
            groupName = obj.type;
        else
            groupName = u8"Разное";

        return groupName;
    };

    auto sortFunc = [](const ListObject& a, const ListObject& b) {
        return a.name < b.name;
    };

    return GroupObject(objs, ProcessType, sortFunc);
}