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
void saveToFile(Pipeline Pipeline, CS Station, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << " " << Pipeline.length << " " << Pipeline.diameter << " " << Pipeline.inRepair << "\n";
        file << " " << Station.workshops << " " << Station.workingWorkshops << " " << Station.efficiency << "\n";
        file.close();
        std::cout << "Data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for saving.\n";
    }
}

// Загрузить информацию из файла
void loadFromFile(Pipeline& Pipeline, CS& Station, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> Pipeline.length >> Pipeline.diameter >> Pipeline.inRepair;
        file >> Station.workshops >> Station.workingWorkshops >> Station.efficiency;
        file.close();
        std::cout << "Data loaded successfully.\n";
    } else {
        std::cerr << "Error opening file for loading.\n";
    }
}

// Главное меню
void menu() {
    Pipeline Pipeline;
    CS Station;
    int choice;

    while (true) {
        std::cout << "\n1. Add pipeline\n2. Add CS\n3. View all objects\n4. Edit Pipeline\n5. Edit CS\n6. Save\n7. Load\n0. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        clear();
        switch (choice) {
            case 1: {
                Pipeline.getInfo();
                break;
            }
            case 2: {
                Station.getInfo();
                clear();
                break;
            }
            case 3: {
                std::cout << "Pipelines:\n";
                Pipeline.showInfo();
                std::cout << "~~~" << std::endl;
                std::cout << "Compressor Stations:\n";
                Station.showInfo();
                break;
            }
            case 4: {
                Pipeline.toggleRepairStatus();
                break;
            }
            case 5: {
                int action;
                std::cout << "1. Start workshop\n2. Stop workshop\n";
                std::cin >> action;
                if (action == 1) {
                    Station.startWorkshop();
                } else if (action == 2) {
                    Station.stopWorkshop();
                } else {
                    std::cout << "Invalid action.\n";
                }
                break;
            }
            case 6:
                saveToFile(Pipeline, Station, "data.txt");
                break;
            case 7:
                loadFromFile(Pipeline, Station, "data.txt");
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