#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "structures.h"

int MaxIdCS(std::unordered_map<int, CS>& CSMap) {
    int maxId = 0;
    for (const auto& CS : CSMap) {
        if (CS.second.id > maxId) {
            maxId = CS.second.id;
        }
    }
    return maxId;
}

// Редактировать станцию
void EditCS(std::unordered_map<int, CS>& CSMap, int id) {
    for (auto& CS : CSMap) {
        if (CS.second.id == id) {
            CSMap[id].editWorkingWorkshops();
            std::cout << "CS " << id << " edited" << std::endl;
            return;
        } 
    }
    std::cout << "CS not edited" << std::endl;
}

// Создать станцию
CS CreateCS(std::unordered_map<int, CS> CSMap) {
    int id;
    std::string name;
    int workshops;
    int workingWorkshops;
    double efficiency;

    std::cout << "Enter CS name: ";
    std::cin >> name;
    std::cout << "Enter number of workshops: ";
    while (!(std::cin >> workshops) || workshops <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter number of working workshops: ";
    while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops) {
        std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter efficiency: ";
    while (!(std::cin >> efficiency) || efficiency < 0|| efficiency > 100) {
        std::cout << "Invalid input. Please enter a number between 0 and 100: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (CSMap.size() == 0) {
        id = 0;
    } else {
        id = MaxIdCS(CSMap) + 1;
    }

    return CS{
        id: id,
        name: name,
        workshops: workshops,
        workingWorkshops: workingWorkshops,
        efficiency: efficiency,
    };
}

void DeleteCS(std::unordered_map<int, CS>& CSMap, int id) {
    for (auto& CS : CSMap) {
        if (CS.second.id == id) {
            CSMap.erase(id);
            std::cout << "CS " << id << " deleted" << std::endl;
            return;
        }
    }
    std::cout << "CS not deleted" << std::endl;
}