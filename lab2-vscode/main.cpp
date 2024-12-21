#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "structures.h"
#include "pipeline.cpp"
#include "cs.cpp"
#include <string>
#include <chrono>
#include "log.cpp"

// Очистить консоль 
void clear() {
    #if defined _WIN32
        system("cls");
    #endif
}

// Сохранить информацию в файл
void saveToFile(std::unordered_map<int, Pipeline>& PipelineMap, std::unordered_map<int, CS>& CSMap, const std::string& filename) {
    int a, b = 0;
    std::ofstream file(filename);
    if (file.is_open()) {
        file << PipelineMap.size() << "\n";
        for (const auto& Pipeline : PipelineMap) {
            file << Pipeline.second.id << " " << Pipeline.second.name << " " << Pipeline.second.length << " " << Pipeline.second.diameter << " " << Pipeline.second.inRepair << "\n";
        }
        file << CSMap.size() << "\n";
        for (const auto& Station : CSMap) {
            file << Station.second.id << " " << Station.second.name << " " << Station.second.workshops << " " << Station.second.workingWorkshops << " " << Station.second.efficiency << "\n";
        }
        a = PipelineMap[PipelineMap.size() - 1].id;
        b = CSMap[CSMap.size() - 1].id;

        file << a << "\n" << b << "\n";
        file.close();
        std::cout << "Data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for saving.\n";
        logString("Error opening file for saving.\n");
    }
}

// Загрузить информацию из файла
std::vector<int> loadFromFile(std::unordered_map<int, Pipeline>& PipelineMap, std::unordered_map<int, CS>& CSMap, const std::string& filename) {
    int a, b;
    std::ifstream file(filename);
    if (file.is_open()) {
        size_t pipesCount, stationsCount;
        file >> pipesCount;
        PipelineMap.clear();
        for (size_t i = 0; i < pipesCount; ++i) {
            Pipeline Pipeline;
            file >> Pipeline.id >> Pipeline.name >> Pipeline.length >> Pipeline.diameter >> Pipeline.inRepair;
            PipelineMap.insert(std::make_pair(Pipeline.id, Pipeline));
        }
        file >> stationsCount;
        CSMap.clear();
        for (size_t i = 0; i < stationsCount; ++i) {
            CS Station;
            file >> Station.id >> Station.name >> Station.workshops >> Station.workingWorkshops >> Station.efficiency;
            CSMap.insert(std::make_pair(Station.id, Station));
        }
        file >> a;
        file >> b;
       
        file.close();
        std::cout << "Data loaded successfully.\n";
        return std::vector<int>{a+1,b+1};
    } else {
        std::cerr << "Error opening file for loading.\n";
        logString("Error opening file for loading.\n");
    }
    return std::vector<int>{0,0};
}

// Главное меню
void menu() {
    std::unordered_map<int, Pipeline> PipelineMap;
    std::unordered_map<int, CS> CSMap;
    int choice;
    int pipeCount = 0;
    int csCount = 0;
    std::vector<int> counts;

    while (true) {
        std::cout << "\n1. Add pipeline\n2. Add CS\n3. View all objects\n4. View filtred objects\n5. Edit Pipeline\n6. Edit CS\n7. Delete pipeline\n8. Delete CS\n9. Pipe batch editing\n10. Save\n11. Load\n0. Exit\n";
        std::cout << "Select an option: ";
        while (!(std::cin >> choice) || choice < 0 || choice > 11 || isdigit(choice) || (std::cin.peek() != '\n')) {
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        clear();
        switch (choice) {
            case 1: {
                Pipeline newPipeline = CreatePipeline(PipelineMap, pipeCount);
                pipeCount += 1;
                PipelineMap.insert(std::make_pair(newPipeline.id, newPipeline));
                logString("Created new pipeline:");
                logPipe(newPipeline);
                break;
            }
            case 2: {
                CS newCS = CreateCS(CSMap, csCount);
                csCount += 1;
                CSMap.insert(std::make_pair(newCS.id, newCS));
                logString("Created new CS:");
                logCS(newCS);
                break;
            }
            case 3: {
                std::cout << "Pipelines:\n";
                for (const auto& Pipeline : PipelineMap) {
                    
                    Pipeline.second.showInfo();
                }
                std::cout << "~~~" << std::endl;
                std::cout << "Compressor Stations:\n";
                for (const auto& Station : CSMap) {
                    Station.second.showInfo();
                }
                logString("Viewed all objects.");
                break;
            }
            case 4: {
                int choice = 0;

                std::cout << "1. Filter pipe by name\n2. Filter by repair status\n3. Filter cs by name\n4. Filter cs by procent filter\n";
                std::cout << "Select an option: ";
                while (!(std::cin >> choice) || choice < 0 || choice > 4 || isdigit(choice) || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid choice. Please try again.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                switch (choice)
                {
                case 1:
                    filterPipeByName(PipelineMap);
                    break;
                case 2:
                    filterPipeByRepairStatus(PipelineMap);    
                    break;
                case 3:
                    filterCSByName(CSMap);
                    break;
                case 4:
                    filterCSByProcentFilter(CSMap);
                    break;
                default:
                    break;
                }
                break;
            }
            case 5: {
                int id;
                std::cout << "Enter Pipeline id to edit: ";
                std::cin >> id;
                EditPipeline(PipelineMap, id);
                logString("Edited pipeline.");
                break;
            }
            case 6: {
                int id;
                std::cout << "Enter CS index to edit: ";
                std::cin >> id;
                EditCS(CSMap, id);
                logString("Edited CS.");
                break;
            }
            case 7: {
                int id;
                std::cout << "Enter Pipeline index to delete: ";
                while (!(std::cin >> id) || isdigit(id) || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid choice. Please try again.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                DeletePipeline(PipelineMap, id);
                logString("Deleted pipeline.");
                break;
            }
            case 8: {
                int id;
                std::cout << "Enter CS index to delete: ";
                while (!(std::cin >> id) || isdigit(id) || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid choice. Please try again.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                DeleteCS(CSMap, id);
                logString("Deleted CS.");
                break;
            }
            case 9:
                int index;
                int index1, index2;
                std::cout << "Enter first index of plenty: ";
                while (!(std::cin >> index1) || index1 < 0 || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid input. Please enter a positive number: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }  
                std::cout << "Enter second index of plenty: ";
                while (!(std::cin >> index2) || index2 < 0 || index2 < index1 || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid input. Please enter index2 < index1: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } 

                std::cout << "Enter 1 for delete or 0 for editing." << std::endl;
                while (!(std::cin >> index) || index < 0 || index > 1 || (std::cin.peek() != '\n')) {
                    std::cout << "Invalid input. Please enter 1 or 0: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (index == 1) {
                    for (int i = index1; i <= index2; i++) {
                        DeletePipeline(PipelineMap, i);
                    }
                    std::cout << "Deliting pipes has been done." << std::endl;
                } else if (index == 0) {
                    for (int i = index1; i <= index2; i++) {
                        PipelineMap[i].toggleRepairStatus();
                    }
                    std::cout << "Repair status has been changed." << std::endl;
                }
                logString("Deleted plenty.");
                break;
            case 10:
                saveToFile(PipelineMap, CSMap, "data.txt");
                logString("Data saved successfully.");
                break;
            case 11:
                counts = loadFromFile(PipelineMap, CSMap, "data.txt");
                pipeCount = counts[0];
                csCount = counts[1];

                logString("Data loaded successfully.");
                break;
            case 0:
                logString("Exiting program.\n");
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}

