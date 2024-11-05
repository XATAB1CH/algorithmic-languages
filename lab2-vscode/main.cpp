#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "structures.h"

// Очистить консоль 
void clear() {
    #if defined _WIN32
        system("cls");
    #endif
}

// Сохранить информацию в файл
void saveToFile(const std::vector<Pipeline>& PipelineArray, const std::vector<CS>& CSArray, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << PipelineArray.size() << "\n";
        for (const auto& Pipeline : PipelineArray) {
            file << Pipeline.name << " " << Pipeline.length << " " << Pipeline.diameter << " " << Pipeline.inRepair << "\n";
        }
        file << CSArray.size() << "\n";
        for (const auto& station : CSArray) {
            file << station.name << " " << station.workshops << " " << station.workingWorkshops << " " << station.efficiency << "\n";
        }
        file.close();
        std::cout << "Data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for saving.\n";
    }
}

// Загрузить информацию из файла
void loadFromFile(std::vector<Pipeline>& PipelineArray, std::vector<CS>& CSArray, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        size_t pipesCount, stationsCount;
        file >> pipesCount;
        PipelineArray.clear();
        for (size_t i = 0; i < pipesCount; ++i) {
            Pipeline Pipeline;
            file >> Pipeline.name >> Pipeline.length >> Pipeline.diameter >> Pipeline.inRepair;
            PipelineArray.push_back(Pipeline);
        }
        file >> stationsCount;
        CSArray.clear();
        for (size_t i = 0; i < stationsCount; ++i) {
            CS station;
            file >> station.name >> station.workshops >> station.workingWorkshops >> station.efficiency;
            CSArray.push_back(station);
        }
        file.close();
        std::cout << "Data loaded successfully.\n";
    } else {
        std::cerr << "Error opening file for loading.\n";
    }
}

// Главное меню
void menu() {
    std::vector<Pipeline> PipelineArray;
    std::vector<CS> CSArray;
    int choice;

    while (true) {
        std::cout << "\n1. Add pipeline\n2. Add CS\n3. View all objects\n4. View filtred objects\n5. Edit Pipeline\n6. Edit CS\n7. Delete pipeline\n8. Delete CS\n9. Save\n10. Load\n11. Pipe batch editing\n0. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        clear();
        switch (choice) {
            case 1: {
                Pipeline Pipeline;
                Pipeline.id = PipelineArray.size();
                Pipeline.getInfo();
                PipelineArray.push_back(Pipeline);
                break;
            }
            case 2: {
                CS cs;
                cs.id = CSArray.size();
                cs.getInfo();
                CSArray.push_back(cs);
                clear();
                break;
            }
            case 3: {
                std::cout << "Pipelines:\n";
                for (const auto& Pipeline : PipelineArray) {
                    Pipeline.showInfo();
                }
                std::cout << "~~~" << std::endl;
                std::cout << "Compressor Stations:\n";
                for (const auto& station : CSArray) {
                    station.showInfo();
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
                for (const auto& pipeline : PipelineArray) {
                    if (pipeline.name.find(pipeNameFilter) != std::string::npos && pipeline.inRepair == pipeRepairFilter) {
                        pipeline.showInfo();
                    }
                }
                
                std::cout << "\n~~~\n" << "Compressor staions:" << std::endl;

                for (const auto& station : CSArray) {
                    unused = 100 - double(double(station.workingWorkshops) / double(station.workshops)) * 100;
                    if (station.name.find(csNameFilter) != std::string::npos && unused > pipeProcentFilter) {
                        station.showInfo();
                    }
                }
            
                break;
            }
            case 5: {
                std::cout << "Enter Pipeline index to edit: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < PipelineArray.size()) {
                    PipelineArray[index].toggleRepairStatus();
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 6: {
                std::cout << "Enter CS index to edit: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < CSArray.size()) {
                    int action;
                    std::cout << "1. Start workshop\n2. Stop workshop\n";
                    std::cin >> action;
                    if (action == 1) {
                        CSArray[index].startWorkshop();
                    } else if (action == 2) {
                        CSArray[index].stopWorkshop();
                    } else {
                        std::cout << "Invalid action.\n";
                    }
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 7: {
                std::cout << "Enter Pipeline index to delete: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < PipelineArray.size()) {
                    PipelineArray.erase(PipelineArray.begin() + index);
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 8: {
                int index;
                std::cout << "Enter CS index to delete: ";
                std::cin >> index;
                if (index >= 0 && index < CSArray.size()) {
                    CSArray.erase(CSArray.begin() + index);
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 9:
                saveToFile(PipelineArray, CSArray, "data.txt");
                break;
            case 10:
                loadFromFile(PipelineArray, CSArray, "data.txt");
                break;
            case 11:
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
                    PipelineArray.erase(PipelineArray.begin() + index1, PipelineArray.begin() + index2 + 1);
                    std::cout << "Deliting pipes has been done." << std::endl;
                } else if (index == 0) {
                    for (int i = index1; i <= index2; i++) {
                        PipelineArray[i].toggleRepairStatus();
                    }
                    std::cout << "Repair status has been changed." << std::endl;
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