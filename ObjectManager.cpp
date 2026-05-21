#include "ObjectManager.h"



void ObjectManager::LoadFromFile(const std::string& filename) {
    objs.clear();

    std::string line;

    std::ifstream f(filename);

    if (f.is_open()) {
        while (std::getline(f, line)) {
            objs.push_back(parseLineToObj(line));
        }
    }else {
        std::cerr << "No such file or directory: " << filename << std::endl;
        return;
    }
}

void ObjectManager::PrintObjects() {
    if (!objs.empty()) {
        for (auto& item : objs) {
            item.Info();
        }
    }else {
        std::cout << u8"Список пуст!\n";
    }
}