#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>

struct Object
{
    std::string name;
    double x = 0.0;
    double y = 0.0;
    std::string type;
    double timestamp = 0.0;

    void Info() {
        std::cout << "name: " << name <<
            "; X: " << x << 
            "; Y: " << y << 
            "; type: " << type << 
            "; timestamp: " << timestamp << "\n";
    }
};

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

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::vector<Object> objs;

    std::string line;

    std::ifstream f("objects.txt");

    if (f.is_open()) {
        while (std::getline(f, line)) {
            objs.push_back(ParseLineToObj(line));
        }
    }

    f.close();

    for (auto&& item : objs) {
        item.Info();
    }
    
}
