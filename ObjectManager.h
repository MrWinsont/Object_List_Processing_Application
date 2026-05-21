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

    void Add(const ListObject& obj);

    void GroupByDistance();

    void GroupByTime();

    void GroupByName();

    void GroupByType();

    void PrintObjects();

    void PrintCurrentGroup();

private:
    std::vector<ListObject> objs;
    std::vector<Group> groupedObjs;
};