#pragma once
#include "grouper.h"
#include <iostream>
#include <fstream>
#include <memory>


class ObjectManager
{
public:
    void LoadFromFile(const std::string& filename);

    void Save(const std::string& filename) {}

    void Add(const ListObject& obj) {
        // doesn't work with Cyrillic
        std::ofstream f("objects.txt", std::ios::app);

        if(f.is_open()){
            f << obj.name << " " <<
                obj.x << " " <<
                obj.y << " " <<
                obj.type << " " <<
                obj.timestamp << "\n";
        }
    }


    //groupers

    void PrintObjects();

private:
    std::vector<ListObject> objs;

    ListObject parseLineToObj(const std::string& line) {
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
};