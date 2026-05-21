#include "grouper.h"

static std::string ProcessDist(const ListObject& obj) {
    auto dist = obj.Dist();
    std::string groupName = u8"далеко";

    if (dist <= 100.0)
        groupName = u8"до 100 ед.";
    else if (dist <= 1000.0)
        groupName = u8"до 1000 ед.";
    else if (dist <= 10000.0)
        groupName = u8"до 10000 ед.";

    return groupName;
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

    return groupName;
}

std::vector<Group> Grouper::ByTime(const std::vector<ListObject>& objs) {
    auto sortFunc = [](const ListObject& a, const ListObject& b) {
        return a.timestamp > b.timestamp;
    };

    return GroupObject(objs, ProcessTime, sortFunc);
}

static std::string ProcessName(const ListObject& obj) {
    std::string firstLetter;

    if (obj.name.size() >= 2 && (unsigned char)obj.name[0] == 0xD0 || (unsigned char)obj.name[0] == 0xD1) {
        firstLetter = obj.name.substr(0, 2);
    }
    else {
        firstLetter = obj.name[0];
    }

    std::string groupName = "#";
    if (firstLetter.size() == 2) {
        groupName = firstLetter;
    }

    return groupName;
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

    return GroupObject(objs, ProcessType, sortFunc);;
}