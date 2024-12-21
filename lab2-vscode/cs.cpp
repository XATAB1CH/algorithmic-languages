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
            CS.second.editWorkingWorkshops();
            std::cout << "CS " << id << " edited" << std::endl;
            return;
        } 
    }
    std::cout << "CS not edited" << std::endl;
}

// Создать станцию
CS CreateCS(std::unordered_map<int, CS> CSMap, int id) {
    std::string name;
    int workshops;
    int workingWorkshops;
    double efficiency;

    std::cout << "Enter CS name: ";
    while (!(std::cin >> name) || name.empty() || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a non-empty string: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter number of workshops: ";
    while (!(std::cin >> workshops) || workshops <= 0 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter number of working workshops: ";
    while (!(std::cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > workshops || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter a valid integer between 0 and " << workshops << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter efficiency: ";
    while (!(std::cin >> efficiency) || efficiency < 0|| efficiency > 100 || (std::cin.peek() != '\n')) {
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

void filterCSByName (std::unordered_map<int, CS> CSMap) {
    std::string CSNameFilter;
    std::cout << "Enter cs name filter: ";
    while (!(std::cin >> CSNameFilter) || CSNameFilter.empty() || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Enter a name: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "CS:\n";
    for (const auto& CS : CSMap) {
        if (CS.second.name.find(CSNameFilter) != std::string::npos) {
            CS.second.showInfo();
        }
    }
}

void filterCSByProcentFilter (std::unordered_map<int, CS> CSMap) {
    double CSProcentFilter = 0;
    double unused = 0;

    std::cout << "Enter CS efficiency: ";
    while (!(std::cin >> CSProcentFilter) || CSProcentFilter <= 0 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\n~~~\n" << "Compressor staions:" << std::endl;
    for (const auto& station : CSMap) {
        if (station.second.efficiency == CSProcentFilter) {
            station.second.showInfo();
        }
    }
}