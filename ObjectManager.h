#pragma once
#include "grouper.h"
#include <iostream>
#include <fstream>
#include <memory>


class ObjectManager
{
public:
	void LoadFromFile(const std::string& filename) {
        objs.clear();

        std::string line;

        std::ifstream f(filename);

        if (f.is_open()) {
            while (std::getline(f, line)) {
                objs.push_back(parseLineToObj(line));
            }
        }
        else {
            std::cerr << "No such file or directory: " << filename << std::endl;
            return;
        }
	}

    void Save(const std::string& filename) {}

    void Add() {}

    //groupers

private:
    std::vector<Object> objs;

    Object parseLineToObj(const std::string& line) {
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
};