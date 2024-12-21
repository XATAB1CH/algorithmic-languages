#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "structures.h"

int MaxIdPipeline(std::unordered_map<int, Pipeline>& PipelineMap) {
    int maxId = 0;
    for (const auto& Pipeline : PipelineMap) {
        if (Pipeline.second.id > maxId) {
            maxId = Pipeline.second.id;
        }
    }
    return maxId;
}

// Редактировать трубу
void EditPipeline(std::unordered_map<int, Pipeline>& PipelineMap, int id) {
    for (auto& Pipeline : PipelineMap) {
        if (Pipeline.second.id == id) {
            Pipeline.second.toggleRepairStatus();
            std::cout << "Pipeline " << id << " edited" << std::endl;
            return;
        } 
    }
    std::cout << "Pipeline not edited" << std::endl;
}

// Создать трубу
Pipeline CreatePipeline(std::unordered_map<int, Pipeline> PipelineMap, int id) {
    std::string name;
    double length;
    double diameter;
    bool inRepair;

    std::cout << "Enter pipe name: ";
    while (!(std::cin >> name) || name.empty() || (std::cin.peek() != '\n')) {
            std::cout << "Invalid input. Please enter a non-empty string: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter pipe length: ";
    while (!(std::cin >> length) || length <= 0 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter pipe diameter: ";
    while (!(std::cin >> diameter) || diameter <= 0 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Is pipe in repair? (Enter 1 if yes, 0 if no): ";
    while (!(std::cin >> inRepair) || inRepair < 0 || inRepair > 1 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter 1 or 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return Pipeline{
        id: id,
        name: name,
        length: length,
        diameter: diameter,
        inRepair: inRepair,
    };
}

void DeletePipeline(std::unordered_map<int, Pipeline>& PipelineMap, int id) {
    for (auto& Pipeline : PipelineMap) {
        if (Pipeline.second.id == id) {
            PipelineMap.erase(id);
            std::cout << "CS " << id << " deleted" << std::endl;
            return;
        }
    }
    std::cout << "CS not deleted" << std::endl;
}

void filterPipeByName (std::unordered_map<int, Pipeline> PipelineMap) {
    std::string pipeNameFilter;
    std::cout << "Enter pipeline name filter: ";
    while (!(std::cin >> pipeNameFilter) || pipeNameFilter.empty() || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Enter a name: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Pipelines:\n";
    for (const auto& pipeline : PipelineMap) {
        if (pipeline.second.name.find(pipeNameFilter) != std::string::npos) {
            pipeline.second.showInfo();
        }
    }
}

void filterPipeByRepairStatus (std::unordered_map<int, Pipeline> PipelineMap) {
    bool pipeRepairStatus = false;
    std::cout << "Enter pipeline repair filter: ";
    while (!(std::cin >> pipeRepairStatus) || pipeRepairStatus < 0 || pipeRepairStatus > 0 || (std::cin.peek() != '\n')) {
        std::cout << "Invalid input. Please enter 1 or 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Pipelines:\n";
    for (const auto& pipeline : PipelineMap) {
        if (pipeline.second.inRepair == pipeRepairStatus) {
            pipeline.second.showInfo();
        }
    }
}