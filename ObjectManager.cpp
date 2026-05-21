#include "ObjectManager.h"

static ListObject parseLineToObj(const std::string& line) {
    if (line.empty()) return ListObject{};

    ListObject obj;

    size_t pos1 = 0;
    size_t pos2 = 0;

    pos2 = line.find(' ', pos1);
    obj.name = line.substr(pos1, pos2 - pos1);
    pos1 = pos2 + 1;

    pos2 = line.find(' ', pos1);
    obj.x = std::stod(line.substr(pos1, pos2 - pos1));
    pos1 = pos2 + 1;

    pos2 = line.find(' ', pos1);
    obj.y = std::stod(line.substr(pos1, pos2 - pos1));
    pos1 = pos2 + 1;

    pos2 = line.find(' ', pos1);
    obj.type = line.substr(pos1, pos2 - pos1);
    pos1 = pos2 + 1;

    obj.timestamp = std::stod(line.substr(pos1));

    return obj;
}

void ObjectManager::LoadFromFile(const std::string& filename) {
    objs.clear();

    std::string line;

    std::ifstream f(filename);

    if (f.is_open()) {
        while (std::getline(f, line)) {
            objs.push_back(parseLineToObj(line));
        }
    }else {
        throw std::runtime_error(
            "Cannot open file: " + filename);
    }
}

void ObjectManager::Save(const std::string& filename) {
    std::ofstream f(filename);

    if (f.is_open()) {
        for (const auto& group : groupedObjs) {
            f << group.name << ":\n";

            for (const auto& obj : group.objGroup) {
                f << obj.name << " "
                    << obj.x << " "
                    << obj.y << " "
                    << obj.type << " "
                    << obj.timestamp
                    << '\n';
            }
        }
    }else {
        throw std::runtime_error(
            "Cannot open file: " + filename);
    }
}

void ObjectManager::Add(const ListObject& obj) {
    // doesn't work with Cyrillic
    std::ofstream f("objects.txt", std::ios::app);

    if (f.is_open()) {

        f << "\n" << obj.name << " " <<
            obj.x << " " <<
            obj.y << " " <<
            obj.type << " " <<
            obj.timestamp;
    }
    objs.push_back(obj);
}

void ObjectManager::PrintObjects() {
    for (auto& item : objs) {
        item.Info();
    }
}

void ObjectManager::PrintCurrentGroup() {
    for (const auto& item : groupedObjs) {
        std::cout << item.name << ":\n";
        for (auto i : item.objGroup) {
            i.Info();
        }
    }
}

void ObjectManager::GroupByDistance() {
    groupedObjs = Grouper::ByDistance(objs);
}

void ObjectManager::GroupByTime() {
    groupedObjs = Grouper::ByTime(objs);
}

void ObjectManager::GroupByName() {
    groupedObjs = Grouper::ByName(objs);
}

void ObjectManager::GroupByType() {
    groupedObjs = Grouper::ByType(objs);
}

bool ObjectManager::IsGroupsEmpty() {
    return groupedObjs.empty();
}

bool ObjectManager::IsObjectListEmpty() {
    return objs.empty();
}