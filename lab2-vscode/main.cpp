#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>

#include "structures.h"
#include "pipeline.cpp"
#include "cs.cpp"

// Очистить консоль 
void clear() {
    #if defined _WIN32
        system("cls");
    #endif
}

// Функция логирования строки
void log(const std::string str) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << str << "\n";
        logFile.close();
    }
}

void logStruct(Pipeline pipe) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << pipe << "\n";
        logFile.close();
    }
}

// Сохранить информацию в файл
void saveToFile(std::unordered_map<int, Pipeline>& PipelineMap, std::unordered_map<int, CS>& CSMap, const std::string& filename) {
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
        file.close();
        std::cout << "Data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for saving.\n";
    }
}

// Загрузить информацию из файла
void loadFromFile(std::unordered_map<int, Pipeline>& PipelineMap, std::unordered_map<int, CS>& CSMap, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        size_t pipesCount, stationsCount;
        file >> pipesCount;
        PipelineMap.clear();
        for (size_t i = 0; i < pipesCount; ++i) {
            Pipeline Pipeline;
            file >> Pipeline.id >> Pipeline.name >> Pipeline.length >> Pipeline.diameter >> Pipeline.inRepair;
            PipelineMap.insert(std::make_pair(i, Pipeline));
        }
        file >> stationsCount;
        CSMap.clear();
        for (size_t i = 0; i < stationsCount; ++i) {
            CS Station;
            file >> Station.id >> Station.name >> Station.workshops >> Station.workingWorkshops >> Station.efficiency;
            CSMap.insert(std::make_pair(Station.id, Station));
        }
        file.close();
        std::cout << "Data loaded successfully.\n";
    } else {
        std::cerr << "Error opening file for loading.\n";
    }
}

// Главное меню
void menu() {
    std::unordered_map<int, Pipeline> PipelineMap;
    std::unordered_map<int, CS> CSMap;
    int choice;

    while (true) {
        std::cout << "\n1. Add pipeline\n2. Add CS\n3. View all objects\n4. View filtred objects\n5. Edit Pipeline\n6. Edit CS\n7. Delete pipeline\n8. Delete CS\n9. Pipe batch editing\n10. Save\n11. Load\n0. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        clear();
        switch (choice) {
            case 1: {
                Pipeline newPipeline = CreatePipeline(PipelineMap);
                log("Создал новую трубу");
                logStruct(newPipeline);
                PipelineMap.insert(std::make_pair(newPipeline.id, newPipeline));
                break;
            }
            case 2: {
                CS newCS = CreateCS(CSMap);
                CSMap.insert(std::make_pair(newCS.id, newCS));
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
                break;
            }
            case 4: {
                int pipeRepairFilter = 0;
                std::string pipeNameFilter;
                double pipeProcentFilter = 0;
                std::string csNameFilter;
                double unused = 0;

                std::cout << "Enter pipeline name filter: ";
                std::cin >> pipeNameFilter;
                std::cout << "Enter pipeline repair filter: ";
                std::cin >> pipeRepairFilter;
                std::cout << "~~~\n";
                std::cout << "Enter CS name filter: ";
                std::cin >> csNameFilter;
                std::cout << "Enter CS procent filter (show objects that have percentage of unused workshops more): ";
                std::cin >> pipeProcentFilter;
                clear();

                std::cout << "Pipelines:\n";
                for (const auto& pipeline : PipelineMap) {
                    if (pipeline.second.name.find(pipeNameFilter) != std::string::npos && pipeline.second.inRepair == pipeRepairFilter) {
                        pipeline.second.showInfo();
                    }
                }
                
                std::cout << "\n~~~\n" << "Compressor staions:" << std::endl;
                for (const auto& station : CSMap) {
                    unused = 100 - double(double(station.second.workingWorkshops) / double(station.second.workshops)) * 100;
                    if (station.second.name.find(csNameFilter) != std::string::npos && unused > pipeProcentFilter) {
                        station.second.showInfo();
                    }
                }
                break;
            }
            case 5: {
                std::cout << "Enter Pipeline id to edit: ";
                int id;
                std::cin >> id;
                EditPipeline(PipelineMap, id);
                break;
            }
            case 6: {
                std::cout << "Enter CS index to edit: ";
                int index;
                std::cin >> index;
                EditCS(CSMap, index);
                break;
            }
            case 7: {
                std::cout << "Enter Pipeline index to delete: ";
                int index;
                std::cin >> index;
                DeletePipeline(PipelineMap, index);
                break;
            }
            case 8: {
                int index;
                std::cout << "Enter CS index to delete: ";
                std::cin >> index;
                DeleteCS(CSMap, index);
                break;
            }
            case 9:
                int index;
                int index1, index2;
                std::cout << "Enter first index of plenty: ";
                std::cin >> index1;    
                std::cout << "Enter second index of plenty: ";
                std::cin >> index2;

                std::cout << "Enter 1 for delete or 0 for editing." << std::endl;
                while (!(std::cin >> index) || index < 0 || index > 1 ) {
                    std::cout << "Invalid input. Please enter 1 or 0: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (index == 1) {
                    for (int i = index1; i <= index2; i++) {
                        PipelineMap.erase(i);
                        std::cout << i << " has been deleted." << std::endl;
                    }
                    std::cout << "Deliting pipes has been done." << std::endl;
                } else if (index == 0) {
                    for (int i = index1; i <= index2; i++) {
                        PipelineMap[i].toggleRepairStatus();
                    }
                    std::cout << "Repair status has been changed." << std::endl;
                }
                break;
            case 10:
                saveToFile(PipelineMap, CSMap, "data.txt");
                break;
            case 11:
                loadFromFile(PipelineMap, CSMap, "data.txt");
                break;
            case 12:
                for (auto& Pipeline : PipelineMap) {
                    std::cout << Pipeline.second.id << " " << Pipeline.second.name << " " << Pipeline.second.length << " "<<Pipeline.second.diameter << " " << Pipeline.second.inRepair <<  std::endl;
                }
                break;
            case 0:
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

