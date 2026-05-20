#include <iostream>
#include <fstream>
#include <windows.h>

#include "grouper.h"

Object ParseLineToObj(const std::string& line) {
    if (line.empty()) return Object{};

    Object obj;

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

void ReadObjects(const std::string& filename, std::vector<Object>& objects) {
    std::string line;

    std::ifstream f(filename);

    if (f.is_open()) {
        while (std::getline(f, line)) {
            objects.push_back(ParseLineToObj(line));
        }
    }
    else {
        std::cerr << "No such file or directory: " << filename << std::endl;
        return;
    }

    f.close();
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::vector<Object> objs;
    ReadObjects("objects.txt", objs);

    for (auto i : objs) {
        i.Info();
    }

    auto gr = GroupByDistance(objs);

    for (const auto& item : gr) {
        std::cout << item.name << ":\n";
        for (auto i : item.objGroup) {
            i.Info();
        }
    }
}
